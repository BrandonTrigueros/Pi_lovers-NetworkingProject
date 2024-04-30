#include "Client.h"

Client::Client() {
  this->legoParts = 0;
  this->socketType = 's';
  this->osv4 = "127.0.0.1";
}

Client::~Client() {
  // delete this->clientSocket;
}

bool Client::createSocket(int argc, char* argv[]) {
  int error = 0;
  if (analyzeArgs(argc)) {
    this->figure = argv[1];

    if (argc > 2) {
      this->clientSocket = new SSLSocket();
      this->clientSocket->Connect(this->osv4, 443);
    } else {
      this->clientSocket = new Socket(this->socketType, false);
      this->clientSocket->Connect(this->osv4, 1233);
    }
    error = 1;
  } else {
    std::cout << RED << "\n\tUsage: ./main.out <animal> \n"
              << RESET << std::endl;
    error = 0;
  }
  return error;
}

bool Client::analyzeArgs(int argc) { return argc > 1; }

void Client::run() {
  // Create an SSL socket and connect to the server
  for (int requestNumber = 1; requestNumber < 2; requestNumber++) {
    // Request format http://legoFigures/get-<figura>-<parte>
    request = "http://legoFigures/get-" + this->figure + "-0"
        + std::to_string(requestNumber);
    this->clientSocket->Write(request.c_str());
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
  }
  // Close the connection
  delete this->clientSocket;
}

std::string Client::castHTML(const std::string& htmlResponse) {
  std::smatch match;
  std::string fixedHtml;
  std::regex tdRegex(
      "<TR>\\s*<TD.*?>(.*?)<\\/TD>\\s*<TD.*?>(?:\\s*<H2>)?(.*?)(?:<\\/"
      "H2>\\s*)?<\\/TD>\\s*<\\/TR>");

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
    // this->legoParts += getLegoParts(htmlResponse);
    this->finalResponse += htmlResponse;
  }
}

// TODO: Only works with chiki's server
int Client::getLegoParts(std::string htmlResponse) {
  std::string::size_type keywordPosition = 0;
  keywordPosition = htmlResponse.find("figura");
  int legoParts = std::stoi(htmlResponse.substr(keywordPosition + 6));
  return legoParts;
}

// TODO: Only works with chiki's server
std::string Client::formatResponse(std::string htmlResponse) {
  std::regex totalRegex("Total de piezas para armar esta figura\\d+");
  htmlResponse = std::regex_replace(htmlResponse, totalRegex, std::string(""));
  std::regex multipleNewlinesRegex("\\n{2,}");
  htmlResponse = std::regex_replace(htmlResponse, multipleNewlinesRegex, "\n");
  return htmlResponse;
}

void Client::printTitle() {
  std::string legoTitle = this->figure;
  std::transform(
      legoTitle.begin(), legoTitle.end(), legoTitle.begin(), ::toupper);
  std::cout << CYAN << "\n   LEGO PIECES FOR " << figure << "\n" << RESET;
}

void Client::printResponse() {
  if (this->figureFound) {
    std::cout << formatResponse(finalResponse) << std::endl;
    // TODO: Only works with chiki's server
    // std::cout << GREEN << "  Piezas necesarias para armar la figura: " <<
    // legoParts << "\n" << RESET;
  }
}
