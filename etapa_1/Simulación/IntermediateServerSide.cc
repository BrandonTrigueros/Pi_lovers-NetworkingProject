#include "IntermediateServerSide.h"

#define REDTEXT "\033[1;31m"
#define GREENTEXT "\033[1;32m"
#define CYANTEXT "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define RESET "\033[0m"

std::string protocolRequest = "http://legoFigures/get-";

void* intermediateServer(void* data) {
  privateData* pData = (privateData*) data;
  sharedData* sData = pData->sData;

  while (!sData->closeIntermediateServer) {
    sem_wait(&sData->intermediateSemaphore);
    
    sData->userRequest = protocolRequest + sData->userRequest + "-" + sData->legoPart;
    if (sData->closeServer) {
      sData->closeIntermediateServer = true;
      sem_post(&sData->serverSemaphore);
      break;
    } else {
      std::cout << CYANTEXT << " - Sending request " << "\033[1;34m" << "\033[4m" << sData->userRequest << RESET <<  CYANTEXT << " to the server - " << RESET << std::endl;
    }
    sem_post(&sData->serverSemaphore);
  }
  
  return nullptr;
}
