#include "MasterIntermediate.h"

MasterIntermediate::MasterIntermediate() {
  this->userRequest = nullptr;
}

MasterIntermediate::~MasterIntermediate() {
 
}


void MasterIntermediate::clientIntermediate() {
  // listen Client
  // receiveTCP
  // sendTCP
}

void MasterIntermediate::run() {
  listenClient();
}

void MasterIntermediate::listenClient() {
  std::thread* worker;
  VSocket *masterIntermediate, *client;
  std::cout << "Master intermediate server is running" << std::endl;
  masterIntermediate = new Socket('s');
  masterIntermediate->Bind(CLIENT_PORT);
  masterIntermediate->Listen(5);  // Set backlog queue to 5 conections

  while (true) {
    client = masterIntermediate->Accept();
    worker = new std::thread(handleClient, (void*)client);
  }
  worker->join();
}


void MasterIntermediate::handleClient(void* socket) {
  char userRequest[BUFFER_SIZE];
  VSocket* client = (VSocket*)socket;
  client->Read(userRequest, BUFFER_SIZE);
  std::cout << userRequest << std::endl;
  std::string response = "Connection handled";
  client->Write(response.c_str());
  client->Close();
}



