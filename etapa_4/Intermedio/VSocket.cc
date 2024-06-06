#include <cstddef>
#include <stdexcept>
#include <cstdio>
#include <cstring> // memset
#include <sys/socket.h>
#include <arpa/inet.h> // ntohs
#include <unistd.h>    // close
#include <arpa/inet.h>
#include <netdb.h> // getaddrinfo, freeaddrinfo

#include "VSocket.h"


void VSocket::InitVSocket(char t, bool IPv6){
  this->IPv6 = IPv6;
  int domain = this->IPv6 ? AF_INET6 : AF_INET;
  int type = t == 's' ? SOCK_STREAM : SOCK_DGRAM;
  this->idSocket = socket(domain, type, 0);
}

void VSocket::InitVSocket(int descriptor) {
  this->idSocket = descriptor;
}

VSocket::~VSocket() {
  this->Close();
}

void VSocket::Close(){
  int close_operation = close(this->idSocket);
  if (close_operation == -1){
    throw std::runtime_error("Socket::Close()");
  }
}

int VSocket::DoConnect(const char *hostip, int port) {
  int connect_operation;
  this->port = port;
  struct sockaddr_in host4;
  memset((char *)&host4, 0, sizeof(host4));
  host4.sin_family = AF_INET;
  connect_operation = inet_pton(AF_INET, hostip, &host4.sin_addr);
  if (connect_operation == -1) {
    throw(std::runtime_error("VSocket::DoConnect, inet_pton"));
  }
  host4.sin_port = htons(port);
  connect_operation = connect(idSocket, (sockaddr *)&host4, sizeof(host4));
  if (connect_operation == -1) {
    throw(std::runtime_error("VSocket::DoConnect, connect"));
  }
  return connect_operation;
}

int VSocket::DoConnect(const char *hostip, const char *service) {
  int connect_operation;
  struct addrinfo hints, *result, *rp;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;     /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* Stream socket */
  hints.ai_flags = 0;
  hints.ai_protocol = 0; /* Any protocol */
  connect_operation = getaddrinfo(hostip, service, &hints, &result);
  for (rp = result; rp; rp = rp->ai_next) {
    connect_operation = connect(this->idSocket, rp->ai_addr, rp->ai_addrlen);
    if (connect_operation == 0) {
      break;
    }
  }
  freeaddrinfo(result);
  if (connect_operation == -1){
    perror("VSocket::connect");
    throw std::runtime_error("VSocket::DoConnect");
  }
  return connect_operation;
}

int VSocket::Bind(int port) {
  int bind_operation;
  struct sockaddr_in host4;
  host4.sin_family = AF_INET;
  host4.sin_addr.s_addr = htonl(INADDR_ANY);
  host4.sin_port = htons(port);
  memset(host4.sin_zero, '\0', sizeof(host4.sin_zero));
  bind_operation = bind(this->idSocket, (sockaddr *)&host4, sizeof(host4));
  if (bind_operation == -1) {
    throw(std::runtime_error("VSocket::Bind()"));
  }
  return bind_operation;
}

size_t VSocket::sendTo(const void *buffer, size_t size, void *addr) {
  int send_result = sendto(this->idSocket, buffer, size, 0, (sockaddr *)addr, sizeof(*((sockaddr *)addr)));
  if (send_result == -1) {
    throw(std::runtime_error("VSocket::sendTo()"));
  }
  return send_result;
}

size_t VSocket::recvFrom(void *buffer, size_t size, void *addr) { 
  socklen_t addrlen = sizeof(*((sockaddr *)addr));
  int recv_result = recvfrom(this->idSocket, buffer, size, 0, (sockaddr *)addr, &addrlen);
  if (recv_result == -1) {
    throw(std::runtime_error("VSocket::recvFrom()"));
  }
  return recv_result;
}
