/**
 *  Universidad de Costa Rica
 *  ECCI
 *  CI0123 Proyecto integrador de redes y sistemas operativos
 *  2023-ii
 *  Grupos: 2 y 3
 *
 * (versión Fedora)
 *
 **/
#ifndef VSocket_h
#define VSocket_h

#include <cstddef>
#include <cstdio>
#include <cstring>  // memset
#include <iostream>
#include <stdexcept>

#include <arpa/inet.h>  // ntohs
#include <sys/socket.h>
#include <unistd.h>  // close
// #include <sys/types.h>
#include <arpa/inet.h>
#include <cstddef>
#include <netdb.h>  // getaddrinfo, freeaddrinfo


class VSocket {
  protected:
  int idSocket;
  bool IPv6;
  int port;

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

  virtual int Bind(int);
  int Listen(int);
  int DoAccept();
  virtual VSocket* Accept() = 0;
  int Shutdown(int);

  size_t sendTo(const void* buffer, size_t size, void* addr);
  size_t recvFrom(void* buffer, size_t size, void* addr);

  inline int getSocketFd() { return this->idSocket; }
};

#endif  // VSocket_h
