#ifndef Server_h
#define Server_h

#include "Socket.h"
#include "FileManager.h"
#include <thread>

#define PORT 1233
#define BUFSIZE 512
class Server {

  public:
    Server() = default;
    ~Server() = default;
    void Run( );
  private:
    static void task( void * data );

};

#endif