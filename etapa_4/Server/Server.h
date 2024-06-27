#ifndef SERVER_H
#define SERVER_H

#include "Socket.h"
#include "VSocket.h"
#include <filesystem>
#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h> // For gethostname
#include <netdb.h>   // For gethostbyname


#define TCP_PORT 4500
#define UDP_PORT 4400
#define BUFFER_SIZE 512

#define HOSTNAME_LENGTH 1024


#define YELLOW "\033[33m"
#define RESET "\033[0m"

class Server {
  private:
  char* userRequest;
  std::vector<std::string> serverPieces;
  std::string myLegoFigures;
  // Request queue

  public:
  Server() = default;
  ~Server() = default;
  void run();

  private:
  bool listenIntermediateUDP();
  bool serverIntermediate_UDP();
  
  void scanExistingPieces();
  void concatFigures();
  std::string getIPAddress();
  static void listenIntermediateTCP();
  static void responseTCP(void*);
};
#endif  // SERVER_H