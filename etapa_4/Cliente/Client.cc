#include "Client.h"

Client::Client() {
  this->clientSocket = nullptr;
  this->socketType = ' ';
  this->figure = "";
  this->request = "";
  this->ipDirection = this->getIPAddress().c_str();
  memset(this->buffer, 0, MAXBUF);
}

Client::~Client() { }

void Client::run() {
  this->clientSocket = new Socket('s', false);
  this->request = "GET /" + this->figure + "/ /HTTP/1.1\r\n";
  this->clientSocket->Connect(this->ipDirection, CLIENT_PORT);
  this->clientSocket->Write(this->request.c_str());

  this->response = "";
  while (this->clientSocket->Read(this->buffer, MAXBUF) > 0) {
    this->response
        += this->buffer;  // Appending received data to the response string
  }
  std::string serverResponse(this->buffer);
  printResponse(serverResponse);
}

bool Client::analyzeArgs(int argc, char* argv[]) {
  bool validArgs = false;  // Assumes the4100 arguments are invalid
  if (argc > 1) {
    validArgs = true;
    this->figure = argv[1];
  } else {
    std::cerr << RED << "WRONG USAGE!\n"
              << RESET << "Usage: ./Client.out <legoFigure>" << std::endl;
  }
  return validArgs;
}

void Client::printResponse(std::string serverResponse) {
  this->response = castHTML(serverResponse);
  std::cout << this->response << std::endl;
}

bool Client::verifyErrorResponse(std::string serverResponse) {
  return serverResponse.find("error 404") != std::string::npos;
}

std::string Client::castHTML(std::string serverResponse) {
  std::string formatedResponse = "";
  if (!verifyErrorResponse(serverResponse)) {
    std::transform(this->figure.begin(), this->figure.end(),
        this->figure.begin(), ::toupper);
    std::cout << "\n\t" << CYAN << this->figure << " PARTS" << RESET
              << std::endl;

    int legoParts = getLegoParts(serverResponse);
    std::regex regexPattern(
        "<TD ALIGN=center>([^<]+)</TD>\\s*<TD ALIGN=center>([^<]+)</TD>");
    std::smatch matches;
    auto responseStart = serverResponse.cbegin();
    auto responseEnd = serverResponse.cend();
    while (
        std::regex_search(responseStart, responseEnd, matches, regexPattern)) {
      formatedResponse += matches[1].str() + " " + matches[2].str() + "\n";
      responseStart = matches.suffix().first;
    }
    formatedResponse += "\n\033[1;33mTotal number of pieces: "
        + std::to_string(legoParts) + "\033[0m\n";
  } else {
    formatedResponse = "\033[1;31mError 404: Figure not Found\033[0m\n";
  }
  return formatedResponse;
}

int Client::getLegoParts(std::string serverResponse) {
  std::string::size_type keywordPosition = 0;
  keywordPosition = serverResponse.find("figura:");
  int legoParts = std::stoi(serverResponse.substr(keywordPosition + 7));
  return legoParts;
}

std::string Client::getIPAddress() {
  char hostname[HOSTNAME_LENGTH];
  hostname[HOSTNAME_LENGTH - 1]
      = '\0';  // Ensure the hostname array is null-terminated
  gethostname(hostname,
      HOSTNAME_LENGTH - 1);  // Retrieve the hostname of the local machine

  struct addrinfo hints, *res, *p;
  int status;
  char ipstr[INET_ADDRSTRLEN];  // Buffer to hold the IPv4 address as a string

  memset(&hints, 0, sizeof hints);  // Zero out the hints structure
  hints.ai_family = AF_INET;  // Specify that we want IPv4 addresses
  hints.ai_socktype = SOCK_STREAM;  // Specify a stream socket (TCP)

  // Get address information for the hostname
  if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
    std::cerr << "getaddrinfo: " << gai_strerror(status)
              << std::endl;  // Print error message
    return "";  // Return an empty string on error
  }

  // Loop through the linked list of results
  for (p = res; p != NULL; p = p->ai_next) {
    void* addr = &((struct sockaddr_in*)p->ai_addr)
                      ->sin_addr;  // Cast the socket address to sockaddr_in and
                                   // extract the IPv4 address
    inet_ntop(p->ai_family, addr, ipstr,
        sizeof ipstr);  // Convert the binary IP address to a readable string
    std::string ipAddress(
        ipstr);  // Create a C++ string from the C-style string
    freeaddrinfo(res);  // Free the memory allocated for the address list
    return ipAddress;  // Return the IP address
  }
  freeaddrinfo(res);  // Free the memory allocated for the address list in case
                      // the loop didn't run
  return "";  // Return an empty string if no IP address was found
}