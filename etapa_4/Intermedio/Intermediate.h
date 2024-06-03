#ifndef Intermediate_h
#define Intermediate_h

#include <map>
#include <string>
#include "VSocket.h"

class Intermediate {

  private:
    char socketType;
    char* IPDirection;
    VSocket* clientSocket;
    
    
    std::map<std::string/*Figura*/, std::string/*Mitad*/> server_pieza;
    std::multimap<std::string/*Ip*/, std::string/*Servers que lo contiene*/> ip_server;
  public:
    Intermediate() = default;
    ~Intermediate() = default;
    void run();
    void connectServer();
    void listenServer();
    void listerClient();

};

#endif

