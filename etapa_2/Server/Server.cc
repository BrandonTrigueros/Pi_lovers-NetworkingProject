#include "Server.h"

void Server::Run() {
  std::thread *worker;
  VSocket *server_socket, *client;
  std::cout << "Server running" << std::endl; // ToDo: Delete this line
  server_socket = new Socket('s');

  server_socket->Bind(PORT); // Port to access this mirror server
  server_socket->Listen(5);  // Set backlog queue to 5 conections

  while (true) {
    // Wait for a client conection
    client = server_socket->Accept();
    // Create a new thread to handle client request
    worker = new std::thread(task, (void*)client);
  }
  worker->join();
}

std::string Server::getFigure(std::string userRequest) {
  size_t first_dash = userRequest.find('-');
  size_t second_dash = userRequest.find('-', first_dash + 1);
  std::string figure = userRequest.substr(first_dash + 1, second_dash - first_dash - 1);
  return figure;
}

std::string Server::getPiece(std::string userRequest) {
  size_t first_dash = userRequest.find('-');
  size_t second_dash = userRequest.find('-', first_dash + 1);
  std::string piece = userRequest.substr(second_dash + 1, 2);
  return piece;
}

void Server::task(void *socket) {
  char request[BUFSIZE];
  std::string html_text;
  std::string http_response;
  std::string lego_name;
  std::string lego_part;
  std::string file_path;
  VSocket* client = (VSocket *)socket;
  // Receive request from client
  client->Read(request, BUFSIZE);
  std::cout << "Request received: " << request << std::endl; // ToDo: Delete this line
  // Request format http://legoFigures/get-<figura>-<parte>
  lego_name = getFigure(request);
  lego_part = getPiece(request);
  file_path = "Legos/" + lego_name + lego_part + ".html";

  FileManager file_manager;
  std::string legos[] = {"Dragon", "Car", "DogHouse", "TieFighter", "BobOmb", "SantaClaus"};

  bool figure_found = false;
  for (int index = 0; index < legos->size(); index++) {
    if (legos[index] == lego_name) {
      figure_found = true;
      break;
    }
  }

  if (figure_found) {
    file_manager.Read(&html_text, file_path.c_str());
    http_response = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(html_text.length()) + "\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
  } else {
    file_manager.Read(&html_text, "Legos/Error404.html");
    http_response = "HTTP/1.1 404 Not Found\r\nContent-Length: " + std::to_string(html_text.length()) + "\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
  }
  client->Write(http_response.c_str());
  client->Write(html_text.c_str());
  client->Close();
}
