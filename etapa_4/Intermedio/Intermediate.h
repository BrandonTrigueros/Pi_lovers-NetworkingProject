#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include "Socket.h"
#include "VSocket.h"
#include <algorithm>
#include <bitset>
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

#define BUFFER_SIZE 5024
#define HOSTNAME_LENGTH 1024

#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define UNDERLINE "\033[4m"
#define RESET "\033[0m"

class Intermediate {
  private:
  std::map<std::string, std::vector<std::string>>
      routingTable;  // Map that contains figure and IP
  std::string routeTable;
  std::string randomNumbers;
  u_int miRand;
  char* broadcastAddress;

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
  std::string getIPAddress();
  void addPieces(std::string);

  std::vector<std::string> splitIP(std::string, char delimiter);
  std::string ipToBinary(std::string);
  std::string binaryToIP(std::string);
  std::string getBroadcastAddress(std::string, std::string);

  public:
  Intermediate();
  ~Intermediate();
  void run();
};
#endif  // INTERMEDIATE_H
