#ifndef CLIENT_H
#define CLIENT_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "Socket.h"
#include "VSocket.h"

#define RED "\033[1;31m"
#define CYAN "\033[1;36m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

#define PORT 1233
#define MAX_BUFFER_SIZE 8000

class Client {
  private:
  char socketType;
  const char* osv4;
  Socket* clientSocket;

  std::string figure;
  std::string request;

  int legoParts;
  bool figureFound;
  bool illegalRequest;
  std::string htmlResponse;
  std::string finalResponse;

  private:
  void printTitle();
  void printResponse();
  int getLegoParts(std::string);
  std::string castHTML(const std::string&);
  void verifyResponse(const std::string);
  std::string formatResponse(std::string);

  public:
  Client();
  ~Client();
  void run();
  bool analyzeArgs(int, char*[]);
};
#endif