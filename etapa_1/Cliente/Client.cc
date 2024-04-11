#include "Client.h"

Client::Client() {
  this->socketType = 's';
  this->osv4 = "163.178.104.187";
}

Client::~Client() {
  // delete this->clientSocket;
}

bool Client::createSocket(int argc, char* argv[]) {
  int error = 0;
  if (analyzeArgs(argc)) {
    this->animal = argv[1];

    if (argc > 2) {
      this->clientSocket = new SSLSocket();
      this->clientSocket->Connect(this->osv4, 443); 
      std::cout << "\n  USING SSL SOCKET";
    } else {
      this->clientSocket = new Socket(this->socketType, false);
      this->clientSocket->Connect(this->osv4, 80); 
      std::cout << "\n USING TCP SOCKET";
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
  for (int requestNumber = 1; requestNumber < 3; requestNumber++) {
    request = "GET /lego/list.php?figure=" + this->animal + "&part=" + ((char)(requestNumber + 48)) +  " HTTP/1.1\r\nhost: redes.ecci\r\n\r\n";
    this->clientSocket->Write(request.c_str());
    // Reset the buffers
    concatResponse = "";
    memset(responseArray, 0, MAX_BUFFER_SIZE);
    // Read
    while (concatResponse.find("</HTML>") == std::string::npos && concatResponse.find("</html>") == std::string::npos){
      this->clientSocket->Read(responseArray, MAX_BUFFER_SIZE);
      concatResponse += this->responseArray;
    }
    
    this->htmlResponse = castHTML(concatResponse);
    verifyResponse(this->htmlResponse);
    
  }
  // Close the connection
  // delete this->clientSocket;
}

std::string Client::castHTML(const std::string htmlResponse) {
  std::regex tagRegex("\\s{2,}|<[^>]+>|\\n"); // Regular expression to match HTML tags
  std::string fixedHTML = std::regex_replace(htmlResponse, tagRegex, ""); // Replaces <div> ..... </diV with ""
  fixedHTML.erase(0, 537);
  fixedHTML = std::regex_replace(fixedHTML, std::regex("   "), ""); // Replaces "  " with "\n"
  fixedHTML = std::regex_replace(fixedHTML, std::regex("  "), "\n"); // Replaces "  " with "\n"
  return fixedHTML;
}

void Client::verifyResponse(const std::string htmlResponse) {
  this->figureFound = false;
  if (this->htmlResponse.empty()) {
    std::cout << RED << "\n Error 404! Figure NOT found\n" << RESET << std::endl;
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
  keywordPosition = htmlResponse.find("figura");
  int legoParts = std::stoi(htmlResponse.substr(keywordPosition + 6));
  return legoParts;
}

std::string Client::formatResponse(std::string htmlResponse) {
  std::regex totalRegex("Total de piezas para armar esta figura\\d+");
  htmlResponse = std::regex_replace(htmlResponse, totalRegex, std::string(""));
  std::regex multipleNewlinesRegex("\\n{2,}");
  htmlResponse = std::regex_replace(htmlResponse, multipleNewlinesRegex, "\n");
  return htmlResponse;
}

void Client::printTitle() {
  std::transform(this->animal.begin(), this->animal.end(), this->animal.begin(), ::toupper);
  std::cout << CYAN << "\n   LEGO PIECES FOR " << animal << "\n" << RESET;
  std::transform(this->animal.begin(), this->animal.end(), this->animal.begin(), ::tolower);
}

void Client::printResponse() {
  if (this->figureFound) {
    std::cout << formatResponse(finalResponse) << std::endl;
    std::cout << GREEN << "  Piezas necesarias para armar la figura: " << legoParts << "\n" << RESET;
  }
}

