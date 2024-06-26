#include "Server.h"

void Server::run() {
  std::thread *worker_UDP, *worker_TCP;
  worker_UDP = new std::thread(listenIntermediateUDP);
  worker_TCP = new std::thread(listenIntermediateTCP);
  worker_TCP->join();
  worker_UDP->join();
}

void Server::listenIntermediateUDP() {
  int st;
  char ip[BUFFER_SIZE];
  char buffer[BUFFER_SIZE];
  std::string message = "";
  Socket* intermediate = new Socket('d', false);
  struct sockaddr serverInfo;
  memset(&serverInfo, 0, sizeof(serverInfo));
  intermediate->Bind(UDP_PORT);
  while (true) {
    st = intermediate->recvFrom((void*)buffer, BUFFER_SIZE, (void*)&serverInfo);
    if (st > 0) {
      // Concatenar IP al mensaje
      struct sockaddr_in& serverInfo = *(struct sockaddr_in*)&serverInfo;
      inet_ntop(AF_INET, &(serverInfo.sin_addr), ip, BUFFER_SIZE);
      message = (char*)ip + std::string(":");
      // Concatenar piezas conocidas al mensaje
      scanExistingPieces();
      for (const auto& piece : this->serverPieces) {
        message += piece + ",";
      }
      // Enviar mensaje
      intermediate->sendTo(
          (void*)message.c_str(), strlen(message.c_str()), (void*)&serverInfo);
    }
    intermediate->Close();
  }
}

void Server::scanExistingPieces() {
  std::string directoryPath = "./Legos";
  if (!std::filesystem::exists(directoryPath)) {
    std::cerr << "El directorio no existe: " << directoryPath << std::endl;
  }
  for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
    if (entry.is_regular_file() && entry.path().extension() == ".html") {
      this->serverPieces.push_back(entry.path().filename().string());
    }
  }
}

void Server::listenIntermediateTCP() {
  std::thread* thread_TCP;
  VSocket *server, *intermediate;
  server = new Socket('s');

  server->Bind(TCP_PORT);
  server->Listen(5);

  while (true) {
    intermediate = server->Accept();
    thread_TCP = new std::thread(responseTCP, (void*)intermediate);
  }
  thread_TCP->join();
}

// todo: Hacer qudevuelva el html solicitado
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
