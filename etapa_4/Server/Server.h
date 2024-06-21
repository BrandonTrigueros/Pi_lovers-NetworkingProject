#ifndef SERVER_H
#define SERVER_H

#include "Socket.h"
#include "VSocket.h"
#include <filesystem>
#include <iostream>
#include <thread>
#include <vector>

#define TCP_PORT 4500
#define UDP_PORT 4400
#define BUFFER_SIZE 512

class Server {
  private:
  char* userRequest;
  std::vector<std::string> serverPieces;
  // Request queue

  public:
  Server() = default;
  ~Server() = default;
  void run();

  private:
  static void listenIntermediateUDP();
  void scanExistingPieces();
};
#endif  // SERVER_H