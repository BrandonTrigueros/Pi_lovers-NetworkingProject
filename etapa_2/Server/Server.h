#ifndef Server_h
#define Server_h

#include "Socket.h"
#include "FileManager.h"

#include <thread>
#include <unistd.h>
#include <algorithm> // transform

#define PORT 1233
#define BUFSIZE 512
class Server {

  public:
    Server() = default;
    ~Server() = default;
    void Run( );
  private:
  static void task( void * data );
  static std::string getFigure(std::string userRequest);
  static std::string getPiece(std::string userRequest);
  static bool isNachOS(std::string); 

};

#endif