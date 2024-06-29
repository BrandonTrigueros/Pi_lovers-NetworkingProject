#include "VSocket.h"
#include <iostream>

void VSocket::InitVSocket(char t, bool IPv6) {
  this->IPv6 = IPv6;
  int domain = this->IPv6 ? AF_INET6 : AF_INET;
  int type = t == 's' ? SOCK_STREAM : SOCK_DGRAM;
  this->idSocket = socket(domain, type, 0);
  int timeout_sec = 5;
  struct timeval timeout;
  timeout.tv_sec = timeout_sec;
  timeout.tv_usec = 0;
  if (setsockopt(this->idSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
    perror("Timeout set failed\n");
    this->Close();
  }
  int optval = 1;
  if (setsockopt(this->idSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
    perror("setsockopt");
  }
}

void VSocket::InitVSocket(int id) { this->idSocket = id; }

VSocket::~VSocket() { this->Close(); }

void VSocket::Close() {
  int close_operation = close(this->idSocket);
  if (-1 == close_operation) {
    throw std::runtime_error("Socket::Close()");
  }
}

int VSocket::DoConnect(const char* hostip, int port) {
  int st;
  this->port = port;
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
    std::perror("connect failed");
    throw(std::runtime_error("VSocket::DoConnect, connect"));
  }
  return st;
}

int VSocket::DoConnect(const char* host, const char* service) {
  int connect_result = 0;
  if (0 == connect_result) {
  } else {
    throw std::runtime_error(gai_strerror(connect_result));
  }
  return connect_result;
}

int VSocket::Listen(int queue) {
  int listen_result = listen(this->idSocket, queue /*length*/);
  if (-1 == listen_result) {
    throw std::runtime_error("VSocket::Listen( int )");
  }
  return listen_result;
}

int VSocket::Bind(int port) {
  int bind_result;
  this->port = port;
  struct sockaddr_in server_addr;

  server_addr.sin_family = AF_INET;  // Definimos la familia para IPv4
  server_addr.sin_addr.s_addr
      = htonl(INADDR_ANY);  // Establecemos cualquier dirección
  server_addr.sin_port = htons(port);  // El puerto asociado al servicio

  size_t len = sizeof(server_addr);

  bind_result = bind(this->idSocket, (const sockaddr*)&server_addr, len);

  if (-1 == bind_result) {
    throw std::runtime_error("VSocket::Bind( int )");
  }

  return bind_result;
}

int VSocket::DoAccept() {
  struct sockaddr_in address;
  socklen_t address_len;
  int st = -1;
  while (st == -1) {
    st = accept(this->idSocket, (sockaddr *)&address, &address_len);
    std::cout << "Im listening TCP" << std::endl;
  }

  return st;
}

int VSocket::Shutdown(int mode) {
  /*
    Modes:
    SHUT_RD: Disables further receive operations.
    SHUT_WR: Disables further send operations.
    SHUT_RDWR: Disables further send and receive operations.
  */
  int st = shutdown(this->idSocket, mode);

  if (-1 == st) {
    throw std::runtime_error("VSocket::Shutdown( int )");
  }

  return st;
}

size_t VSocket::sendTo(const void* buffer, size_t size, void* addr) {
  int send_result = sendto(this->idSocket, buffer, size, 0, (sockaddr*)addr,
      sizeof(*((sockaddr*)addr)));
  if (-1 == send_result) {
    throw(std::runtime_error("VSocket::sendTo()"));
  }
  return send_result;
}

size_t VSocket::recvFrom(void* buffer, size_t size, void* addr) {
  socklen_t addrlen = sizeof(*((sockaddr*)addr));
  int recv_result
      = recvfrom(this->idSocket, buffer, size, 0, (sockaddr*)addr, &addrlen);
  return recv_result;
}
