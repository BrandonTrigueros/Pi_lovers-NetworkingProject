#ifndef MASTERINTERMEDIATE_H
#define MASTERINTERMEDIATE_H

#include <thread>
#include <iostream>
#include "Socket.h"
#include "VSocket.h"

#define CLIENT_PORT 1234 //4100
#define TCP_PORT 4200
#define UDP_PORT 4300
#define BUFFER_SIZE 512

class MasterIntermediate {
  private:
  char* userRequest;
  // Request queue
  // Response queue
  // Map intermediates & ip
  // Multimap Figuras & servers

  public:
  MasterIntermediate();
  ~MasterIntermediate();
  void run();

  void clientIntermediate();
  void listenClient();
  static void handleClient(void*);
  // void sendTCP();
  // void receiveTCP();
  
  // void sendUDP();
  // void receiveUDP();

  // buildRequest();
  // removeFromQueue();

  // addToQueue();

  // castHTML();
  
};
#endif // MASTERINTERMEDIATE_H
