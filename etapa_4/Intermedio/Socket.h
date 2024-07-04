#ifndef Socket_h
#define Socket_h

#include <arpa/inet.h>  // for inet_pton
#include <stdio.h>  // for perror
#include <stdlib.h>  // for exit
#include <string.h>  // for memset
#include <sys/socket.h>
#include <sys/types.h>  // for connect

#include "VSocket.h"

class Socket : public VSocket {

  public:
  Socket(char, bool = false);
  Socket(int);
  ~Socket();
  int Connect(const char*, int);
  int Connect(const char*, const char*);
  size_t Read(void*, size_t);
  size_t Write(const void*, size_t);
  size_t Write(const char*);
  Socket* Accept();

  protected:
};

#endif
