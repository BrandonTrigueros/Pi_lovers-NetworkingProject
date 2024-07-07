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
#define TCP_PORT_SERVER 1234

#define BUFFER_SIZE 5024

#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define UNDERLINE "\033[4m"
#define RESET "\033[0m"

class Intermediate {
  private:
  std::map<std::string, std::vector<std::string>>
      routingTable;  // Map that contains figure and IP
  std::string routeTable;
  u_int random[2];

  // client
  void listenClients();
  static void handleClient(void*, void*);

  // intermediate
  void listenIntermediateBroadcast();
  void broadcastNewServer();
  void broadcastDeadServer();

  // server
  bool intermediateServer_UDP();
  void listenServerUDP();

  static std::string sendTCPRequest(std::string, std::string);
  static std::string getFigureIP(
      std::string, std::map<std::string, std::vector<std::string>>);

  static bool verifyRequest(
      std::string, std::map<std::string, std::vector<std::string>>);
  static std::string buildRequest(std::string);

  std::vector<std::string> split(const std::string& s, char delimiter);
  void updateTable(std::string);
  void addPiece(std::string);
  void deletePiece(std::string);
  void parseTable();
  void printTable();
  void deleteServer(std::string);
  void addPieces(std::string);

  public:
  Intermediate();
  ~Intermediate();
  void run();
};
#endif  // INTERMEDIATE_H
