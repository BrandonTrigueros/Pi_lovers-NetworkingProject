#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include "Socket.h"
#include "VSocket.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
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
  std::vector<std::string> knownPieces; // Map with the figures of our server
  std::map<std::string, std::vector<std::string>> routingTable; // Map that contains figure and IP
  std::string ipDirection;

  public:
  Intermediate();
  ~Intermediate();
  void run();

  private:
  std::string route_table;
  std::map<std::string, std::vector<std::string>> pieces_map;
  // client
  void listenClients();
  static void handleClient(void*, std::map<std::string, std::vector<std::string>>);

  // intermediate
  void listenIntermediateBroadcast();
  int broadcastNewServer();

  // server
  bool intermediateServer_UDP();
  void listenServerUDP();

  void sendTCPRequest(const char*, int);

  bool verifyRequest();
  std::string buildRequest(const char*, int);

  std::vector<std::string> split(const std::string &s, char delimiter);
  void actTable(std::string);
  void addPiece(std::string);
  void deletePiece(std::string);
  void parseTable();
  void printTable();

  // void sendTCP();
  // void receiveTCP();
  // void receiveUDP();
  // castHTML();
};
#endif  // INTERMEDIATE_H
