#ifndef CLIENT_H
#define CLIENT_H

#include <algorithm>
#include <cctype>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <regex>
#include <iostream>

#include "VSocket.h"
#include "Socket.h"
#include "SSLSocket.h"

#define RED "\033[1;31m"
#define CYAN "\033[1;36m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"
#define MAX_BUFFER_SIZE 8000

class Client {
  private:  
    VSocket* clientSocket;
    char socketType;
    char responseArray[MAX_BUFFER_SIZE]; 
    std::string concatResponse;
    std::string figure; 
    std::string request; 
    std::string htmlResponse; 
    std::string finalResponse;
    int legoParts;
    bool figureFound;
    const char* osv4;

    
    std::string castHTML(const std::string&);
    void verifyResponse(const std::string);

    int getLegoParts(std::string);
    std::string formatResponse(std::string);
    

  public:
    Client();
    ~Client();
    void run();
    bool analyzeArgs(int, char* []);
    void printTitle();
    void printResponse();
}; 
#endif