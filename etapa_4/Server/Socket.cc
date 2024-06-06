#include "Socket.h"

Socket::Socket(char type, bool IPv6) {
  this->InitVSocket(type, IPv6);
}

Socket::Socket(int id) {
  this->InitVSocket(id);
}

Socket::~Socket() {
  Close();
}

int Socket::Connect(const char *host, int port) {
  return this->DoConnect(host, port);
}

int Socket::Connect(const char *host, const char *service) {
  return this->DoConnect(host, service);
}

size_t Socket::Read(void *text, size_t size) {
  int read_result = read(this->idSocket, text, size);
  if (read_result == -1) {
    throw std::runtime_error("Socket::Read( const void *, size_t )");
  }
  return read_result;
}

size_t Socket::Write(const void *text, size_t size) {
  int write_result = write(this->idSocket, text, size);
  if (write_result == -1) {
    throw std::runtime_error("Socket::Write( void *, size_t )");
  }
  return write_result;
}

size_t Socket::Write(const char *text) {
  int write_result = write(this->idSocket, text, strlen(text));
  if (write_result == -1) {
    throw std::runtime_error("Socket::Write( void *, size_t )");
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