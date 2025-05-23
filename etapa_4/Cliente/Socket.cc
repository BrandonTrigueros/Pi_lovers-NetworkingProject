/**
 *   CI0123 PIRO
 *   Clase para utilizar los "sockets" en Linux
 *
 **/

#include "Socket.h"

/**
 *  Class constructor
 *     use Unix socket system call
 *
 *  @param	char type: socket type to define
 *     's' for stream
 *     'd' for datagram
 *  @param	bool ipv6: if we need a IPv6 socket
 *
 **/
Socket::Socket(char type, bool IPv6) { this->InitVSocket(type, IPv6); }

Socket::Socket(int id) { this->InitVSocket(id); }

/**
 * Class destructor
 *
 **/
Socket::~Socket() { Close(); }

/**
 * Close method
 *    use Unix close system call (once opened a socket is managed like a file in
 *Unix)
 *
 **/
void Socket::Close() { }

/**
 * Connect method
 *   use "connect" Unix system call
 *
 * @param	char * host: host address in dot notation, example
 *"10.1.104.187"
 * @param	int port: process address, example 80
 *
 **/
int Socket::Connect(const char* host, int port) {
  return this->DoConnect(host, port);
}

int Socket::Connect(const char* host, const char* service) {
  return this->DoConnect(host, service);
}

/**
 * Read method
 *   use "read" Unix system call (man 3 read)
 *
 * @param	void * text: buffer to store data read from socket
 * @param	int size: buffer capacity, read will stop if buffer is full
 *
 **/
size_t Socket::Read(void* text, size_t size) {
  int st = read(this->idSocket, text, size);
  if (-1 == st) {
    throw std::runtime_error("Socket::Read( const void *, size_t )");
  }
  return st;
}

/**
 * Write method
 *   use "write" Unix system call (man 3 write)
 *
 * @param	void * buffer: buffer to store data write to socket
 * @param	size_t size: buffer capacity, number of bytes to write
 *
 **/

size_t Socket::Write(const void* text, size_t size) {
  ssize_t st = write(this->idSocket, text, size);
  if (-1 == st) {
    throw std::runtime_error("Socket::Write( void *, size_t )");
  }
  return st;
}

/**
 * Write method
 *
 * @param	char * text: string to store data write to socket
 *
 *  This method write a string to socket, use strlen to determine how many bytes
 *
 **/

size_t Socket::Write(const char* text) {
  int st = -1;
  st = write(this->idSocket, text, strlen(text));
  if (-1 == st) {
    //      throw std::runtime_error( "Socket::Write( void *, size_t )" );
    throw std::runtime_error("Socket::Write( const char * )");
  }
  return st;

  /**
   * Accept method
   *    use base class to accept connections
   *
   *  @returns   a new class instance
   *
   *  Waits for a new connection to service (TCP mode: stream)
   *
   **/
}

Socket* Socket::Accept() {
  int id = this->DoAccept();
  if (id == -1) {
    throw std::runtime_error("Socket::Accept()");
    return NULL;
  } else {
    Socket* other = new Socket(id);
    return other;
  }
}
