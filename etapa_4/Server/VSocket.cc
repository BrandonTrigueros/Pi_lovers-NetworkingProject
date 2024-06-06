#include "VSocket.h"
#include <iostream>

void VSocket::InitVSocket(char t, bool IPv6) {
  this->IPv6 = IPv6;
  int domain = this->IPv6 ? AF_INET6 : AF_INET;
  int type = t == 's' ? SOCK_STREAM : SOCK_DGRAM;
  this->idSocket = socket(domain, type, 0);
}

void VSocket::InitVSocket(int id) {
  this->idSocket = id;
}

VSocket::~VSocket() {
  this->Close();
}

void VSocket::Close() {
  int close_result;
  if (close_result == -1) {
    throw std::runtime_error("Socket::Close()");
  }
}

int VSocket::DoConnect(const char *hostip, int port) {
  int connect_result;
  this->port = port;
  struct sockaddr_in host4;
  memset((char *)&host4, 0, sizeof(host4));
  host4.sin_family = AF_INET;
  connect_result = inet_pton(AF_INET, hostip, &host4.sin_addr);
  if (connect_result == -1) {
    throw(std::runtime_error("VSocket::DoConnect, inet_pton"));
  }
  host4.sin_port = htons(port);
  connect_result = connect(idSocket, (sockaddr *)&host4, sizeof(host4));
  if (connect_result == -1) {
    std::perror("connect failed");
    throw(std::runtime_error("VSocket::DoConnect, connect"));
  }
  return connect_result;
}

int VSocket::DoConnect(const char *host, const char *service) {
  int connect_result;
  if (connect_result == 0) {
  } else {
    throw std::runtime_error(gai_strerror(connect_result));
  }
  return connect_result;
}

int VSocket::Listen(int queue) {
  int listen_result = listen(this->idSocket, queue /*length*/);
  if (listen_result == -1) {
    throw std::runtime_error("VSocket::Listen( int )");
  }
  return listen_result;
}

int VSocket::Bind(int port) {
  int bind_result;
  this->port = port;
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;                // Definimos la familia para IPv4
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Establecemos cualquier dirección
  server_addr.sin_port = htons(port);              // El puerto asociado al servicio
  size_t len = sizeof(server_addr);
  bind_result = bind(this->idSocket, (const sockaddr *)&server_addr, len);
  if (bind_result == -1) {
    throw std::runtime_error("VSocket::Bind( int )");
  }
  return bind_result;
}

int VSocket::DoAccept() {
  struct sockaddr_in address;
  socklen_t address_len;
  int accept_resutl = accept(this->idSocket, (sockaddr *)&address, &address_len);
  if (accept_resutl == -1) {
    throw std::runtime_error("VSocket::DoAccept()");
  }
  return accept_resutl;
}

int VSocket::Shutdown(int mode) {
  int shutdown_result = shutdown(this->idSocket, mode);
  if (shutdown_result == -1) {
    throw std::runtime_error("VSocket::Shutdown( int )");
  }
  return shutdown_result;
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
