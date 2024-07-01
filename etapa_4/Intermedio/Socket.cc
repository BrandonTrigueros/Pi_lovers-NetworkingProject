#include "Socket.h"

Socket::Socket(char type, bool IPv6) { this->InitVSocket(type, IPv6); }

Socket::Socket(int id) { this->InitVSocket(id); }

Socket::~Socket() { Close(); }

int Socket::Connect(const char* host, int port) {

  return this->DoConnect(host, port);
}

int Socket::Connect(const char* host, const char* service) {
  return this->DoConnect(host, service);
}

size_t Socket::Read(void* text, size_t size) {
  int read_result = read(this->idSocket, text, size);
  if (-1 == read_result) {
    throw std::runtime_error("Socket::Read( const void *, size_t )");
  }
  return read_result;
}

size_t Socket::Write(const void* text, size_t size) {
  int write_result = write(this->idSocket, text, size);
  if (-1 == write_result) {
    throw std::runtime_error("Socket::Write( void *, size_t )");
  }

  return write_result;
}

size_t Socket::Write(const char* text) {
  int write_result = write(this->idSocket, text, strlen(text));

  if (-1 == write_result) {
    throw std::runtime_error("Socket::Write( void *, size_t )");
  }

  return write_result;
}

// socket, subnet, bind, broadcast

size_t Socket::Broadcast(char* message, size_t size) {
  struct sockaddr_in host4;
  memset((char*)&host4, 0, sizeof(host4));
  host4.sin_family = AF_INET;
  host4.sin_port = htons(this->port);
  host4.sin_addr.s_addr
      = inet_addr("172.16.123.79");  // Dirección de broadcast para tu isla
  char broadcast = '1';
  int st = setsockopt(
      this->idSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));
  if (0 > st) {
    throw std::runtime_error("Socket::Broadcast( char *, size_t )");
  }
  st = sendto(this->idSocket, message, size, 0, (struct sockaddr*)&host4,
      sizeof(host4));
  if (st < 0) {
    throw std::runtime_error("Error sending broadcast message");
  }
  return st;

  //? recieve
}

size_t Socket::ListenBroadcast(char* buffer, size_t size) {
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  int broadcast = 1;
  if (setsockopt(
          idSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))
      < 0) {
    throw std::runtime_error("Error setting broadcast option");
  }
  if (bind(idSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    throw std::runtime_error("Error binding socket");
  }

  while (true) {
    socklen_t addrLen = sizeof(addr);
    ssize_t recvLen = recvfrom(idSocket, buffer, sizeof(buffer) - 1, 0,
        (struct sockaddr*)&addr, &addrLen);
  }
}

Socket* Socket::Accept() {
  int id;
  Socket* other;

  id = this->DoAccept();

  other = new Socket(id);

  return other;
}