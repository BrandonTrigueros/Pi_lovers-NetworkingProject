#include "Intermediate.h"

Intermediate::Intermediate() { }

Intermediate::~Intermediate() { }

void Intermediate::run() {
  // ! <--------------------------------- Tabla de ruteo y UDP
  // -----------------------------> requestPieces

  // Connectintermediates
  // ListenServer -> Solo si no esta conectado a su server
  // ListenIntermediates
  // ! <---------------------------------- Requests TCP
  // --------------------------------------> ListenClient() SendRequest();
  std::cout << YELLOW << "P.I Lovers intermediate server is running" << RESET
            << std::endl;
  if (!intermediateServer_UDP()) {
    listenServerUDP();
  }
  listenClients();
  // Al levantarse lo primero que hacemos es escuchar por UDP
  // listenIntermediateBroadcast();
  // Se envía por broadcast las piezas al resto de intermediarios
  // broadcastNewServer();
  // Se comienza a escuchar requests de los clientes
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
  std::cout << "Listening to intermediates broadcast" << std::endl;
  VSocket* intermediate = new Socket('d');
  intermediate->broadcastAddress = "172.16.123.79";
  intermediate->Bind(UDP_PORT_INTERMEDIATE);
  for (;;) {
    char buffer[BUFFER_SIZE];
    char* addrSrc;
    addrSrc = intermediate->ListenBroadcast(buffer, BUFFER_SIZE);
    struct sockaddr_in* addr = (struct sockaddr_in*)addrSrc;

    // responder al broadcast
    // gurdar info de tabla de ruteo
  }
}

int Intermediate::broadcastNewServer() {
  std::cout << "Broadcasting new server" << std::endl;
  VSocket* intermediate = new Socket('d');
  intermediate->broadcastAddress = "172.16.123.79";
  // hacer broacast con ip y pieza conocida
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
  intermediateInfo.sin_port = htons(UDP_PORT_SERVER);
  intermediateInfo.sin_addr.s_addr = INADDR_ANY;

  numBytes = intermediate->sendTo(
      (void*)message, strlen(message), (void*)&intermediateInfo);
  numBytes = intermediate->recvFrom(
      (void*)buffer, BUFFER_SIZE, (void*)&intermediateInfo);
  buffer[numBytes - 1] = '\0';
  updateTable(buffer);
  intermediate->Close();
  return numBytes <= 0 ? false : true;
}

void Intermediate::listenServerUDP() {
  int bytesReceived = 0;
  struct sockaddr_in serverInfo;
  VSocket* intermediate = new Socket('d', false);
  intermediate->Bind(UDP_PORT_SERVER);
  char buffer[BUFFER_SIZE];
  char* message = (char*)"Connection accepted";
  memset(&serverInfo, 0, sizeof(serverInfo));
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
