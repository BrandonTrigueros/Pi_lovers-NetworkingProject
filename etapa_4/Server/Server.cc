#include "Server.h"

void Server::run()
{
  std::thread *worker_UDP, *worker_TCP;
  bool conected = false;
  std::cout << YELLOW << "P.I Lovers server is running..." << RESET << std::endl;
  while (!conected) {
    if (!serverIntermediate_UDP()) {
      conected = listenIntermediateUDP();
    }
  } 
}

bool Server::listenIntermediateUDP()
{
  std::cout << "Waiting for intermediate..." << std::endl;
  struct sockaddr serverInfo;
  VSocket *intermediate = new Socket('d', false);
  bool isConected = false;
  int bytesReceived = 0;
  int tries = 0;
  intermediate->Bind(UDP_PORT);
  char buffer[BUFFER_SIZE];
  char *message = (char *)"Connection accepted";
  memset(&serverInfo, 0, sizeof(serverInfo));
  // std::cout << "Server is running" << std::endl;
  while (bytesReceived <= 0 && tries < 5) {
    // std::cout << "I'm listening" << std::endl;
    bytesReceived = intermediate->recvFrom((void *)buffer, BUFFER_SIZE, (void *)&serverInfo);
    // std::cout << "Received data: " << buffer << std::endl;
    tries++;
  }

  if (bytesReceived > 0) {
    intermediate->sendTo((void *)message, strlen(message), (void *)&serverInfo);
    // std::cout << "Sent data: " << message << std::endl;
    isConected = true;
  }
  intermediate->Close();
  return isConected;
}

bool Server::serverIntermediate_UDP()
{
  Socket *intermediate;
  int numBytes;
  char buffer[BUFFER_SIZE];
  char *message = (char *)"Connection request";
  struct sockaddr_in intermediateInfo;
  intermediate = new Socket('d');
  memset(&intermediateInfo, 0, sizeof(intermediateInfo));
  intermediateInfo.sin_family = AF_INET;
  intermediateInfo.sin_port = htons(UDP_PORT);
  intermediateInfo.sin_addr.s_addr = INADDR_ANY;

  // std::cout << "Message: " << message << std::endl;
  numBytes = intermediate->sendTo(
      (void *)message, strlen(message), (void *)&intermediateInfo);
  numBytes = intermediate->recvFrom(
      (void *)buffer, BUFFER_SIZE, (void *)&intermediateInfo);
  buffer[numBytes] = '\0';
  intermediate->Close();
  return numBytes <= 0 ? false : true;
}

void Server::scanExistingPieces()
{
  std::string directoryPath = "./Legos";
  if (!std::filesystem::exists(directoryPath))
  {
    std::cerr << "El directorio no existe: " << directoryPath << std::endl;
  }
  for (const auto &entry : std::filesystem::directory_iterator(directoryPath))
  {
    if (entry.is_regular_file() && entry.path().extension() == ".html")
    {
      this->serverPieces.push_back(entry.path().filename().string());
    }
  }
}

void Server::listenIntermediateTCP()
{
  std::thread *thread_TCP;
  VSocket *server, *intermediate;
  server = new Socket('s');

  server->Bind(TCP_PORT);
  server->Listen(5);

  while (true)
  {
    intermediate = server->Accept();
    thread_TCP = new std::thread(responseTCP, (void *)intermediate);
  }
  thread_TCP->join();
}

// todo: Hacer qudevuelva el html solicitado
void Server::responseTCP(void *socket)
{
  char request[BUFFER_SIZE];
  char *response = (char *)"TCP connection accepted";
  VSocket *intermediate = (VSocket *)socket;
  intermediate->Read(request, BUFFER_SIZE);
  std::cout << "Received data: " << request << std::endl;
  intermediate->Write((void *)response, strlen(response));
  std::cout << "Sent data: " << response << std::endl;
  intermediate->Close();
}
