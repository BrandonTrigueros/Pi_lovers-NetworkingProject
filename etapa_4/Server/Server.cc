#include "Server.h"

void Server::run()
{
  std::thread *worker_UDP, *worker_TCP;
  std::cout << "Server running" << std::endl;
  worker_UDP = new std::thread(listenIntermediateUDP);
  worker_TCP = new std::thread(listenIntermediateTCP);
  worker_TCP->join();
  worker_UDP->join();
}

void Server::listenIntermediateUDP() {
  int status = 0;
  struct sockaddr_in serverInfo;
  char ip[BUFFER_SIZE];
  char buffer[BUFFER_SIZE];
  VSocket *intermediate = new Socket('d', false);
  intermediate->Bind(UDP_PORT);
  char* message;
  memset(&serverInfo, 0, sizeof(serverInfo));

  while (true) {
    status = intermediate->recvFrom((void*) buffer, BUFFER_SIZE, (void*)&serverInfo);
    std::cout << "Received data: " << buffer << std::endl;
    if( status > 0 ) {
      inet_ntop(AF_INET, &(serverInfo.sin_addr), ip, BUFFER_SIZE);
      message = (char*)ip;
    }
    status = intermediate->sendTo((void*) message, strlen(message), (void*)&serverInfo);
    std::cout << "Sent data: " << message << std::endl;
  }
  intermediate->Close();
}

void Server::listenIntermediateTCP() {
  std::thread* thread_TCP;
  VSocket *server, *intermediate;
  server = new Socket('s');

  server->Bind(TCP_PORT);  // Port to access this mirror server
  server->Listen(5);  // Set backlog queue to 5 conections

  while (true) {
    intermediate = server->Accept();
    thread_TCP = new std::thread(responseTCP, (void*)intermediate);
  }
  thread_TCP->join();
}

void Server::responseTCP(void* socket) {
  char request[BUFFER_SIZE];
  char* response = (char*)"TCP connection accepted";
  VSocket* intermediate = (VSocket*)socket;
  intermediate->Read(request, BUFFER_SIZE);
  std::cout << "Received data: " << request << std::endl;
  intermediate->Write((void*)response, strlen(response));
  std::cout << "Sent data: " << response << std::endl;
  intermediate->Close();
}