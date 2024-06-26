#ifndef CLIENT_H
#define CLIENT_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "Socket.h"
#include "VSocket.h"

#define CLIENT_PORT 4100
#define MAXBUF 1024

#define RED "\033[1;31m"
#define CYAN "\033[1;36m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

class Client {
  private:
  VSocket* clientSocket;
  char socketType;
  const char* ipDirection;
  char buffer[MAXBUF];
  std::string figure;
  std::string request;
  std::string response;

  public:
  Client();
  ~Client();
  void run();
  bool analyzeArgs(int, char*[]);
  void printResponse();
};
#endif