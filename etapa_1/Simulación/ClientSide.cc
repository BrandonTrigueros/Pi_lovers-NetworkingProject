#include "ClientSide.h"
#include "IntermediateServerSide.h"
#include "ServerSide.h"

void startSimulation() {
  pthread_t clientThread, intermediateThread, serverThread;
  clientThread = 0;
  intermediateThread = 0;
  serverThread = 0;
  initThreadsData(clientThread, intermediateThread, serverThread);
}

void initThreadsData(pthread_t clientThread, pthread_t intermediateThread, pthread_t serverThread) {
  sharedData* sData = new sharedData;
  sData->userRequest = "";
  sData->serverResponse = "";
  sem_init(&sData->userSemaphore, 0, 1);
  sem_init(&sData->intermediateSemaphore, 0, 0);
  sem_init(&sData->serverSemaphore, 0, 0);
  sData->closeIntermediateServer = false;
  sData->closeServer = false;
  
  // Create the threads
  privateData clientData, intermediateData, serverData;
  clientData = {sData};
  intermediateData = {sData};
  serverData = {sData};

  pthread_create(&clientThread, nullptr, userRequest, &clientData);
  pthread_create(&intermediateThread, NULL, intermediateServer, &intermediateData);
  pthread_create(&serverThread, NULL, server, &serverData);

  // Detach client and intermediate threads
  pthread_join(clientThread, NULL);
  pthread_join(intermediateThread, NULL);

  // Wait for the server thread to finish
  pthread_join(serverThread, NULL);

  sem_destroy(&sData->userSemaphore);
  sem_destroy(&sData->intermediateSemaphore);
  sem_destroy(&sData->serverSemaphore);
  delete sData;
}

#define REDTEXT "\033[1;31m"
#define GREENTEXT "\033[1;32m"
#define CYANTEXT "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define RESET "\033[0m"

void* userRequest(void* data) {
  privateData* pData = (privateData*) data;
  sharedData* sData = pData->sData;
  std::string userInput = "";
  std::string legoPart = "";

  system("clear");
  do {
    std::cout << MAGENTA <<"     Welcome to the LEGO server!" << RESET << std::endl << std::endl;
    std::cout << "Enter a request or q to exit: ";
    std::getline(std::cin, userInput);
    sData->userRequest = userInput;

    if (sData->userRequest == "q" || sData->userRequest == "Q") {
      sData->closeServer = true;
      sem_post(&sData->intermediateSemaphore);
      break;
    }

    std::cout << "Enter first/second/full according to the part you wish to view: ";
    std::getline(std::cin, legoPart);
    sData->legoPart = legoPart;

    std::cout << std::endl <<  CYANTEXT << " - Request sent to the intermediate server -" << RESET << std::endl;
    sem_post(&sData->intermediateSemaphore);
    sem_wait(&sData->userSemaphore);

    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    std::cout <<  CYANTEXT << " - Obtaining the response from the server -" << RESET << std::endl;
    std::cout << sData->serverResponse << std::endl;

  } while (!sData->closeServer);

  return nullptr;
}

