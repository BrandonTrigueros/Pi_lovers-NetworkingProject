#ifndef Intermediate_h
#define Intermediate_h

#include "Socket.h"
#include "VSocket.h"
#include <arpa/inet.h>
#include <map>
#include <string.h>
#include <string>
#include <thread>

#define PORT 1233
#define MAX 1024

class Intermediate {
  private:
  char socketType;
  char* IPDirection;
  // VSocket* clientSocket;

  // std::map<std::string /*Figura*/, std::string /*Mitad*/> server_pieza;
  // std::multimap<std::string /*Ip*/, std::string /*Servers que lo contiene*/>
  //     ip_server;

  public:
  Intermediate() = default;
  ~Intermediate() = default;
  void run();

  private:
  void intermediate_client();
  static void listen_client(Socket*);

  // void connect_server();
  // void listen_server();
};

#endif
