#ifndef Intermediate_h
#define Intermediate_h

#include <map>
#include <string>
#include "VSocket.h"
#include "Socket.h"
#include <arpa/inet.h>
#include <string.h>
#include <thread>

#define PORT 1233
#define MAX 512

class Intermediate {

  private:
    char socketType;
    char* IPDirection;
    VSocket* clientSocket;
    
    std::map<std::string/*Figura*/, std::string/*Mitad*/> szerver_piea;
    std::multimap<std::string/*Ip*/, std::string/*Servers que lo contiene*/> ip_server;
  public:
    Intermediate() = default;
    ~Intermediate() = default;
    void run();
    void connect_server();
    void connect_intermediate_UDP();
    void connect_intermediate_TCP();
    void listen_server();
    void intermediate_intermediate();
    void listen_intermediate_TCP(void* socket);
    void listen_intermediate_UDP(void* socket);
    void intermediate_client();
    static void listen_client(void*);

};

#endif

