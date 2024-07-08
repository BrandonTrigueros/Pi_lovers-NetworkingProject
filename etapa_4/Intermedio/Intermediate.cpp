#include "Intermediate.h"

#define TABLA 1
#define RAND 0

std::vector<int> splitStringToInts(const std::string& str) {
  std::vector<int> numbers;
  std::stringstream ss(str);
  std::string temp;

  while (std::getline(ss, temp, ',')) {
    numbers.push_back(std::stoi(temp));
  }
  return numbers;
}

std::string joinIntsToString(const std::vector<int>& numbers) {
  std::ostringstream oss;
  for (size_t i = 0; i < numbers.size(); ++i) {
    if (i != 0) {
      oss << ", ";
    }
    oss << numbers[i];
  }
  return oss.str();
}

std::string removeNumberFromString(
    const std::string& numbersStr, const std::string& numberToRemoveStr) {
  int numberToRemove = std::stoi(numberToRemoveStr);
  std::vector<int> numbers = splitStringToInts(numbersStr);

  auto it = std::remove(numbers.begin(), numbers.end(), numberToRemove);
  numbers.erase(it, numbers.end());

  return joinIntsToString(numbers);
}

u_int crateRandom() {
  srand(time(NULL));
  return rand() % 1000;
}

Intermediate::Intermediate() {
  if (RAND) {
    u_int rand = crateRandom();
    this->miRand = rand;
    this->randomNumbers.append(std::to_string(rand));
  }

  std::string ipAddress = getIPAddress();
  std::string subnetMask = "255.255.255.0";
  std::string broadcastAddress
      = (this->getBroadcastAddress(ipAddress, subnetMask));
  this->broadcastAddress = (char*)broadcastAddress.c_str();
}

Intermediate::~Intermediate() { }

void Intermediate::run() {
  // ! <--------------------------------- Tabla de ruteo y UDP
  // ----------------------------->ListenServer -> Solo si no esta conectado a
  // su server
  std::cout << YELLOW << "P.I Lovers intermediate server is running" << RESET
            << std::endl;
  if (!intermediateServer_UDP()) {
    listenServerUDP();
  }

  // ----------------------------->Connect intermediates

  broadcastNewServer();
  std::thread broadcastListener(
      &Intermediate::listenIntermediateBroadcast, this);
  // broadcastListener.join();  //! Quitar este join que no deja avanzar
  broadcastListener.detach();

  // ! <---------------------------------- Requests TCP
  // ----------------------------->ListenClient() SendRequest();
  sleep(50);
  // listenClients();
}

void Intermediate::listenClients() {
  std::thread* worker;
  VSocket *intermediateSocket, *client;
  intermediateSocket = new Socket('s');
  intermediateSocket->Bind(CLIENT_PORT);
  intermediateSocket->Listen(5);
  while (true) {
    client = intermediateSocket->Accept();
    worker = new std::thread(
        handleClient, (void*)client, (void*)&this->routingTable);
  }
  worker->join();
}

void Intermediate::handleClient(void* socket, void* routingTableRef) {
  char request[BUFFER_SIZE];
  std::map<std::string, std::vector<std::string>> routingTable
      = *(std::map<std::string, std::vector<std::string>>*)routingTableRef;
  Socket* client = (Socket*)socket;
  client->Read(request, BUFFER_SIZE);
  std::string response;
  std::string requestStr(request);
  size_t firstSlashPos = requestStr.find_first_of('/');
  size_t lastSlashPos = requestStr.find_first_of('/', firstSlashPos + 1);
  std::string figureComment
      = requestStr.substr(firstSlashPos + 1, lastSlashPos - 5);
  requestStr = figureComment;
  std::string serverResponse = "";
  if (verifyRequest(requestStr, routingTable)) {
    for (int i = 0; i < 2; i++) {
      memset(request, 0, BUFFER_SIZE);
      std::string figurePart = requestStr + std::to_string(i);
      std::string ipAddress = getFigureIP(figurePart, routingTable);
      serverResponse += sendTCPRequest(figurePart, ipAddress);
    }
  } else {
    serverResponse = "error 404";
  }
  client->Write(serverResponse.c_str());
  client->Close();
}

std::string Intermediate::sendTCPRequest(
    std::string figureName, std::string ipAddress) {
  char buffer[BUFFER_SIZE];
  Socket* intermediateSocket = new Socket('s', false);
  std::string figureRequest = buildRequest(figureName);

  memset(buffer, 0, BUFFER_SIZE);
  intermediateSocket->Connect(ipAddress.c_str(), TCP_PORT_SERVER);
  intermediateSocket->Write(
      figureRequest.c_str(), strlen(figureRequest.c_str()));
  intermediateSocket->Read(buffer, BUFFER_SIZE);
  std::string serverResponse(buffer);
  intermediateSocket->Close();
  return serverResponse;
}

std::string Intermediate::getFigureIP(std::string legoFigure,
    std::map<std::string, std::vector<std::string>> routingTable) {
  std::string figureIP = "";
  auto it = routingTable.find(legoFigure);
  if (it != routingTable.end()) {
    figureIP = it->second.front();
  }
  return figureIP;
}

void Intermediate::listenIntermediateBroadcast() {
  std::cout << "Listening to intermediates broadcast msgs" << std::endl;
  char buffer[BUFFER_SIZE];
  VSocket* intermediate = new Socket('d');
  // intermediate->broadcastAddress = "192.168.100.255";  //! 172.16.123.79
  intermediate->broadcastAddress = this->broadcastAddress;
  intermediate->Bind(UDP_PORT_INTERMEDIATE);
  int reps = 0;
  while (true) {
    std::string addrSrc = "";
    memset(buffer, 0, BUFFER_SIZE);
    addrSrc = intermediate->RecvBroadcast(buffer, BUFFER_SIZE);
    std::cout << "Received message: " << buffer << std::endl;

    if (TABLA) {
      std::cout << "Current table: " << this->routeTable << std::endl;
    }
    if (RAND) {
      std::cout << "Current numbers: " << this->randomNumbers << std::endl;
    }

    if (addrSrc != "") {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(UDP_PORT_INTERMEDIATE);
      addr.sin_addr.s_addr = inet_addr(addrSrc.c_str());
      if (strncmp(buffer, "Online", 6) == 0) {
        std::string message(buffer);
        size_t pos = message.find('$');
        message = message.substr(pos);
        std::cout << "Message online: agregando: " << message << std::endl;

        std::string response;
        if (RAND) {
          this->randomNumbers.append(", " + message);
          response = "Connected, " + this->randomNumbers;
        }
        if (TABLA) {
          this->addPieces(message);
          response = "Connected, " + this->routeTable;
        }

        std::cout << "Sending response: " << response << std::endl;
        sleep(1);  //! Sleep para local, probar en el lab sin sleep
        intermediate->sendTo(
            (void*)response.c_str(), strlen(response.c_str()), (void*)&addr);
      } else if (strncmp(buffer, "Connected", 9) == 0) {
        std::string message(buffer);
        size_t pos = message.find('$');
        message = message.substr(pos);
        std::cout << "Message connected: nueva info: " << message << std::endl;

        if (RAND) {
          this->randomNumbers = message;
        }

        if (TABLA) {
          this->updateTable(message);
        }

      } else if (strncmp(buffer, "Offline", 7) == 0) {

        if (RAND) {
          std::string message(buffer);
          std::cout << "Message offline: eliminando numero: "
                    << message.substr(9) << std::endl;
          std::cout << "Numero a eliminar: " << message.substr(9) << std::endl;
          this->randomNumbers
              = removeNumberFromString(this->randomNumbers, message.substr(9));
        }
        if (TABLA) {
          deleteServer(std::string(addrSrc));
        }
      }
    }
    // if (this->miRand >= 500 && reps == 5) {
    //   broadcastDeadServer();
    //   break;
    // }
    reps++;
  }
  intermediate->Close();
}

void Intermediate::broadcastNewServer() {
  // Envíar mensaje de broadcast
  VSocket* intermediate = new Socket('d');

  // intermediate->broadcastAddress = "192.168.100.255";  //! 172.16.123.79
  intermediate->broadcastAddress = this->broadcastAddress;
  std::cout << "Intermediate broadcast address: "
            << intermediate->broadcastAddress << std::endl;

  intermediate->Bind(UDP_PORT_INTERMEDIATE);

  std::string broadcastMessage;
  if (RAND) {
    broadcastMessage = "Online, " + this->randomNumbers;
  }
  if (TABLA) {
    broadcastMessage = "Online, " + this->routeTable;
  }

  char* broadcastMessageChar = (char*)broadcastMessage.c_str();
  intermediate->Broadcast(broadcastMessageChar, strlen(broadcastMessageChar));
  std::cout << "Mensaje enviado por broadcast: " << broadcastMessage
            << std::endl;
  intermediate->Close();
}

void Intermediate::broadcastDeadServer() {
  std::cout << "Broadcasting dead server" << std::endl;
  VSocket* intermediate = new Socket('d');

  // intermediate->broadcastAddress = "192.168.100.255";  //! 172.16.123.79
  intermediate->broadcastAddress = this->broadcastAddress;

  intermediate->Bind(UDP_PORT_INTERMEDIATE);
  std::string broadcastMessage;

  if (TABLA) {
    broadcastMessage = "Offline";
  }
  if (RAND) {
    broadcastMessage = "Offline, " + std::to_string(this->miRand);
  }

  char* broadcastMessageChar = (char*)broadcastMessage.c_str();
  intermediate->Broadcast(broadcastMessageChar, strlen(broadcastMessageChar));
  std::cout << "Mensaje enviado por broadcast: " << broadcastMessage
            << std::endl;
  intermediate->Close();
}

bool Intermediate::intermediateServer_UDP() {
  int numBytes;
  char buffer[BUFFER_SIZE];
  char* message = (char*)"Online";
  struct sockaddr_in intermediateInfo;
  VSocket* intermediate = new Socket('d');
  memset(&intermediateInfo, 0, sizeof(intermediateInfo));
  intermediateInfo.sin_family = AF_INET;
  // intermediateInfo.sin_addr.s_addr = inet_addr("10.1.35.14");
  intermediateInfo.sin_addr.s_addr = inet_addr("10.1.137.160");
  //intermediateInfo.sin_addr.s_addr = inet_addr(getIPAddress().c_str());
  //std::cout << "this IP address: " << getIPAddress() << std::endl;
  intermediateInfo.sin_port = htons(UDP_PORT_SERVER);
  numBytes = intermediate->sendTo(
      (void*)message, strlen(message), (void*)&intermediateInfo);
  numBytes = intermediate->recvFrom(
      (void*)buffer, BUFFER_SIZE, (void*)&intermediateInfo);
  buffer[numBytes - 1] = '\0';
  if (numBytes > 0) {
    std::cout << GREEN << "Connected" << RESET << std::endl;
    updateTable(buffer);
  }
  intermediate->Close();
  return numBytes <= 0 ? false : true;
}

void Intermediate::listenServerUDP() {
  int bytesReceived = 0;
  struct sockaddr_in serverInfo;
  VSocket* intermediate = new Socket('d', false);
  char* message = (char*)"Connection accepted";
  memset(&serverInfo, 0, sizeof(serverInfo));
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_port = htons(UDP_PORT_SERVER);
  serverInfo.sin_addr.s_addr = INADDR_ANY;
  intermediate->Bind(UDP_PORT_SERVER);
  char buffer[BUFFER_SIZE];
  while (bytesReceived <= 0) {
    std::cout << "Listening Server" << std::endl;
    bytesReceived = intermediate->recvFrom(
        (void*)buffer, BUFFER_SIZE, (void*)&serverInfo);
  }
  std::cout << GREEN << "Connected" << RESET << std::endl;
  updateTable(buffer);
  intermediate->sendTo((void*)message, strlen(message), (void*)&serverInfo);
  intermediate->Close();
}

bool Intermediate::verifyRequest(std::string userRequest,
    std::map<std::string, std::vector<std::string>> routingTableRef) {
  std::string partOne = userRequest + "0";
  std::string partTwo = userRequest + "1";

  int partCounter = 0;
  for (const auto& legoFigure : routingTableRef) {
    if (legoFigure.first == partOne || legoFigure.first == partTwo) {
      partCounter++;
    }
  }
  return partCounter == 2;
}

std::string Intermediate::buildRequest(std::string figureName) {
  std::string legoFigure(figureName);
  int partPosition = figureName.size() - 1;
  std::string figurePart = figureName.substr(partPosition);
  legoFigure = legoFigure.substr(0, partPosition);
  std::string request = "GET / ";
  request += legoFigure + "%" + figurePart + "//HTTP\r\n\r\n";
  std::cout << BLUE << UNDERLINE << request << RESET << std::endl;

  return request;
}

std::vector<std::string> Intermediate::split(
    const std::string& s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

void Intermediate::addPieces(std::string pieces) {
  std::vector<std::string> parts = split(pieces, '$');
  for (const std::string& part : parts) {
    addPiece(part);
  }
}

void Intermediate::addPiece(std::string piece) {
  std::vector<std::string> parts = split(piece, '@');
  if (parts.size() < 2) {
    std::cerr << "Invalid piece format" << std::endl;
    return;
  }
  std::string figura = parts[0];
  std::string ip = parts[1];
  if (routingTable.find(figura) != routingTable.end()) {
    routingTable[figura].push_back(ip);
  } else {
    routingTable[figura] = { ip };
  }
  routeTable.clear();
  for (const auto& pair : routingTable) {
    routeTable += "$" + pair.first;
    for (const std::string& ip : pair.second) {
      routeTable += "@" + ip;
    }
  }
  routeTable += "$";
}

void Intermediate::deletePiece(std::string piece) {
  std::vector<std::string> parts = split(piece, '@');
  if (parts.size() < 2) {
    std::cerr << "Invalid piece format" << std::endl;
    return;
  }
  std::string figura = parts[0];
  std::string ip = parts[1];
  auto it = routingTable.find(figura);
  if (it != routingTable.end()) {
    auto& ips = it->second;
    ips.erase(std::remove(ips.begin(), ips.end(), ip), ips.end());
    if (ips.empty()) {
      routingTable.erase(it);
    }
  } else {
    std::cerr << "Error: Intentando eliminar una figura inexistente"
              << std::endl;
  }
  routeTable.clear();
  for (const auto& pair : routingTable) {
    routeTable += "$" + pair.first;
    for (const std::string& ip : pair.second) {
      routeTable += "@" + ip;
    }
  }
  routeTable += "$";
}

void Intermediate::parseTable() {
  this->routingTable.clear();
  std::vector<std::string> segmentos = split(this->routeTable, '$');
  for (const std::string& segmento : segmentos) {
    if (!segmento.empty()) {
      std::vector<std::string> parts = split(segmento, '@');
      if (!parts.empty()) {
        std::string figure = parts[0];
        std::vector<std::string> ips(parts.begin() + 1, parts.end());
        this->routingTable[figure] = ips;
      }
    }
  }
}

void Intermediate::updateTable(std::string newTable) {
  this->routeTable = newTable;
  this->parseTable();
}

void Intermediate::printTable() {
  for (const auto& pair : this->routingTable) {
    std::cout << "Figure: " << pair.first << std::endl;
    std::cout << "IP address: ";
    for (const std::string& ip : pair.second) {
      std::cout << ip << " ";
    }
    std::cout << std::endl;
  }
}

void Intermediate::deleteServer(std::string ip) {
  for (auto& pair : this->routingTable) {
    auto& ips = pair.second;
    ips.erase(std::remove(ips.begin(), ips.end(), ip), ips.end());
    if (ips.empty()) {
      this->routingTable.erase(pair.first);
    }
  }
  routeTable.clear();
  for (const auto& pair : routingTable) {
    routeTable += "$" + pair.first;
    for (const std::string& ip : pair.second) {
      routeTable += "@" + ip;
    }
  }
  routeTable += "$";
}

std::string Intermediate::getIPAddress() {
  char hostname[HOSTNAME_LENGTH];
  hostname[HOSTNAME_LENGTH - 1]
      = '\0';  // Ensure the hostname array is null-terminated
  gethostname(hostname,
      HOSTNAME_LENGTH - 1);  // Retrieve the hostname of the local machine

  struct addrinfo hints, *res, *p;
  int status;
  char ipstr[INET_ADDRSTRLEN];  // Buffer to hold the IPv4 address as a string

  memset(&hints, 0, sizeof hints);  // Zero out the hints structure
  hints.ai_family = AF_INET;  // Specify that we want IPv4 addresses
  hints.ai_socktype = SOCK_STREAM;  // Specify a stream socket (TCP)

  // Get address information for the hostname
  if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
    std::cerr << "getaddrinfo: " << gai_strerror(status)
              << std::endl;  // Print error message
    return "";  // Return an empty string on error
  }

  // Loop through the linked list of results
  for (p = res; p != NULL; p = p->ai_next) {
    void* addr = &((struct sockaddr_in*)p->ai_addr)
                      ->sin_addr;  // Cast the socket address to sockaddr_in and
                                   // extract the IPv4 address
    inet_ntop(p->ai_family, addr, ipstr,
        sizeof ipstr);  // Convert the binary IP address to a readable string
    std::string ipAddress(
        ipstr);  // Create a C++ string from the C-style string
    freeaddrinfo(res);  // Free the memory allocated for the address list
    return ipAddress;  // Return the IP address
  }
  freeaddrinfo(res);  // Free the memory allocated for the address list in case
                      // the loop didn't run
  return "";  // Return an empty string if no IP address was found
}

std::vector<std::string> split(std::string str, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(str);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

std::string Intermediate::ipToBinary(std::string ip) {
  std::vector<std::string> octets = split(ip, '.');
  std::string binaryIp;
  for (const std::string& octet : octets) {
    int num = std::stoi(octet);
    std::bitset<8> bin(num);
    binaryIp += bin.to_string();
  }
  return binaryIp;
}

std::string Intermediate::binaryToIP(std::string binary) {
  std::stringstream ip;
  for (size_t i = 0; i < binary.size(); i += 8) {
    std::bitset<8> octet(binary.substr(i, 8));
    ip << octet.to_ulong();
    if (i < binary.size() - 8) {
      ip << ".";
    }
  }
  return ip.str();
}

std::string Intermediate::getBroadcastAddress(
    std::string ip, std::string subnetMask) {
  std::string binaryIp = ipToBinary(ip);
  std::string binaryMask = ipToBinary(subnetMask);

  // Invert the subnet mask
  std::string invertedMask;
  for (char bit : binaryMask) {
    invertedMask += (bit == '0') ? '1' : '0';
  }

  // Perform bitwise OR between the IP address and the inverted subnet mask
  std::string broadcastBinary;
  for (size_t i = 0; i < binaryIp.size(); ++i) {
    broadcastBinary
        += (binaryIp[i] == '1' || invertedMask[i] == '1') ? '1' : '0';
  }

  return binaryToIP(broadcastBinary);
}