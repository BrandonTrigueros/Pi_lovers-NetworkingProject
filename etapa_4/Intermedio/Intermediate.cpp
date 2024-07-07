#include "Intermediate.h"

u_int crateRandom() {
  srand(time(NULL));
  return rand() % 1000;
}

Intermediate::Intermediate() {
  u_int rand = crateRandom();
  this->random[0] = rand;
  std::cout << "Random: " << this->random[0] << std::endl;
}

Intermediate::~Intermediate() { }

void Intermediate::run() {
  // ! <--------------------------------- Tabla de ruteo y UDP
  // ----------------------------->ListenServer -> Solo si no esta conectado a
  // su server
  // std::cout << YELLOW << "P.I Lovers intermediate server is running" << RESET
  //           << std::endl;
  // if (!intermediateServer_UDP()) {
  //   listenServerUDP();
  // }

  // ----------------------------->Connect intermediates

  broadcastNewServer();
  std::thread* broadcastListener
      = new std::thread(&Intermediate::listenIntermediateBroadcast, this);
  broadcastListener->join();

  // ! <---------------------------------- Requests TCP
  // ----------------------------->ListenClient() SendRequest();
  // listenClients();
}

void Intermediate::listenClients() {
  std::cout << "Listening client" << std::endl;
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
  std::cout << "Handling client" << std::endl;
  char request[BUFFER_SIZE];
  std::map<std::string, std::vector<std::string>> routingTable
      = *(std::map<std::string, std::vector<std::string>>*)routingTableRef;
  Socket* client = (Socket*)socket;
  client->Read(request, BUFFER_SIZE);
  request[strlen(request)] = '\0';
  std::string response;
  std::string requestStr(request);
  size_t firstSlashPos = requestStr.find_first_of('/');
  size_t lastSlashPos = requestStr.find_first_of('/', firstSlashPos + 1);
  std::string figureComment
      = requestStr.substr(firstSlashPos + 1, lastSlashPos - 5);
  requestStr = figureComment;
  std::string serverResponse = "";
  if (verifyRequest(requestStr, routingTable)) {
    std::cout << "REQUEST: " << requestStr << std::endl;
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
  intermediate->broadcastAddress = "192.168.100.255";
  intermediate->Bind(UDP_PORT_INTERMEDIATE);
  while (true) {
    std::string addrSrc = "";
    memset(buffer, 0, BUFFER_SIZE);
    addrSrc = intermediate->RecvBroadcast(buffer, BUFFER_SIZE);
    std::cout << "Received: " << buffer << "from: " << addrSrc << std::endl;
    // std::cout << "Routing table: " << std::endl;
    // printTable();
    std::string random0 = std::to_string(this->random[0]);
    std::string random1 = std::to_string(this->random[1]);
    std::cout << "Random 0: " << random0 << std::endl;
    std::cout << "Random 1: " << random1 << std::endl;

    if (addrSrc != "") {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(UDP_PORT_INTERMEDIATE);
      addr.sin_addr.s_addr = inet_addr(addrSrc.c_str());
      if (strncmp(buffer, "Online, 1", 6) == 0) {
        std::string message(buffer);
        message = message.substr(8);
        std::cout << "Message online: agregando: " << message << std::endl;
        this->random[1] = stoi(message);
        std::string response = "Connected, " + std::to_string(this->random[0])
            + ", " + std::to_string(this->random[1]) + routeTable;
        std::cout << "Sending response: " << response << std::endl;
        intermediate->sendTo(
            (void*)response.c_str(), strlen(response.c_str()), (void*)&addr);
      } else if (strncmp(buffer, "Connected", 9) == 0) {
        std::string message(buffer);
        message = message.substr(11);
        std::cout << "Message connected: agregando: " << message << std::endl;
        // get random from string
        this->random[0] = stoi(message.substr(0, message.find(',')));
        this->random[1] = stoi(message.substr(message.find(',') + 2));
      } else if (strncmp(buffer, "Offline", 7) == 0) {
        std::cout << "Message offline: eliminando servidor: " << addrSrc
                  << std::endl;
        deleteServer(std::string(addrSrc));
      }
    }
  }
}

void Intermediate::broadcastNewServer() {
  // Envíar mensaje de broadcast
  VSocket* intermediate = new Socket('d');
  intermediate->broadcastAddress = "192.168.100.255";
  intermediate->Bind(UDP_PORT_INTERMEDIATE);
  std::cout << "Broadcast socket binded to: " << UDP_PORT_INTERMEDIATE
            << std::endl;
  std::string broadcastMessage
      = "Online, " + std::to_string(this->random[0]);  //+ this->routeTable;
  std::cout << "Broadcast message: " << broadcastMessage << std::endl;
  char* broadcastMessageChar = (char*)broadcastMessage.c_str();
  intermediate->Broadcast(broadcastMessageChar, strlen(broadcastMessageChar));
  std::cout << "Mensaje enviado por broadcast: " << broadcastMessage
            << std::endl;
  intermediate->Close();
}

void Intermediate::broadcastDeadServer() {
  std::cout << "Broadcasting dead server" << std::endl;
  VSocket* intermediate = new Socket('d');
  intermediate->broadcastAddress = "172.16.123.79";
  std::string broadcastMessage = "Offline";
  char* broadcastMessageChar = (char*)broadcastMessage.c_str();
  intermediate->Broadcast(broadcastMessageChar, strlen(broadcastMessageChar));
}

bool Intermediate::intermediateServer_UDP() {
  int numBytes;
  char buffer[BUFFER_SIZE];
  char* message = (char*)"Connection request";
  struct sockaddr_in intermediateInfo;
  VSocket* intermediate = new Socket('d');
  memset(&intermediateInfo, 0, sizeof(intermediateInfo));
  intermediateInfo.sin_family = AF_INET;
  intermediateInfo.sin_addr.s_addr
      = inet_addr("127.0.0.1");  //! change back to 10.1.35.14
  intermediateInfo.sin_port = htons(UDP_PORT_SERVER);
  numBytes = intermediate->sendTo(
      (void*)message, strlen(message), (void*)&intermediateInfo);
  std::cout << "Num Bytes " << numBytes << std::endl;
  numBytes = intermediate->recvFrom(
      (void*)buffer, BUFFER_SIZE, (void*)&intermediateInfo);
  buffer[numBytes - 1] = '\0';
  updateTable(buffer);
  intermediate->Close();
  // std::cout << "Received: " << buffer << std::endl;
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
    bytesReceived = intermediate->recvFrom(
        (void*)buffer, BUFFER_SIZE, (void*)&serverInfo);
  }
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