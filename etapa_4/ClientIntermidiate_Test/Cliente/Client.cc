#include "Client.h"

Client::Client() {
  this->socketType = 's';
  this->osv4 = "127.0.0.1";
  this->legoParts = 0;
  this->htmlResponse = "";
  this->figureFound = false;
  this->illegalRequest = false;
}

Client::~Client() { delete this->clientSocket; }

bool Client::analyzeArgs(int argc, char* argv[]) {
  if (argc > 1) {
    this->figure = argv[1];
    this->request = "http://legoFigures/get-" + this->figure + "-0";
    return 1;
  } else {
    std::cout << RED << "\n\tUsage: ./main.out <animal> \n"
              << RESET << std::endl;
    return 0;
  }
}

void Client::run() {
  this->printTitle();
  char readBuffer[MAX_BUFFER_SIZE];
  this->clientSocket = new Socket(this->socketType, false);
  this->clientSocket->Connect(this->osv4, PORT);
  for (int requestNumber = 0; requestNumber < 2; requestNumber++) {
    this->request += std::to_string(requestNumber + 1);
    this->clientSocket->Write(this->request.c_str());
    while (this->htmlResponse.find("</HTML>") == std::string::npos) {
      memset(readBuffer, '\0', MAX_BUFFER_SIZE);
      this->clientSocket->Read(readBuffer, MAX_BUFFER_SIZE);
      this->htmlResponse += readBuffer;
      std::cout << "readBuffer: " << readBuffer << std::endl;
      std::cout << "htmlResponse: " << this->htmlResponse << std::endl;
    }
    verifyResponse(this->htmlResponse);
  }
  this->printResponse();
}

void Client::printTitle() {
  std::string legoTitle = this->figure;
  std::transform(
      legoTitle.begin(), legoTitle.end(), legoTitle.begin(), ::toupper);
  std::cout << CYAN << "\n       LEGO PIECES FOR " << this->figure << "\n"
            << RESET;
}

void Client::printResponse() {
  if (this->illegalRequest) {
    std::cout << RED << "\n Error 400! Illegal request\n" << RESET << std::endl;
  } else {
    if (!this->figureFound) {
      std::cout << RED << "\n Error 404! Figure NOT found\n"
                << RESET << std::endl;
    } else {
      std::cout << formatResponse(this->finalResponse) << std::endl;
      std::cout << GREEN << "  Piezas necesarias para armar la figura: "
                << this->legoParts << "\n"
                << RESET;
    }
  }
}

int Client::getLegoParts(std::string htmlResponse) {
  std::string::size_type keywordPosition = 0;
  keywordPosition = htmlResponse.find("piezas");
  int legoParts = std::stoi(htmlResponse.substr(keywordPosition + 6));
  return legoParts;
}

std::string Client::castHTML(const std::string& htmlResponse) {
  std::smatch match;
  std::string fixedHtml;
  std::regex tdRegex(
      "<TR>\\s*<TD.*?>(.*?)<\\/TD>\\s*<TD.*?>(?:\\s*<H[1-6]>)?(.*?)(?:<\\/"
      "H[1-6]>\\s*)?<\\/TD>\\s*<\\/TR>",
      std::regex_constants::icase);
  auto htmlBegin = htmlResponse.cbegin();
  auto htmlEnd = htmlResponse.cend();
  while (std::regex_search(htmlBegin, htmlEnd, match, tdRegex)) {
    fixedHtml += match[1].str() + "\t" + match[2].str() + "\n";
    htmlBegin = match.suffix().first;
  }
  return fixedHtml;
}

void Client::verifyResponse(const std::string htmlResponse) {
  if (this->htmlResponse.find("Illegal request") != std::string::npos) {
    this->illegalRequest = true;
  } else if (this->htmlResponse.find("Not found") != std::string::npos) {
    this->figureFound = false;
  } else {
    this->figureFound = true;
    this->legoParts += getLegoParts(htmlResponse);
    this->finalResponse += this->castHTML(htmlResponse);
  }
}

std::string Client::formatResponse(std::string htmlResponse) {
  std::regex piecesRegex("Total de piezas\\s\\d+");
  htmlResponse = std::regex_replace(htmlResponse, piecesRegex, std::string(""));
  std::regex multipleNewlinesRegex("\\n{2,}");
  htmlResponse = std::regex_replace(htmlResponse, multipleNewlinesRegex, "\n");
  return htmlResponse;
}
