#include "Client.h"

int main(int argc, char* argv[]) {
  Client client;
  if (client.analyzeArgs(argc, argv)) {
    client.run();
  }
  return 0;
}