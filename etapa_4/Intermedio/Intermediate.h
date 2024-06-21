#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include <thread>
#include <iostream>
#include "Socket.h"
#include "VSocket.h"
#include "RequestQueue.h"
#include "ResponseQueue.h"

#define CLIENT_PORT 1234 //4100
#define TCP_PORT_INTERMEDIATE 4200
#define TCP_PORT_SERVER 4500
#define UDP_PORT_INTERMEDIATE 4300
#define UDP_PORT_SERVER 4400
#define BUFFER_SIZE 512

class Intermediate {
  private:
    char* userRequest;
    RequestQueue* requestQueue;
    ResponseQueue* responseQueue;
    std::string ipDirection = "127.0.0.1";
    // Map intermediates & ip
    // Multimap Figuras & servers

  public:
    Intermediate();
    ~Intermediate();
    void run();

    void clientIntermediate();
    void listenClient();
    static void handleClient(void*, RequestQueue*);
    // void sendTCP();
    // void receiveTCP();

    void intermediateServer_UDP();
    // void receiveUDP();

    void sendTCPRequest(RequestQueue*);
    std::string buildRequest(int);
    // removeFromQueue();

    // addToQueue();

    // castHTML();
  
};
#endif // MASTERINTERMEDIATE_H
