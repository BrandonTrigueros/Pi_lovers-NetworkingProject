#include "Intermediate.h"

Intermediate::Intermediate() {
  this->userRequest = nullptr;
  this->request_queue = new RequestQueue();
  request_queue->initQueue(request_queue);
}

Intermediate::~Intermediate() {
 
}


void Intermediate::clientIntermediate() {
  // listen Client
  // receiveTCP
  // sendTCP
}

void Intermediate::run() {
  listenClient();
}

void Intermediate::listenClient() {
  std::thread* worker;
  VSocket *intermediateSocket, *client;
  std::cout << "Master intermediate server is running" << std::endl;
  intermediateSocket = new Socket('s');
  intermediateSocket->Bind(CLIENT_PORT);
  intermediateSocket->Listen(5);  // Set backlog queue to 5 conections

  while (true) {
    client = intermediateSocket->Accept();
    worker = new std::thread(handleClient, (void*)client, this->request_queue);
  }
  worker->join();
}


void Intermediate::handleClient(void* socket, RequestQueue* request_queue) {
  char userRequest[BUFFER_SIZE];
  VSocket* client = (VSocket*)socket;
  client->Read(userRequest, BUFFER_SIZE);
  std::cout << userRequest << std::endl;
  request_queue->enqueue(request_queue, userRequest);
  std::string response = "Connection handled";
  request_queue->dequeue(request_queue, userRequest);
  client->Write(response.c_str());
  client->Close();
}



