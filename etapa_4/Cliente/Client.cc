#include "Client.h"

Client::Client() {
  this->legoParts = 0;
  this->socketType = 's';
  this->osv4 = "127.0.0.1";
}

Client::~Client() {
  // delete this->clientSocket;
}

bool Client::analyzeArgs(int argc, char* argv[]) {
  int success = 0;
  if (argc > 1) {
    this->figure = argv[1];
    success = 1;
  } else {
    std::cout << RED << "\n\tUsage: ./main.out <animal> \n" << RESET << std::endl;
  }
  return success;
}

void Client::run() {
  for (int requestNumber = 1; requestNumber < 3; requestNumber++) {     // 2 requests
    this->clientSocket = new Socket(this->socketType, false);
    this->clientSocket->Connect(this->osv4, 1233);  // Client is connected to 1233 port
    // Request format http://legoFigures/get-<figura>-<parte>
    request = "http://legoFigures/get-" + this->figure + "-0"
        + std::to_string(requestNumber);
    this->clientSocket->Write(request.c_str());
    std::cout << "ENVIE REQUEST" << std::endl;
    // Reset the buffers
    concatResponse = "";
    memset(responseArray, 0, MAX_BUFFER_SIZE);
    // Read
    while (concatResponse.find("</HTML>") == std::string::npos) {
      this->clientSocket->Read(responseArray, MAX_BUFFER_SIZE);
      concatResponse += this->responseArray;
    }
    this->htmlResponse = castHTML(concatResponse);
    verifyResponse(this->htmlResponse);
    // Close the connection
    delete this->clientSocket;
  }
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
  this->figureFound = false;
  if (this->htmlResponse.empty()) {
    std::cout << RED << "\n Error 404! Figure NOT found\n"
              << RESET << std::endl;
  } else if (this->htmlResponse.find("Illegal request") != std::string::npos) {
    std::cout << RED << "\n Error 404! Illegal request\n" << RESET << std::endl;
  } else {
    this->figureFound = true;
    this->legoParts += getLegoParts(htmlResponse);
    this->finalResponse += htmlResponse;
  }
}

int Client::getLegoParts(std::string htmlResponse) {
  std::string::size_type keywordPosition = 0;
  keywordPosition = htmlResponse.find("piezas");
  int legoParts = std::stoi(htmlResponse.substr(keywordPosition + 6));
  return legoParts;
}

std::string Client::formatResponse(std::string htmlResponse) {
  std::regex piecesRegex("Total de piezas\\s\\d+");
  htmlResponse = std::regex_replace(htmlResponse, piecesRegex, std::string(""));
  std::regex multipleNewlinesRegex("\\n{2,}");
  htmlResponse = std::regex_replace(htmlResponse, multipleNewlinesRegex, "\n");
  return htmlResponse;
}

void Client::printTitle() {
  std::string legoTitle = this->figure;
  std::transform(
      legoTitle.begin(), legoTitle.end(), legoTitle.begin(), ::toupper);
  std::cout << CYAN << "\n       LEGO PIECES FOR " << figure << "\n" << RESET;
}

void Client::printResponse() {
  if (this->figureFound) {
    std::cout << formatResponse(finalResponse) << std::endl;
    std::cout << GREEN << "  Piezas necesarias para armar la figura: " <<
    legoParts << "\n" << RESET;
  }
}
