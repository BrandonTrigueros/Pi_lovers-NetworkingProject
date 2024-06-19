#include "Server.h"

void Server::run()
{
  std::thread *worker;
  worker = new std::thread(listenIntermediateUDP);
  worker->join();
}

void Server::listenIntermediateUDP() {
  struct sockaddr serverInfo;
  VSocket *intermediate = new Socket('d', false);
  intermediate->Bind(UDP_PORT);
  char buffer[BUFFER_SIZE];
  char* message = (char *) "Connection accepted";
  memset(&serverInfo, 0, sizeof(serverInfo));
  std::cout << "Server is running" << std::endl;
  while (true) {
    intermediate->recvFrom((void*) buffer, BUFFER_SIZE, (void*)&serverInfo);
    std::cout << "Received data: " << buffer << std::endl;
    intermediate->sendTo((void*) message, strlen(message), (void*)&serverInfo);
    std::cout << "Sent data: " << message << std::endl;
  }
  intermediate->Close();
}
