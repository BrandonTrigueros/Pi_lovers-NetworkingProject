#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include "RequestQueue.h"
#include "ResponseQueue.h"
#include "Socket.h"
#include "VSocket.h"
#include <iostream>
#include <map>
#include <thread>
#include <vector>

#define CLIENT_PORT 4100
#define TCP_PORT 4200
#define UDP_BROADCAST_PORT 4300
#define UDP_PORT_SERVER 4400
#define BUFFER_SIZE 512

class Intermediate {
  private:
  char* userRequest;
  RequestQueue* requestQueue;
  ResponseQueue* responseQueue;
  // Map ip & figuras
  std::map<std::string, std::vector<std::string>> routingTable;

  // Multimap Figuras & servers

  public:
  Intermediate();
  ~Intermediate();
  void run();

  private:
  // intermidiate
  void listenIntermidiateBroadcast();
  int broadcastNewServer();

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
#endif  // MASTERINTERMEDIATE_H
