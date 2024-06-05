#include "Intermediate.h"

void Intermediate::run() {
  // Se conecta al servidor
  connectServer();
  // Escucha al servidor
  // listenServer();
  // Escucha a los clientes
  // listerClient();
}

void Intermediate::connectServer() {
  VSocket * intermediate;
  int st;

  struct sockaddr_in other;
  memset( &other, 0, sizeof( other ) );
  other.sin_family = AF_INET;
  other.sin_port = htons(PORT);
  other.sin_addr.s_addr = INADDR_ANY;
  char buffer[MAX];
  char *hello = (char *) "New intermediate severs is up and running";

  // Creates a socket
  intermediate = new Socket('d');
  // Connects to the server
  st = intermediate->sendTo((void *) hello, strlen(hello), (void *) &other);
  printf("Message sent.\n");

  // Receives a message from the server
  st = intermediate->recvFrom( (void *) buffer, MAX, (void *) & other );
  buffer[st] = '\0';
  printf("Message received: %s\n", buffer); // ToDo: comment this line

  intermediate->Close();
}

void Intermediate::listenServer() {

}

void Intermediate::listerClient() {
  
}