#include "Intermediate.h"

Intermediate::Intermediate() { this->ipDirection = "127.0.0.1"; }

Intermediate::~Intermediate() {}

void Intermediate::run()
{
  // ! <--------------------------------- Tabla de ruteo y UDP  ----------------------------->
  // requestPieces

  // Connectintermediates
  // ListenServer -> Solo si no esta conectado a su server
  // ListenIntermediates
  // ! <---------------------------------- Requests TCP -------------------------------------->
  // ListenClient()
  // SendRequest();
  std::cout <<  YELLOW << "P.I Lovers intermediate server is running" << RESET << std::endl;
  if (!intermediateServer_UDP())
  {
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

void Intermediate::listenClients()
{
  std::thread *worker;
  VSocket *intermediateSocket, *client;
  intermediateSocket = new Socket('s');
  intermediateSocket->Bind(CLIENT_PORT);
  intermediateSocket->Listen(5);
  while (true) {
    std::cout << "Waiting for client" << std::endl;
    client = intermediateSocket->Accept();
    std::cout << "Client connected" << std::endl;
    worker = new std::thread(handleClient, (void *)client, this->routingTable);
  }
  worker->join();
}

void Intermediate::handleClient(void *socket, std::map<std::string, std::vector<std::string>> routingTable)
{
  char request[BUFFER_SIZE];
  Socket *client = (Socket *)socket;
  client->Read(request, BUFFER_SIZE);

  //! MANEJO DE LA REQUEST
  std::map<std::string, std::vector<std::string>> routingTableRef = routingTable;
  std::string partOne, partTwo, partOneIP, partTwoIP, response;
  std::string requestStr(request);
  size_t firstSlashPos = requestStr.find_first_of('/');
  size_t lastSlashPos = requestStr.find_first_of('/', firstSlashPos + 1);
  std::string figureComment = requestStr.substr(firstSlashPos + 1, lastSlashPos - 5);
  requestStr = figureComment;
  std::cout << "Figure is: " << requestStr << std::endl;

  if (verifyRequest(requestStr, routingTableRef))
  {
    std::cout << "Figure is available" << std::endl;
    sendTCPRequest(requestStr.c_str(), 0, routingTable);
    sendTCPRequest(requestStr.c_str(), 1, routingTable);
  }
  else
  {
    // ToDo: return ERROR 404
  }

  // ip1 = this->routingTable[p1][0];
  // ip2 = this->routingTable[p2][0];
  // if (ip1 == this->ipDirection) {
  //   //? Que acá se capture el html en un string
  //   sendTCPRequest(figure.c_str(), 1);
  // } else {
  //   // Create thread with socket to search for the piece
  // }
  // if (ip2 == this->ipDirection) {
  //   //? Que acá se capture el html en un string
  //   sendTCPRequest(figure.c_str(), 2);
  // } else {
  //   // Create thread with socket to search for the piece
  // }

  //? Cuando se tienen ambos, se castean a html, se crea la response y se manda

  client->Write(response.c_str());
  client->Close();
  //! REQUEST MANEJADA
}

void Intermediate::sendTCPRequest(const char *figureName, int figurePart, std::map<std::string, std::vector<std::string>> routingTable)
{
  char buffer[BUFFER_SIZE];
  Socket *intermediateSocket = new Socket('s', false);
  std::string figureRequest = (buildRequest(figureName, figurePart)).c_str();

  std::string figureIP = getFigureIP(figureName, 0, routingTable);
  std::cout << "Figure IP: " << figureIP << std::endl;

  figureIP = getFigureIP(figureName, 1, routingTable);
  std::cout << "Figure IP: " << figureIP << std::endl;

  //? La ip debería ser la del servidor de piezas?
  intermediateSocket->Connect(figureIP.c_str(), TCP_PORT_SERVER);
  intermediateSocket->Write(figureRequest.c_str(), strlen(figureRequest.c_str()));
  intermediateSocket->Read(buffer, BUFFER_SIZE);
  intermediateSocket->Close();
  //? Server devolverá acá el html? Deberíamos devolverlo com valor de retorno?
}

std::string Intermediate::getFigureIP(std::string figureName, int legoPart, std::map<std::string, std::vector<std::string>> routingTable)
{
  std::string figureIP = "";
  std::string legoFigure = figureName + std::to_string(legoPart);
  std::cout << "Figure: " << legoFigure << std::endl;

  auto it = routingTable.find(figureName + "0");
  if (it != routingTable.end())
  {
    std::cout << "Figure found" << std::endl;
    figureIP = it->second.front(); // or it->second[0]
    std::cout << "Figure IP: " << figureIP << std::endl;
  }
  else
  {
    std::cout << "Figure not found" << std::endl;
  }
  return figureIP;
}

void Intermediate::listenIntermediateBroadcast()
{
  //! Ni idea aun de como entrarle a esto
}

int Intermediate::broadcastNewServer()
{
  //! Ni idea aun de como entrarle a esto x2
  return 0;
}

bool Intermediate::intermediateServer_UDP()
{
  int numBytes;
  char buffer[BUFFER_SIZE];
  char *message = (char *)"Connection request";
  struct sockaddr_in intermediateInfo;
  VSocket *intermediate = new Socket('d');
  memset(&intermediateInfo, 0, sizeof(intermediateInfo));
  intermediateInfo.sin_family = AF_INET;
  intermediateInfo.sin_port = htons(UDP_PORT_SERVER);
  intermediateInfo.sin_addr.s_addr = INADDR_ANY;

  numBytes = intermediate->sendTo(
      (void *)message, strlen(message), (void *)&intermediateInfo);
  numBytes = intermediate->recvFrom(
      (void *)buffer, BUFFER_SIZE, (void *)&intermediateInfo);
  buffer[numBytes - 1] = '\0';
  updateTable(buffer);
  printTable();
  intermediate->Close();
  return numBytes <= 0 ? false : true;
  // //! CAPTURAR RESPUESTA DEL SERVER (PIEZAS CONOCIDAS)
  // std::stringstream ss(buffer);
  // std::string item;
  // while (std::getline(ss, item, ',')) {
  //   knownPieces.push_back(item);
  // }
  // //! RESPUESTA CAPTURADA EN ATRIBUTO KNOWNPIECES
}

void Intermediate::listenServerUDP()
{
  int bytesReceived = 0;
  struct sockaddr_in serverInfo;
  VSocket *intermediate = new Socket('d', false);
  intermediate->Bind(UDP_PORT_SERVER);
  char buffer[BUFFER_SIZE];
  char *message = (char *)"Connection accepted";
  memset(&serverInfo, 0, sizeof(serverInfo));
  while (bytesReceived <= 0)
  {
    bytesReceived = intermediate->recvFrom((void *)buffer, BUFFER_SIZE, (void *)&serverInfo);
  }
  updateTable(buffer);
  printTable();
  intermediate->sendTo((void *)message, strlen(message), (void *)&serverInfo);
  intermediate->Close();
}

bool Intermediate::verifyRequest(std::string userRequest, std::map<std::string, std::vector<std::string>> routingTableRef)
{
  return ((int)((routingTableRef.find(userRequest + "0") != routingTableRef.end())) != -1) &&
         ((int)((routingTableRef.find(userRequest + "1") != routingTableRef.end()) )!= -1);
}

std::string Intermediate::buildRequest(const char *figureName, int figurePart)
{
  std::string legoFigure(figureName);
  std::string request = "GET / ";
  request += legoFigure + "%" + std::to_string(figurePart) + "//HTTP\r\n\r\n";
  return request;
}

std::vector<std::string> Intermediate::split(const std::string &s, char delimiter)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter))
  {
    tokens.push_back(token);
  }
  return tokens;
}

void Intermediate::addPiece(std::string piece)
{
  std::vector<std::string> parts = split(piece, '@');
  if (parts.size() < 2)
  {
    std::cerr << "Invalid piece format" << std::endl;
    return;
  }
  std::string figura = parts[0];
  std::string ip = parts[1];
  if (pieces_map.find(figura) != pieces_map.end())
  {
    pieces_map[figura].push_back(ip);
  }
  else
  {
    pieces_map[figura] = {ip};
  }
  route_table.clear();
  for (const auto &pair : pieces_map)
  {
    route_table += "$" + pair.first;
    for (const std::string &ip : pair.second)
    {
      route_table += "@" + ip;
    }
  }
  route_table += "$";
}

void Intermediate::deletePiece(std::string piece)
{
  std::vector<std::string> parts = split(piece, '@');
  if (parts.size() < 2)
  {
    std::cerr << "Invalid piece format" << std::endl;
    return;
  }
  std::string figura = parts[0];
  std::string ip = parts[1];
  auto it = pieces_map.find(figura);
  if (it != pieces_map.end())
  {
    auto &ips = it->second;
    ips.erase(std::remove(ips.begin(), ips.end(), ip), ips.end());
    if (ips.empty())
    {
      pieces_map.erase(it);
    }
  }
  else
  {
    std::cerr << "Error: Intentando eliminar una figura inexistente" << std::endl;
  }
  route_table.clear();
  for (const auto &pair : pieces_map)
  {
    route_table += "$" + pair.first;
    for (const std::string &ip : pair.second)
    {
      route_table += "@" + ip;
    }
  }
  route_table += "$";
}

void Intermediate::parseTable()
{
  this->pieces_map.clear();
  std::vector<std::string> segmentos = split(this->route_table, '$');
  for (const std::string &segmento : segmentos)
  {
    if (!segmento.empty())
    {
      std::vector<std::string> parts = split(segmento, '@');
      if (!parts.empty())
      {
        std::string figure = parts[0];
        std::vector<std::string> ips(parts.begin() + 1, parts.end());
        this->pieces_map[figure] = ips;
      }
    }
  }
}

void Intermediate::updateTable(std::string newTable)
{
  this->route_table = newTable;
  this->parseTable();
}

void Intermediate::printTable()
{
  for (const auto &pair : this->pieces_map)
  {
    std::cout << "Figura: " << pair.first << std::endl;
    std::cout << "IPs: ";
    for (const std::string &ip : pair.second)
    {
      std::cout << ip << " ";
    }
    std::cout << std::endl;
  }
}
