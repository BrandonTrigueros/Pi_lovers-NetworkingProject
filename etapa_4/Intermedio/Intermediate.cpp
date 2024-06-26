#include "Intermediate.h"

Intermediate::Intermediate() { this->ipDirection = "127.0.0.1"; }

Intermediate::~Intermediate() { }

void Intermediate::run() {
  // Al levantarse lo primero que hacemos es escuchar por UDP
  listenIntermidiateBroadcast();
  // Se trata de establecer una conexión con el servidor de piezas
  intermediateServer_UDP();
  // Se envía por broadcast las piezas al resto de intermediarios
  broadcastNewServer();
  // Se comienza a escuchar requests de los clientes
  listenClients();

  //? Que hace el intermedio aparte de handlear requests?
  // while (true) {
  //   sendTCPRequest(this->requestQueue);
  // }
}

void Intermediate::listenClients() {
  std::thread* worker;
  VSocket *intermediateSocket, *client;
  intermediateSocket = new Socket('s');
  intermediateSocket->Bind(CLIENT_PORT);
  intermediateSocket->Listen(5);
  while (true) {
    client = intermediateSocket->Accept();
    worker = new std::thread(handleClient, (void*)client);
  }
  worker->join();
}

void Intermediate::handleClient(void* socket) {
  char request[BUFFER_SIZE];
  std::string p1, p2, ip1, ip2, response;
  Socket* client = (Socket*)socket;
  client->Read(request, BUFFER_SIZE);

  //! MANEJO DE LA REQUEST
  std::string requestStr(request);
  std::string figure = requestStr.substr(5, requestStr.find_last_of('/') - 6);
  p1 = figure + "1";
  p2 = figure + "2";
  ip1 = this->routingTable[p1][0];
  ip2 = this->routingTable[p2][0];
  if (ip1 == this->ipDirection) {
    //? Que acá se capture el html en un string
    sendTCPRequest(figure.c_str(), 1);
  } else {
    // Create thread with socket to search for the piece
  }
  if (ip2 == this->ipDirection) {
    //? Que acá se capture el html en un string
    sendTCPRequest(figure.c_str(), 2);
  } else {
    // Create thread with socket to search for the piece
  }

  //? Cuando se tienen ambos, se castean a html, se crea la response y se manda

  client->Write(response.c_str());
  client->Close();
  //! REQUEST MANEJADA
}

void Intermediate::listenIntermidiateBroadcast() {
  //! Ni idea aun de como entrarle a esto
}
int Intermediate::broadcastNewServer() {
  //! Ni idea aun de como entrarle a esto x2
}

void Intermediate::intermediateServer_UDP() {
  Socket* intermediate;
  int numBytes;
  char buffer[BUFFER_SIZE];
  char* message = (char*)"Connection request";
  struct sockaddr_in intermediateInfo;
  intermediate = new Socket('d');
  memset(&intermediateInfo, 0, sizeof(intermediateInfo));
  intermediateInfo.sin_family = AF_INET;
  intermediateInfo.sin_port = htons(UDP_PORT_SERVER);
  intermediateInfo.sin_addr.s_addr = INADDR_ANY;

  bool isConnected = false;
  while (!isConnected) {
    numBytes = intermediate->sendTo(
        (void*)message, strlen(message), (void*)&intermediateInfo);
    numBytes = intermediate->recvFrom(
        (void*)buffer, BUFFER_SIZE, (void*)&intermediateInfo);
    buffer[numBytes] = '\0';
    if (numBytes > 0) {
      isConnected = true;
    }
  }
  intermediate->Close();
  //! CAPTURAR RESPUESTA DEL SERVER (PIEZAS CONOCIDAS)
  std::stringstream ss(buffer);
  std::string item;
  while (std::getline(ss, item, ',')) {
    knownPieces.push_back(item);
  }
  //! RESPUESTA CAPTURADA EN ATRIBUTO KNOWNPIECES
}

void Intermediate::sendTCPRequest(const char* figureName, int figurePart) {
  char buffer[BUFFER_SIZE];
  Socket* intermediateSocket = new Socket('s', false);
  const char* figureRequest = (buildRequest(figureName, figurePart)).c_str();

  //? La ip debería ser la del servidor de piezas?
  intermediateSocket->Connect(this->ipDirection.c_str(), TCP_PORT_SERVER);

  intermediateSocket->Write(figureRequest, strlen(figureRequest));
  intermediateSocket->Read(buffer, BUFFER_SIZE);
  intermediateSocket->Close();
  //? Server devolverá acá el html? Deberíamos devolverlo com valor de retorno?
}

std::string Intermediate::buildRequest(const char* figureName, int figurePart) {
  std::string legoFigure(figureName);
  std::string request = "GET / ";
  request += legoFigure + "%" + std::to_string(figurePart) + "//HTTP\r\n\r\n";
  return request;
}