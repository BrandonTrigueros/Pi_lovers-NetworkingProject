#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include "Socket.h"
#include "VSocket.h"
#include <iostream>
#include <map>
#include <sstream>
#include <thread>
#include <vector>

#define CLIENT_PORT 4100
#define TCP_PORT_INTERMEDIATE 4200
#define UDP_PORT_INTERMEDIATE 4300
#define UDP_PORT_SERVER 4400
#define TCP_PORT_SERVER 4500

#define BUFFER_SIZE 512

class Intermediate {
  private:
  std::vector<std::string> knownPieces;
  std::map<std::string, std::vector<std::string>> routingTable;  // figura, ips
  std::string ipDirection;

  public:
  Intermediate();
  ~Intermediate();
  void run();

  private:
  // client
  void listenClients();
  void handleClient(void*);

  // intermediate
  void listenIntermidiateBroadcast();
  int broadcastNewServer();

  // server
  void intermediateServer_UDP();

  void sendTCPRequest(const char*, int);
  std::string buildRequest(const char*, int);

  // void sendTCP();
  // void receiveTCP();
  // void receiveUDP();
  // castHTML();
};
#endif  // INTERMEDIATE_H
