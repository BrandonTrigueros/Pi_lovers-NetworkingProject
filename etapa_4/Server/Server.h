#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include <iostream>
#include "Socket.h"
#include "VSocket.h"

#define TCP_PORT 4500
#define UDP_PORT 4400
#define BUFFER_SIZE 512

class Server {
  private:
  char* userRequest;
  // Request queue

  public:
  Server() = default;
  ~Server() = default;
  void run();

  static void listenIntermediateUDP();

};
#endif // SERVER_H