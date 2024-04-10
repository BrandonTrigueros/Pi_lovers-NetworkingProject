#include "IntermediateServerSide.h"

#define REDTEXT "\033[1;31m"
#define GREENTEXT "\033[1;32m"
#define CYANTEXT "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define RESET "\033[0m"

void* intermediateServer(void* data) {
  privateData* pData = (privateData*) data;
  sharedData* sData = pData->sData;

  while (!sData->closeIntermediateServer) {
    sem_wait(&sData->intermediateSemaphore);
    if (sData->closeServer) {
      sData->closeIntermediateServer = true;
    } else {
      std::cout << CYANTEXT << " - Sending request to the server - " << RESET << std::endl;
    }
    sem_post(&sData->serverSemaphore);
    sem_wait(&sData->intermediateSemaphore);
    sem_post(&sData->userSemaphore);
  }
  
  return nullptr;
}
