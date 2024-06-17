#include "Client.h"
#include "Client.h"

Client::Client() {
  this->clientSocket = nullptr;
  this->socketType = ' ';
  this->figure = "";
  this->request = "";
  this->ipDirection = nullptr;
  memset(this->buffer, 0, MAXBUF);
}

Client::~Client() {

}

void Client::run() {
  this->clientSocket = new Socket('s', false);
  this->ipDirection = "127.0.0.1";
  this->request = "GET /" + this->figure + "/ /HTTP/1.1\r\n";
  this->clientSocket->Connect(this->ipDirection, CLIENT_PORT);
  this->clientSocket->Write(this->request.c_str());

  std::cout << "Request was sent" << std::endl;

  this->response = "";
  while (this->clientSocket->Read(this->buffer, MAXBUF) > 0)
  {
    this->response += this->buffer; // Appending received data to the response string
  }
  printResponse();
}

bool Client::analyzeArgs(int argc, char *argv[]) {
  bool validArgs = false; // Assumes the arguments are invalid
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

void Client::printResponse() {
  std::cout << "\t" << CYAN << this->figure << " parts" << RESET << std::endl;
  std::cout << this->response << std::endl;
}