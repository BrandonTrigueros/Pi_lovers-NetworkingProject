#include "Client.h"

int main(int argc, char* argv[]) {
  Client client;
  if (client.createSocket(argc, argv)) {
    client.printTitle();
    client.run();
    client.printResponse();
  }
  return 0;  
}