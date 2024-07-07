#include "Intermediate.h"

Intermediate::Intermediate() { }

Intermediate::~Intermediate() { }

void Intermediate::run() {
  // ! <--------------------------------- Tabla de ruteo y UDP
  // ----------------------------->ListenServer -> Solo si no esta conectado a su server
  std::cout << YELLOW << "P.I Lovers intermediate server is running" << RESET
            << std::endl;
  if (!intermediateServer_UDP()) {
    listenServerUDP();
  }

  // ----------------------------->Connect intermediates

  // broadcastNewServer();
  // listenIntermediateBroadcast();

  // ! <---------------------------------- Requests TCP
  // ----------------------------->ListenClient() SendRequest();
  listenClients();
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
  VSocket* intermediate = new Socket('d');
  std::cout << "Socket UDP para escuchar broadcasts inicializado";
  intermediate->broadcastAddress = "172.16.123.79";
  intermediate->Bind(UDP_PORT_INTERMEDIATE);
  for (;;) {
    char buffer[BUFFER_SIZE];
    char* addrSrc;
    addrSrc = intermediate->ListenBroadcast(buffer, BUFFER_SIZE);
    std::cout << "Received: " << buffer << "from: " << addrSrc << std::endl;
    struct sockaddr_in* addr = (struct sockaddr_in*)addrSrc;
    // Revisar si el prefijo es "Online, " o "Offline"
    if (strncmp(buffer, "Online", 6) == 0) {
      // Quitar el prefijo "Online, "
      std::string message(buffer);
      message = message.substr(7);
      std::cout << "Message online: agregando" << message << std::endl;
      // gurdar info de tabla de ruteo
      updateTable(message);
      // responder al broadcast
      intermediate->sendTo(
          (void*)this->routeTable.c_str(), this->routeTable.size(), addr);
    } else if (strncmp(buffer, "Offline", 7) == 0) {
      std::cout << "Message offline: eliminando servidor: " << addrSrc
                << std::endl;
      // quitar direccion ip de tabla de ruteo
      deleteServer(std::string(addrSrc));
    }
  }
}

int Intermediate::broadcastNewServer() {
  std::cout << "Broadcasting new server" << std::endl;
  VSocket* intermediate = new Socket('d');
  std::cout << "bind al puerto broadcast";
  intermediate->broadcastAddress = "172.16.123.79";
  std::string broadcastMessage = "Online, " + this->routeTable;
  char* broadcastMessageChar = (char*)broadcastMessage.c_str();
  intermediate->Bind(UDP_PORT_INTERMEDIATE);
  intermediate->Broadcast(broadcastMessageChar, strlen(broadcastMessageChar));
  char buffer[BUFFER_SIZE];
  char* addrSrc;
  addrSrc = intermediate->ListenBroadcast(buffer, BUFFER_SIZE);
  // quitar prefijo "Connected, "
  std::string message(buffer);
  message = message.substr(11);
  // actualizar tabla de ruteo
  updateTable(message);
  return 0;
}

int broadcastDeadServer() {
  std::cout << "Broadcasting dead server" << std::endl;
  VSocket* intermediate = new Socket('d');
  intermediate->broadcastAddress = "172.16.123.79";
  std::string broadcastMessage = "Offline";
  char* broadcastMessageChar = (char*)broadcastMessage.c_str();
  intermediate->Broadcast(broadcastMessageChar, strlen(broadcastMessageChar));
  return 0;
}

bool Intermediate::intermediateServer_UDP() {
  int numBytes;
  char buffer[BUFFER_SIZE];
  char* message = (char*)"Connection request";
  struct sockaddr_in intermediateInfo;
  VSocket* intermediate = new Socket('d');
  memset(&intermediateInfo, 0, sizeof(intermediateInfo));
  intermediateInfo.sin_family = AF_INET;
  // intermediateInfo.sin_addr.s_addr = inet_addr("10.1.35.14");
  intermediateInfo.sin_addr.s_addr = inet_addr(getIPAddress().c_str());
  intermediateInfo.sin_port = htons(UDP_PORT_SERVER);
  numBytes = intermediate->sendTo(
      (void*)message, strlen(message), (void*)&intermediateInfo);
  numBytes = intermediate->recvFrom(
      (void*)buffer, BUFFER_SIZE, (void*)&intermediateInfo);
  buffer[numBytes - 1] = '\0';
  if(numBytes > 0) {
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
  hostname[HOSTNAME_LENGTH - 1] = '\0';       // Ensure the hostname array is null-terminated
  gethostname(hostname, HOSTNAME_LENGTH - 1); // Retrieve the hostname of the local machine

  struct addrinfo hints, *res, *p;
  int status;
  char ipstr[INET_ADDRSTRLEN]; // Buffer to hold the IPv4 address as a string

  memset(&hints, 0, sizeof hints); // Zero out the hints structure
  hints.ai_family = AF_INET;       // Specify that we want IPv4 addresses
  hints.ai_socktype = SOCK_STREAM; // Specify a stream socket (TCP)

  // Get address information for the hostname
  if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0)
  {
    std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl; // Print error message
    return "";                                                         // Return an empty string on error
  }

  // Loop through the linked list of results
  for (p = res; p != NULL; p = p->ai_next)
  {
    void *addr = &((struct sockaddr_in *)p->ai_addr)->sin_addr; // Cast the socket address to sockaddr_in and extract the IPv4 address
    inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr); // Convert the binary IP address to a readable string
    std::string ipAddress(ipstr); // Create a C++ string from the C-style string
    freeaddrinfo(res); // Free the memory allocated for the address list
    return ipAddress; // Return the IP address
  }
  freeaddrinfo(res); // Free the memory allocated for the address list in case the loop didn't run
  return ""; // Return an empty string if no IP address was found
}