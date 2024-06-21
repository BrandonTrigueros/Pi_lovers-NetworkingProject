#include "Intermediate.h"

Intermediate::Intermediate()
{
  this->userRequest = nullptr;
  this->requestQueue = new RequestQueue();
  requestQueue->initQueue(this->requestQueue);

  this->responseQueue = new ResponseQueue();
  responseQueue->initQueue(this->responseQueue);
}

Intermediate::~Intermediate()
{
}

void Intermediate::clientIntermediate()
{
  // listen Client
  // receiveTCP
  // sendTCP
}

void Intermediate::run() {
  // listenClient();
  intermediateServer_UDP();
  std::cout << "Connection established UDP" << std::endl;

  while (true) {
    // ToDo: Implement sempahore
    if (this->requestQueue->isEmpty(this->requestQueue)) {
      std::cout << "Waiting for request" << std::endl;
      std::cout << "After response: Request received" << std::endl;
    }
    sendTCPRequest(this->requestQueue);
  }
}

void Intermediate::listenClient() {
  std::thread *worker;
  VSocket *intermediateSocket, *client;
  std::cout << "Master intermediate server is running" << std::endl;
  intermediateSocket = new Socket('s');
  intermediateSocket->Bind(CLIENT_PORT);
  intermediateSocket->Listen(5); // Set backlog queue to 5 conections

  while (true)
  {
    client = intermediateSocket->Accept();
    worker = new std::thread(handleClient, (void *)client, this->requestQueue);
  }
  
  worker->join();
  intermediateSocket->Close();
}

void Intermediate::handleClient(void *socket, RequestQueue *request_queue) {
  char userRequest[BUFFER_SIZE];
  VSocket *client = (VSocket *)socket;
  client->Read(userRequest, BUFFER_SIZE);
  std::cout << userRequest << std::endl;
  request_queue->enqueue(request_queue, userRequest);
  std::string response = "Connection handled";
  client->Write(response.c_str());
  client->Close();
}

void Intermediate::intermediateServer_UDP() {
  VSocket *intermediate;
  int numBytes;
  char buffer[BUFFER_SIZE];
  char *message = (char *)"Connection request";
  struct sockaddr_in intermediateInfo;

  intermediate = new Socket('d');
  memset(&intermediateInfo, 0, sizeof(intermediateInfo));
  intermediateInfo.sin_family = AF_INET;
  intermediateInfo.sin_port = htons(UDP_PORT_SERVER);
  intermediateInfo.sin_addr.s_addr = INADDR_ANY;
  
  bool isConnected = false;
  while (!isConnected) {
    numBytes = intermediate->sendTo((void*)message, strlen(message), (void *)&intermediateInfo);
    std::cout << "Sent data: " << message << std::endl;
    numBytes = intermediate->recvFrom((void*)buffer, BUFFER_SIZE, (void *)&intermediateInfo);
    buffer[numBytes] = '\0';
    if (numBytes > 0) {
      std::cout << "Received data: " << buffer << std::endl;
      isConnected = true;
    }
  }
  intermediate->Close();
}

void Intermediate::sendTCPRequest(RequestQueue* requestQueue) {
  VSocket* intermediateSocket;
  char buffer[BUFFER_SIZE]; // ToDo: Implement buffer
  std::string figureRequest; // ToDo: Implement figure request
  for (int i = 0; i < 2; i++) {
    intermediateSocket = new Socket('s', false);
    intermediateSocket->Connect(this->ipDirection.c_str(), TCP_PORT_SERVER);
    figureRequest = buildRequest(i);
    std::cout << "Sending data: " << figureRequest << std::endl;
    intermediateSocket->Write(figureRequest.c_str(), strlen(figureRequest.c_str()));
    intermediateSocket->Read(buffer, BUFFER_SIZE);
    std::cout << "Received data: " << buffer << std::endl;
    intermediateSocket->Close();
  }
}

std::string Intermediate::buildRequest(int figurePart) {
  char* dequeue_value = "\0";
  this->requestQueue->dequeue(this->requestQueue, dequeue_value);
  std::string legoFigure(dequeue_value);
  std::string request = "GET / ";
  request += legoFigure + "%" + std::to_string(figurePart) + "//HTTP\r\n\r\n"; 
  std::cout << "Request: " << request << std::endl;
  return request;
}