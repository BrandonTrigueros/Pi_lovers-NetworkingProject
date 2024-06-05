/**
 *  Establece la definición de la clase Socket para efectuar la comunicación
 *  de procesos que no comparten memoria, utilizando un esquema de memoria
 *  distribuida.  El desarrollo de esta clase se hará en varias etapas, primero
 *  los métodos necesarios para los clientes, en la otras etapas los métodos para el servidor,
 *  manejo de IP-v6, conexiones seguras y otros
 *
 *  Universidad de Costa Rica
 *  ECCI
 *  CI0123 Proyecto integrador de redes y sistemas operativos
 *  2023-ii
 *  Grupos: 2
 *
 **/

#include "VSocket.h"

#include <iostream>
/**
  *  Class initializer
  *     use Unix socket system call
  *
  *  @param     char t: socket type to define
  *     's' for stream
  *     'd' for datagram
  *  @param     bool ipv6: if we need a IPv6 socket
  *
 **/
void VSocket::InitVSocket( char t, bool IPv6 ){
  this->IPv6 = IPv6;
  int domain = this->IPv6 ? AF_INET6 : AF_INET;
  int type = t == 's' ? SOCK_STREAM : SOCK_DGRAM;
  this->idSocket = socket(domain, type, 0);
}


/**
  *  Class initializer
  *     use Unix socket system call
  *
  *  @param     int id: descriptor for an already opened socket (accept)
  *
 **/
void VSocket::InitVSocket( int id ){
  this->idSocket = id;
}


/**
  * Class destructor
  *
 **/
VSocket::~VSocket() {
  this->Close();
}


/**
  * Close method
  *    use Unix close system call (once opened a socket is managed like a file in Unix)
  *
 **/
void VSocket::Close(){
  int st;
  if ( -1 == st ) {
    throw std::runtime_error( "Socket::Close()" );
  }
}


/**
  * DoConnect method
  *   use "connect" Unix system call
  *
  * @param      char * host: host address in dot notation, example "10.1.104.187"
  * @param      int port: process address, example 80
  *
 **/
int VSocket::DoConnect( const char * hostip, int port ) {
  int st;
  this->port = port;
  struct sockaddr_in  host4;
  memset( (char *) &host4, 0, sizeof( host4 ) );
  host4.sin_family = AF_INET;
  st = inet_pton( AF_INET, hostip, &host4.sin_addr );
  if ( -1 == st ) {
    throw( std::runtime_error( "VSocket::DoConnect, inet_pton" ));
  }
  host4.sin_port = htons( port );
  st = connect( idSocket, (sockaddr *) &host4, sizeof( host4 ) );
  if ( -1 == st ) {
    std::perror("connect failed");
    throw( std::runtime_error( "VSocket::DoConnect, connect" ));
  }
  return st;

}


/**
  * DoConnect method
  *   use "connect" Unix system call
  *
  * @param      char * host: host address in dns notation, example "os.ecci.ucr.ac.cr"
  * @param      char * service: process address, example "http"
  *
 **/
int VSocket::DoConnect( const char *host, const char *service ) {
  int st;

  if ( 0 == st ) {
  } else {
    throw std::runtime_error( gai_strerror( st ) );
  }

  return st;

}


/**
  * Listen method
  *
  * @param      int queue: max pending connections to enqueue (server mode)
  *
  *  This method define how many elements can wait in queue
  *
 **/
int VSocket::Listen( int queue ) {
  int st = listen( this->idSocket, queue/*length*/);

  if ( -1 == st ) {
    throw std::runtime_error( "VSocket::Listen( int )" );
  }

  return st;

}

/**
  * Bind method
  *    use "bind" Unix system call (man 3 bind) (server mode)
  *
  * @param      int port: bind a unamed socket to a port defined in sockaddr structure
  *
  *  Links the calling process to a service at port
  *
 **/
int VSocket::Bind( int port ) {
  int st;
  this->port = port;
  struct sockaddr_in server_addr;
  
  server_addr.sin_family = AF_INET;	// Definimos la familia para IPv4
  server_addr.sin_addr.s_addr = htonl( INADDR_ANY );	// Establecemos cualquier dirección
  server_addr.sin_port = htons( port );	// El puerto asociado al servicio
  
  size_t len = sizeof( server_addr );
  
  st = bind( this->idSocket, (const sockaddr *) & server_addr, len );

  if ( -1 == st ) {
    throw std::runtime_error( "VSocket::Bind( int )" );
  }

  return st;

}


/**
  * DoAccept method
  *    use "accept" Unix system call (man 3 accept) (server mode)
  *
  *  @returns   a new class instance
  *
  *  Waits for a new connection to service (TCP mode: stream)
  *
 **/
int VSocket::DoAccept(){
  struct sockaddr_in address;
  socklen_t address_len;
  
  int st = accept(this->idSocket, (sockaddr *)&address, &address_len);
  
  if ( -1 == st ) {
    throw std::runtime_error( "VSocket::DoAccept()" );
  }

  return st;

}


/**
  * Shutdown method
  *    use "shutdown" Unix system call (man 3 shutdown)
  *
  *  @param	int mode define how to cease socket operation
  *
  *  Partial close the connection (TCP mode)
  *
 **/
int VSocket::Shutdown( int mode ) {
  /*
    Modes:
    SHUT_RD: Disables further receive operations.
    SHUT_WR: Disables further send operations.
    SHUT_RDWR: Disables further send and receive operations.
  */
  int st = shutdown( this->idSocket, mode );

  if ( -1 == st ) {
    throw std::runtime_error( "VSocket::Shutdown( int )" );
  }

  return st;

}


/**
  *  sendTo method
  *
  *  @param	const void * buffer: data to send
  *  @param	size_t size data size to send
  *  @param	void * addr address to send data
  *
  *  Send data to another network point (addr) without connection (Datagram)
  *
 **/
size_t VSocket::sendTo( const void * buffer, size_t size, void * addr ) {
  return 0;
}


/**
  *  recvFrom method
  *
  *  @param	const void * buffer: data to send
  *  @param	size_t size data size to send
  *  @param	void * addr address to receive from data
  *
  *  @return	size_t bytes received
  *
  *  Receive data from another network point (addr) without connection (Datagram)
  *
 **/
size_t VSocket::recvFrom( void * buffer, size_t size, void * addr ) {
  return 0;
}
