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

#include <cstddef>
#include <stdexcept>
#include <cstdio>
#include <cstring>			// memset

#include <sys/socket.h>
#include <arpa/inet.h>			// ntohs
#include <unistd.h>			// close
//#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>			// getaddrinfo, freeaddrinfo

#include "VSocket.h"


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
void VSocket::InitVSocket( char t, bool IPv6 ) {
   this->IPv6 = IPv6;
   int domain = this->IPv6 ? AF_INET6 : AF_INET;
   int type = t == 's' ? SOCK_STREAM : SOCK_DGRAM;
   this->idSocket = socket(domain, type, 0);
}


/**
  *  Class initializer
  *
  *  @param     int descriptor: socket descriptor for an already opened socket
  *
 **/
void VSocket::InitVSocket( int descriptor ) {

   this->idSocket = descriptor;

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
   int st = close(this->idSocket);

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
   /*
      This  function converts the character string src 
      into a network address structure in the af address family, 
      then copies the network address structure to dst
   */
   st = inet_pton( AF_INET, hostip, &host4.sin_addr );
   if ( -1 == st ) {
      throw( std::runtime_error( "VSocket::DoConnect, inet_pton" ));
   }
   host4.sin_port = htons( port );
   st = connect( idSocket, (sockaddr *) &host4, sizeof( host4 ) );
   if ( -1 == st ) {
      throw( std::runtime_error( "VSocket::DoConnect, connect" ));
   }
   return st;
}


/**
  * DoConnect method
  *   use "connect" Unix system call
  *
  * @param      const char * host: host address 
  * @param      const char * service, service name, example "http"
  *
 **/
int VSocket::DoConnect( const char * hostip, const char * service ) {
   int st;

   struct addrinfo hints, *result, *rp;

   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
   hints.ai_socktype = SOCK_STREAM; /* Stream socket */
   hints.ai_flags = 0;
   hints.ai_protocol = 0;          /* Any protocol */
   
   st = getaddrinfo( hostip, service, &hints, &result );

   for ( rp = result; rp; rp = rp->ai_next ) {
      st = connect( this->idSocket, rp->ai_addr, rp->ai_addrlen );
      if ( 0 == st )
         break;
   }

   freeaddrinfo( result );

   if ( -1 == st ) {
      perror( "VSocket::connect" );
      throw std::runtime_error( "VSocket::DoConnect" );
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
   // bind -> assign a local socket address address to a socket 
   int st;
   struct sockaddr_in  host4;
   host4.sin_family = AF_INET;
   host4.sin_addr.s_addr = htonl( INADDR_ANY );
   host4.sin_port = htons( port );
   memset(host4.sin_zero, '\0', sizeof (host4.sin_zero));
   st = bind(this->idSocket, (sockaddr *) &host4, sizeof(host4));

   if ( -1 == st ) {
      throw( std::runtime_error( "VSocket::Bind()" ));
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
   // sendto -> send a message on a socket
   int st = sendto(this->idSocket, buffer, size, 0, (sockaddr *)addr, sizeof(*((sockaddr*)addr)));

   if ( -1 == st ) {
      throw( std::runtime_error( "VSocket::sendTo()" ));
   }

   return st;
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
   // recvfrom -> places the received message into the buffer buf
   socklen_t addrlen = sizeof(*((sockaddr*)addr));
   int st = recvfrom(this->idSocket, buffer, size, 0, (sockaddr *)addr, &addrlen);

   if ( -1 == st ) {
      throw( std::runtime_error( "VSocket::recvFrom()" ));
   }

   return st;
}

