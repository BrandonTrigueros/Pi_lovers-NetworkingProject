#include "Client.h"

Client::Client()
{
  this->clientSocket = nullptr;
  this->socketType = ' ';
  this->figure = "";
  this->request = "";
  this->ipDirection = nullptr; // ToDo (Brandon or Jose): maybe we can obtain dynamically this
  memset(this->buffer, 0, MAXBUF);
}

Client::~Client() {}

void Client::run()
{
  this->clientSocket = new Socket('s', false);  //! Change IP back to 172.16.123.68
  this->ipDirection = "127.0.0.1"; // ToDo change to the server's IP as needed (can be obtained dynamically in the constructor)
  this->request = "GET /" + this->figure + "/ /HTTP/1.1\r\n";
  this->clientSocket->Connect(this->ipDirection, CLIENT_PORT);
  this->clientSocket->Write(this->request.c_str());

  this->response = "";
  while (this->clientSocket->Read(this->buffer, MAXBUF) > 0)
  {
    this->response += this->buffer; // Appending received data to the response string
  }
  std::string serverResponse(this->buffer);
  printResponse(serverResponse);
}

bool Client::analyzeArgs(int argc, char *argv[])
{
  bool validArgs = false; // Assumes the4100 arguments are invalid
  if (argc > 1)
  {
    validArgs = true;
    this->figure = argv[1];
  }
  else
  {
    std::cerr << RED << "WRONG USAGE!\n"
              << RESET << "Usage: ./Client.out <legoFigure>" << std::endl;
  }
  return validArgs;
}

void Client::printResponse(std::string serverResponse)
{
  this->response = castHTML(serverResponse);
  std::cout << this->response << std::endl;
}

bool Client::verifyErrorResponse(std::string serverResponse) {
  return serverResponse.find("error 404") != std::string::npos;
}

std::string Client::castHTML(std::string serverResponse)
{
  std::string formatedResponse = "";
  if (!verifyErrorResponse(serverResponse)) {
    std::transform(this->figure.begin(), this->figure.end(), this->figure.begin(), ::toupper);
    std::cout << "\n\t" << CYAN << this->figure << " PARTS" << RESET << std::endl;
    
    int legoParts = getLegoParts(serverResponse);
    std::regex regexPattern("<TD ALIGN=center>([^<]+)</TD>\\s*<TD ALIGN=center>([^<]+)</TD>");
    std::smatch matches;
    auto responseStart = serverResponse.cbegin();
    auto responseEnd = serverResponse.cend();
    while (std::regex_search(responseStart, responseEnd, matches, regexPattern))
    {
      formatedResponse += matches[1].str() + " " + matches[2].str() + "\n";
      responseStart = matches.suffix().first;
    }
    formatedResponse += "\n\033[1;33mTotal number of pieces: " + std::to_string(legoParts) + "\033[0m\n";
  } else {
    formatedResponse = "\033[1;31mError 404: Figure not Found\033[0m\n";
  }
  return formatedResponse;
}

int Client::getLegoParts(std::string serverResponse)
{
  std::string::size_type keywordPosition = 0;
  keywordPosition = serverResponse.find("figura:");
  std::cout << serverResponse << std::endl;
  std::cout << keywordPosition << std::endl;
  int legoParts = std::stoi(serverResponse.substr(keywordPosition + 7));
  return legoParts;
}