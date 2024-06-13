#include "Server.h"

void Server::Run() {

  std::cout << "Server running" << std::endl;

  std::thread intermediate_listener(&Server::listenIntermediates, this);
  intermediate_listener.join();

  // std::thread* worker;
  // VSocket *server_socket, *client;
  // server_socket = new Socket('s');
  // server_socket->Bind(PORT);  // Port to access this mirror server
  // server_socket->Listen(5);  // Set backlog queue to 5 conections
  // VSocket *message_socket = new Socket('d', false);
  // message_socket->Bind(PORT);
  
  // while (true) {
  // listenIntermediates();
  // Wait for a client conection
  //  client = server_socket->Accept();
  // Create a new thread to handle client request
  //   worker = new std::thread(task, (void*)client);
  // }

  //worker->join();
}

void Server::listenIntermediates() {
  struct sockaddr server_info;
  VSocket *intermediate = new Socket('d', false);
  intermediate->Bind(PORT);
  char buffer[512];
  char *message = (char *) "Intermediate server connected"; 
  memset(&server_info, 0, sizeof(server_info));

  while (true) {
    intermediate->recvFrom((void*) buffer, BUFSIZE, (void*)&server_info);
    std::cout << "Received data: " << buffer << std::endl; // ToDo: comment this line
    intermediate->sendTo((void*) message, strlen(message), (void*)&server_info);
  }
  intermediate->Close();
}

std::string Server::getFigure(std::string userRequest) {
  size_t first_dash = userRequest.find('-');
  size_t second_dash = userRequest.find('-', first_dash + 1);
  std::string figure
      = userRequest.substr(first_dash + 1, second_dash - first_dash - 1);
  return figure;
}

std::string Server::getPiece(std::string userRequest) {
  size_t first_dash = userRequest.find('-');
  size_t second_dash = userRequest.find('-', first_dash + 1);
  std::string piece = userRequest.substr(second_dash + 1, 2);
  return piece;
}

int Server::getNumParts(std::string htmlResponse) {
  std::string::size_type keywordPosition = 0;
  keywordPosition = htmlResponse.find("piezas");
  int legoParts = std::stoi(htmlResponse.substr(keywordPosition + 6));
  return legoParts;
}

std::string Server::castHTML(const std::string& htmlResponse) {
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

void Server::task(void* socket) {
  char request[BUFSIZE];
  std::string html_text;
  std::string http_response;
  std::string lego_name;
  std::string file_path;
  VSocket* client = (VSocket*)socket;
  client->Read(request, BUFSIZE);
  // Request format http://legoFigures/get-<figura>-<parte>
  std::cout << request << std::endl;
  lego_name = getFigure(request);

  FileManager file_manager;
  std::string legos[]
      = { "Dragon", "Car", "DogHouse", "TieFighter", "BobOmb", "SantaClaus", "Jovani"};

  bool figure_found = false;
  for (int index = 0; index <= legos->size(); index++) {
    if (legos[index] == lego_name) {
      figure_found = true;
      break;
    }
  }

  if (figure_found) {
    file_manager.Read(&html_text, file_path.c_str());
    http_response = "HTTP/1.1 200 OK\r\nContent-Length: "
        + std::to_string(html_text.length())
        + "\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
  } else {
    file_manager.Read(&html_text, "Legos/Error404.html");
    http_response = "HTTP/1.1 404 Not Found\r\nContent-Length: "
        + std::to_string(html_text.length())
        + "\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
  }

  client->Write(http_response.c_str());
  client->Write(html_text.c_str());
  client->Close();
}

