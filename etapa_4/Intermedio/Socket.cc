
#include <stdexcept>   // exceptions
#include <stdio.h>     // for perror
#include <stdlib.h>    // for exit
#include <string.h>    // for memset
#include <arpa/inet.h> // for inet_pton
#include <sys/types.h> // for connect
#include <sys/socket.h>
#include <unistd.h> // for read & write

#include "Socket.h"

Socket::Socket(char type, bool IPv6) {
  this->InitVSocket(type, IPv6);
}

Socket::~Socket() {
  Close();
}

void Socket::Close() {
}

int Socket::Connect(const char *host, int port) {
  return this->DoConnect(host, port);
}

int Socket::Connect(const char *host, const char *service) {
  return this->DoConnect(host, service);
}

size_t Socket::Read(void *text, size_t size) {
  char *buffer = (char *)text;
  std::cout << "SIZE: " << size << std::endl;
  std::cout << "IDSOCKET: " << this->idSocket << std::endl;
  std::cout << "TEXT: " << buffer << std::endl;

  int read_result = read(this->idSocket, text, size);
  std::cout << "READ: " << read_result << std::endl; 
  if (read_result == -1) {
    throw std::runtime_error("Intermediate_Socket::Read( const void *, size_t )");
  }
  return read_result;
} // Puede correrlo un toque bro?

size_t Socket::Write(const void *text, size_t size) {
  int write_result = write(this->idSocket, text, size);
  std::cout << "WRITE: " << write_result << std::endl;
  if (write_result == -1) {
    throw std::runtime_error("Intermediate_Socket::Write( void *, size_t )");
  }
  return write_result;
}

size_t Socket::Write(const char *text) {
  int write_result = write(this->idSocket, text, strlen(text));
  if (write_result == -1) {
    perror("SSLSocket::Write");
    throw std::runtime_error("Intermediate_Socket::Write( const char *text )");
  }
  return write_result;
}

Socket *Socket::Accept() {
  int id;
  Socket *other;
  id = this->DoAccept();
  other = new Socket(id);
  return other;
}
