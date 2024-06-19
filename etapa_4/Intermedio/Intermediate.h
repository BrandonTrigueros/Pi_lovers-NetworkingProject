#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include <thread>
#include <iostream>
#include "Socket.h"
#include "VSocket.h"
#include "RequestQueue.h"
#include "ResponseQueue.h"

#define CLIENT_PORT 1234 //4100
#define TCP_PORT 4200
#define UDP_PORT_INTERMEDIATE 4300
#define UDP_PORT_SERVER 4400
#define BUFFER_SIZE 512

class Intermediate {
  private:
    char* userRequest;
    RequestQueue* requestQueue;
    ResponseQueue* responseQueue;
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

    // buildRequest();
    // removeFromQueue();

    // addToQueue();

    // castHTML();
  
};
#endif // MASTERINTERMEDIATE_H
