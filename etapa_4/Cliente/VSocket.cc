/**
 *  Establece la definición de la clase Socket para efectuar la comunicación
 *  de procesos que no comparten memoria, utilizando un esquema de memoria
 *  distribuida.  El desarrollo de esta clase se hará en varias etapas, primero
 *  los métodos necesarios para los clientes, en la otras etapas los métodos
 *para el servidor, manejo de IP-v6, conexiones seguras y otros
 *
 *  Universidad de Costa Rica
 *  ECCI
 *  CI0123 Proyecto integrador de redes y sistemas operativos
 *  2023-ii
 *  Grupos: 2 y 3
 *
 * (versión Fedora)
 *zzzzzy
 **/

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
#include <netdb.h>  // getaddrinfo, freeaddrinfo

#include "VSocket.h"


void VSocket::InitVSocket(char t, bool IPv6) {
  int st;
  int domain = (IPv6) ? AF_INET6 : AF_INET;
  int type = (t == 's') ? SOCK_STREAM : SOCK_DGRAM;
  // create with O_NONBLOCK
  st = socket(domain, type, 0);
  if (-1 == st) {
    throw std::runtime_error("VSocket::InitVSocket");
    return;
  }
  this->idSocket = st;
  this->IPv6 = IPv6;
  int optval = 1;
  if (setsockopt(this->idSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
    perror("setsockopt");
  }
}


void VSocket::InitVSocket(int id) {
  struct sockaddr_in address;
  socklen_t len = sizeof(address);

  if (getsockname(id, (struct sockaddr*)&address, &len) == -1) {
    throw std::runtime_error("VSocket::InitVSocket(fd)");
  } else {
    // this->port = ntohs(address.sin_port);
    this->IPv6 = (address.sin_family == AF_INET6);
    this->idSocket = id;
  }
  // this->idSocket = id;
  // this->IPv6 = false;
}


VSocket::~VSocket() { this->Close(); }


void VSocket::Close() {
  // if its already closed, return
  if (-1 == this->idSocket) {
    throw std::runtime_error("VSocket::Close");
    return;
  }
  int st;
  st = close(this->idSocket);
  if (-1 == st) {
    throw std::runtime_error("VSocket::Close");
  }
}


int VSocket::DoConnect(const char* hostip, int port) {
  int st;
  struct sockaddr_in host4;
  memset((char*)&host4, 0, sizeof(host4));
  host4.sin_family = AF_INET;
  st = inet_pton(AF_INET, hostip, &host4.sin_addr);
  if (-1 == st) {
    throw(std::runtime_error("VSocket::DoConnect, inet_pton"));
  }
  host4.sin_port = htons(port);
  st = connect(idSocket, (sockaddr*)&host4, sizeof(host4));
  if (-1 == st) {
    throw(std::runtime_error("VSocket::DoConnect, connect"));
  }
  return st;
}

int VSocket::DoConnect(const char* hostip, const char* service) {
  // Para IPv6
  struct addrinfo hints, *res, *rp;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;  // Allow IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;  // Stream socket
  hints.ai_flags = 0;
  hints.ai_protocol = 0;  // Any protocol
  int st = getaddrinfo(hostip, service, &hints, &res);
  if (st != 0) {
    std::cout << "getaddrinfo: " << gai_strerror(st) << std::endl;
    throw std::runtime_error("VSocket::DoConnect, getaddrinfo");
  }
  for (rp = res; rp != NULL; rp = rp->ai_next) {
    st = connect(this->idSocket, rp->ai_addr, rp->ai_addrlen);
    // print port
    if (0 != st) {
      break;
    }
  }
  freeaddrinfo(res);
  return st;
}


int VSocket::Bind(int port) {
  int st;
  if (this->IPv6) {
    struct sockaddr_in6 server;
    memset(&server, 0, sizeof(server));
    server.sin6_family = AF_INET6;  // IPv6
    server.sin6_addr = in6addr_loopback;  // Any address
    server.sin6_port = htons(port);  // Port
    int len = sizeof(server);
    st = bind(this->idSocket, (struct sockaddr*)&server, len);
  } else {
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;  // IPv4
    server.sin_addr.s_addr = htonl(INADDR_ANY);  // Any address
    server.sin_port = htons(port);  // Port
    int len = sizeof(server);
    st = bind(this->idSocket, (struct sockaddr*)&server, len);
  }
  if (st == -1) {
    throw std::runtime_error("VSocket::Bind");
  }
  return st;
}


int VSocket::Listen(int queue_len) {
  int st = -1;
  st = listen(this->idSocket, queue_len);
  if (st == -1) {
    throw std::runtime_error("VSocket::Listen( int )");
  }
  return st;
}


int VSocket::DoAccept() {
  int st = -1;
  st = accept(this->idSocket, NULL, NULL);
  if (st == -1) {
    throw std::runtime_error("VSocket::DoAccept()");
  }
  return st;
}


int VSocket::Shutdown(int mode) {
  int st = -1;
  st = shutdown(this->idSocket, mode);
  if (st == -1) {
    throw std::runtime_error("VSocket::Shutdown( int )");
  }
  return st;
}

size_t VSocket::sendTo(const void* buffer, size_t size, void* addr) {
  int st = -1;
  socklen_t addr_len;
  this->IPv6 ? addr_len = sizeof(struct sockaddr_in6)
             : addr_len = sizeof(struct sockaddr_in);
  st = sendto(
      this->idSocket, buffer, size, 0, (struct sockaddr*)addr, addr_len);
  if (-1 == st) {
    throw std::runtime_error("VSocket::sendTo");
  } else {
    return st;
  }
}

size_t VSocket::recvFrom(void* buffer, size_t size, void* addr) {
  int st = -1;
  socklen_t addr_len;
  this->IPv6 ? addr_len = sizeof(struct sockaddr_in6)
             : addr_len = sizeof(struct sockaddr_in);
  st = recvfrom(
      this->idSocket, buffer, size, 0, (struct sockaddr*)addr, &addr_len);
  if (-1 == st) {
    throw std::runtime_error("VSocket::recvFrom");
  } else {
    return st;
  }
}