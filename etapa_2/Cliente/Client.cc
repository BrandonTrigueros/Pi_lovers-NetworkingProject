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
    std::cout << RED << "\n\tUsage: ./main.out <animal> \n" << RESET << std::endl;
    error = 0;
  }
  return error;
}

bool Client::analyzeArgs(int argc) {
  return argc > 1;
}

void Client::run() {
  // Create an SSL socket and connect to the server
  for (int requestNumber = 1; requestNumber < 2; requestNumber++) {
    // Request format http://legoFigures/get-<figura>-<parte>
    request = "http://legoFigures/get-" + this->figure + "-0" + std::to_string(requestNumber);
    this->clientSocket->Write(request.c_str());
    // Reset the buffers
    concatResponse = "";
    memset(responseArray, 0, MAX_BUFFER_SIZE);
    // Read
    while (concatResponse.find("</HTML>") == std::string::npos){
      this->clientSocket->Read(responseArray, MAX_BUFFER_SIZE);
      concatResponse += this->responseArray;
    }

    this->htmlResponse = castHTML(concatResponse);
    verifyResponse(this->htmlResponse);
  }
  // Close the connection
  delete this->clientSocket;
}

// std::string Client::castHTML(const std::string htmlResponse) {
//   std::regex tagRegex("\\s{2,}|<[^>]+>|\\n"); // Regular expression to match HTML tags
//   std::string fixedHTML = std::regex_replace(htmlResponse, tagRegex, ""); // Replaces <div> ..... </diV with ""
//   // TODO: Fix this, only works with chiki's server
//   // fixedHTML.erase(0, 537);
//   fixedHTML = std::regex_replace(fixedHTML, std::regex("   "), ""); // Replaces "  " with "\n"
//   fixedHTML = std::regex_replace(fixedHTML, std::regex("  "), "\n"); // Replaces "  " with "\n"
//   return fixedHTML;
// }


std::string Client::castHTML(const std::string& htmlResponse) {
    // Regular expression to match HTML tags and newlines
    std::regex tagRegex("(<[^>]+>)|\n");
    // Remove HTML tags and newlines from the HTML response
    std::string fixedHTML = std::regex_replace(htmlResponse, tagRegex, "");
    // Replace multiple spaces with a single space
    fixedHTML = std::regex_replace(fixedHTML, std::regex("\\s+"), " ");
    // Trim leading and trailing whitespaces
    fixedHTML = std::regex_replace(fixedHTML, std::regex("^\\s+|\\s+$"), "");
    return fixedHTML;
}

std::string Client::castHTML(const std::string& htmlResponse) {
  
}


void Client::verifyResponse(const std::string htmlResponse) {
  this->figureFound = false;
  if (this->htmlResponse.empty()) {
    std::cout << RED << "\n Error 404! Figure NOT found\n" << RESET << std::endl;
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
  std::transform(legoTitle.begin(), legoTitle.end(), legoTitle.begin(), ::toupper);
  std::cout << CYAN << "\n   LEGO PIECES FOR " << figure << "\n" << RESET;
}

void Client::printResponse() {
  if (this->figureFound) {
    std::cout << formatResponse(finalResponse) << std::endl;
    // TODO: Only works with chiki's server
    // std::cout << GREEN << "  Piezas necesarias para armar la figura: " << legoParts << "\n" << RESET;
  }
}

