/**
 *
 **/

#ifndef VSocket_h
#define VSocket_h

#include <cstddef>
#include <cstdio>
#include <cstring>  // memset
#include <stdexcept>

#include <arpa/inet.h>  // ntohs
#include <sys/socket.h>
#include <unistd.h>  // close
// #include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>  // getaddrinfo, freeaddrinfo

class VSocket {
  public:
  void InitVSocket(char, bool = false);
  void InitVSocket(int);
  ~VSocket();

  void Close();
  int DoConnect(const char*, int);
  int DoConnect(const char*, const char*);
  virtual int Connect(const char*, int) = 0;
  virtual int Connect(const char*, const char*) = 0;

  virtual size_t Read(void*, size_t) = 0;
  virtual size_t Write(const void*, size_t) = 0;
  virtual size_t Write(const char*) = 0;
  virtual size_t Broadcast(char* message, size_t size) = 0;
  int Listen(int);
  int Bind(int);
  int DoAccept();
  virtual VSocket* Accept() = 0;
  int Shutdown(int);
  size_t sendTo(const void*, size_t, void*);
  size_t recvFrom(void*, size_t, void*);

  protected:
  int idSocket;
  bool IPv6;
  int port;
};

#endif  // VSocket_h
