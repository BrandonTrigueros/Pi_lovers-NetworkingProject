#include "Intermediate.h"

Intermediate::Intermediate() {
  this->userRequest = nullptr;
  this->requestQueue = new RequestQueue();
  requestQueue->initQueue(this->requestQueue);

  this->responseQueue = new ResponseQueue();
  responseQueue->initQueue(this->responseQueue);
}

Intermediate::~Intermediate() { }

void Intermediate::run() {
  listenIntermidiateBroadcast();
  intermediateServer_UDP();
  broadcastNewServer();
  // listenClient();
}

void Intermediate::listenIntermidiateBroadcast() { }

int Intermediate::broadcastNewServer() { }

void Intermediate::intermediateServer_UDP() {
  VSocket* intermediate;
  int numBytes;
  char buffer[BUFFER_SIZE];
  char* message = (char*)"Connection request";
  struct sockaddr_in intermediateInfo;

  intermediate = new Socket('d');
  memset(&intermediateInfo, 0, sizeof(intermediateInfo));
  intermediateInfo.sin_family = AF_INET;
  intermediateInfo.sin_port = htons(UDP_PORT_SERVER);
  intermediateInfo.sin_addr.s_addr = INADDR_ANY;

  bool isConnected = false;
  while (!isConnected) {
    numBytes = intermediate->sendTo(
        (void*)message, strlen(message), (void*)&intermediateInfo);
    std::cout << "Sent data: " << message << std::endl;
    numBytes = intermediate->recvFrom(
        (void*)buffer, BUFFER_SIZE, (void*)&intermediateInfo);
    buffer[numBytes] = '\0';
    if (numBytes > 0) {
      std::cout << "Received data: " << buffer << std::endl;
      isConnected = true;
    }
  }

  intermediate->Close();
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
    worker = new std::thread(handleClient, (void*)client, this->requestQueue);
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