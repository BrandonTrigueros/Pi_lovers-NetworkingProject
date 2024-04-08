#ifndef CLIENTSIDE_H
#define CLIENTSIDE_H

#include <iostream>
#include <pthread.h>
#include <thread>
#include <unistd.h> // Include the header for sleep function
#include "ThreadData.h"

  void startSimulation();

  void createThreads(pthread_t, pthread_t, pthread_t);
  void initThreadsData(pthread_t, pthread_t, pthread_t);

  void* userRequest(void*);

#endif // CLIENT_SIDE_H