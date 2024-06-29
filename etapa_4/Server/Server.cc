#include "Server.h"

void Server::run()
{
  scanExistingPieces();
  concatFigures();
  bool conected = false;
  std::cout << YELLOW << "P.I Lovers server is running..." << RESET << std::endl;
  while (!conected)
  {
    conected = serverIntermediate_UDP();
    if (!conected)
    {
      conected = listenIntermediateUDP();
    }
  }
  listenIntermediateTCP();
}

bool Server::serverIntermediate_UDP()
{
  Socket *intermediate;
  int numBytes;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in intermediateInfo;
  intermediate = new Socket('d');
  memset(&intermediateInfo, 0, sizeof(intermediateInfo));
  intermediateInfo.sin_family = AF_INET;
  intermediateInfo.sin_port = htons(UDP_PORT);
  intermediateInfo.sin_addr.s_addr = INADDR_ANY;
  numBytes = intermediate->sendTo(
      (void *)this->myLegoFigures.c_str(), strlen(this->myLegoFigures.c_str()), (void *)&intermediateInfo);
  numBytes = intermediate->recvFrom(
      (void *)buffer, BUFFER_SIZE, (void *)&intermediateInfo);
  buffer[numBytes] = '\0';
  intermediate->Close();
  return numBytes <= 0 ? false : true;
}

bool Server::listenIntermediateUDP()
{
  struct sockaddr serverInfo;
  VSocket *intermediate = new Socket('d', false);
  bool isConected = false;
  int bytesReceived = 0;
  int tries = 0;
  intermediate->Bind(UDP_PORT);
  char buffer[BUFFER_SIZE];
  memset(&serverInfo, 0, sizeof(serverInfo));
  while (bytesReceived <= 0 && tries < 5)
  {
    bytesReceived = intermediate->recvFrom((void *)buffer, BUFFER_SIZE, (void *)&serverInfo);
    tries++;
  }

  if (bytesReceived > 0)
  {
    intermediate->sendTo((void *)this->myLegoFigures.c_str(), strlen(this->myLegoFigures.c_str()), (void *)&serverInfo);
    isConected = true;
  }
  intermediate->Close();
  return isConected;
}

void Server::scanExistingPieces()
{
  std::string directoryPath = "./Legos";
  if (!std::filesystem::exists(directoryPath))
  {
    std::cerr << "The directory doesn't exist: " << directoryPath << std::endl;
    return;
  }

  for (const auto &entry : std::filesystem::directory_iterator(directoryPath))
  {
    if (entry.is_regular_file())
    {
      std::string filename = entry.path().filename().string();
      size_t dotPos = filename.rfind('.');
      if (dotPos == std::string::npos)
      {
        this->serverPieces.push_back(filename);
      }
      else
      {
        std::string filenameWithoutExt = filename.substr(0, dotPos);
        this->serverPieces.push_back(filenameWithoutExt);
      }
    }
  }
}

void Server::concatFigures() {
  std::string ipAddress = getIPAddress();
  for (unsigned int i = 0; i < this->serverPieces.size(); i++)
  {
    this->myLegoFigures += "$" + this->serverPieces[i] + "@" + ipAddress;
  }
  this->myLegoFigures += "$";
}

std::string Server::getIPAddress() {
  char hostname[HOSTNAME_LENGTH];
  hostname[HOSTNAME_LENGTH - 1] = '\0';       // Ensure the hostname array is null-terminated
  gethostname(hostname, HOSTNAME_LENGTH - 1); // Retrieve the hostname of the local machine

  struct addrinfo hints, *res, *p;
  int status;
  char ipstr[INET_ADDRSTRLEN]; // Buffer to hold the IPv4 address as a string

  memset(&hints, 0, sizeof hints); // Zero out the hints structure
  hints.ai_family = AF_INET;       // Specify that we want IPv4 addresses
  hints.ai_socktype = SOCK_STREAM; // Specify a stream socket (TCP)

  // Get address information for the hostname
  if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0)
  {
    std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl; // Print error message
    return "";                                                         // Return an empty string on error
  }

  // Loop through the linked list of results
  for (p = res; p != NULL; p = p->ai_next)
  {
    void *addr = &((struct sockaddr_in *)p->ai_addr)->sin_addr; // Cast the socket address to sockaddr_in and extract the IPv4 address
    inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr); // Convert the binary IP address to a readable string
    std::string ipAddress(ipstr); // Create a C++ string from the C-style string
    freeaddrinfo(res); // Free the memory allocated for the address list
    return ipAddress; // Return the IP address
  }
  freeaddrinfo(res); // Free the memory allocated for the address list in case the loop didn't run
  return ""; // Return an empty string if no IP address was found
}

void Server::listenIntermediateTCP() {
  std::thread *thread_TCP;
  VSocket *server, *intermediate;
  server = new Socket('s');

  server->Bind(TCP_PORT);
  server->Listen(5);

  while (true)
  {
    std::cout << "Im listening Intermediate" << std::endl;
    intermediate = server->Accept();
    thread_TCP = new std::thread(responseTCP, (void *)intermediate);
  }
  thread_TCP->join();
}

// todo: Hacer qudevuelva el html solicitado
void Server::responseTCP(void *socket) {
  char request[BUFFER_SIZE];
  char *response = (char *)"TCP connection accepted";
  VSocket *intermediate = (VSocket *)socket;
  intermediate->Read(request, BUFFER_SIZE);
  // std::cout << "Received data: " << request << std::endl;
  intermediate->Write((void *)response, strlen(response));
  // std::cout << "Sent data: " << response << std::endl;
  intermediate->Close();
}
