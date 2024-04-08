#ifndef THREADDATA_H
#define THREADDATA_H

#include <iostream> 
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

// Shared data structure
struct sharedData {
  std::string userRequest;
  std::string legoPart;
  std::string serverResponse;
  sem_t userSemaphore;
  sem_t intermediateSemaphore;
  sem_t serverSemaphore;
  bool closeIntermediateServer;
  bool closeServer;
};

// Private data structure
struct privateData {
  sharedData* sData;
};

#endif // THREADDATA_H

