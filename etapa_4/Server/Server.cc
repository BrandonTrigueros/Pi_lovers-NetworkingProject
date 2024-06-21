#include "Server.h"

void Server::run() {
  // std::thread* worker;
  // worker = new std::thread(listenIntermediateUDP);
  // worker->join();

  // scanExistingPieces();
  this->scanExistingPieces();
  // print this->serverPieces
  // for (const auto& piece : this->serverPieces) {
  //   std::cout << piece << std::endl;
  // }
}

// todo server sends a list of available pieces to the intermediate server
void Server::listenIntermediateUDP() {
  struct sockaddr serverInfo;
  VSocket* intermediate = new Socket('d', false);
  intermediate->Bind(UDP_PORT);
  char buffer[BUFFER_SIZE];

  std::string message = "";
  for (const auto& piece : this->serverPieces) {
    message += piece + ",";
  }

  memset(&serverInfo, 0, sizeof(serverInfo));

  std::cout << "Server is running" << std::endl;
  while (true) {
    intermediate->recvFrom((void*)buffer, BUFFER_SIZE, (void*)&serverInfo);
    std::cout << "Received data: " << buffer << std::endl;
    intermediate->sendTo((void*)message, strlen(message), (void*)&serverInfo);
    std::cout << "Sent data: " << message << std::endl;
  }
  intermediate->Close();
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
