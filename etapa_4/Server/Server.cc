#include "Server.h"

void Server::run() {

}


void  Server::listenIntermediateUDP(){
  std::thread* worker;
  VSocket *piezas, *intermediate;
  VSocket *piezas = new Socket('d', false);
  piezas->Bind(UDP_PORT);
  while (true) {
    intermediate = piezas->Accept();
    worker = new std::thread(handleIntermediateUDP, (void*)intermediate);
  }
  intermediate->Close();
}

void Server::handleIntermediateUDP(void* socket){
  VSocket* intermediate = (VSocket*)socket;
  struct sockaddr server_info;
  char buffer[BUFFER_SIZE];
  memset(&server_info, 0, sizeof(server_info));
  intermediate->recvFrom((void*) buffer, BUFFER_SIZE, (void*)&server_info);
  std::cout << "Received data: " << buffer << std::endl;
  char message[] = "Se ha establecido la conexion con exito";
  intermediate->sendTo((void*) message, strlen(message), (void*)&server_info);
}