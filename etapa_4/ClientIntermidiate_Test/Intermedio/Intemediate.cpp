#include "Intermediate.h"

void Intermediate::run() {
  // connect_server();
  // listenServer();
  intermediate_client();
}

void Intermediate::intermediate_client() {
  std::thread* worker;
  Socket *connection_socket, *cliente;
  connection_socket = new Socket('s');  // todo hacerlo el this->socket
  connection_socket->Bind(PORT);
  connection_socket->Listen(5);
  while (true) {
    cliente = connection_socket->Accept();
    worker = new std::thread(listen_client, cliente);
  }
  // worker->join();
}

void Intermediate::listen_client(Socket* intermedio) {
  char request[MAX];
  std::string lego_name;
  std::string file_path;

  std::string html_text = "Not found </HTML>";
  std::string http_response = "HTTP/1.1 404 Not Found\r\nContent-Length: "
      + std::to_string(html_text.length())
      + "\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";

  intermedio->Read(request, MAX);

  // ToDo: Connect the server and get the response

  intermedio->Write(http_response.c_str());
  intermedio->Write(html_text.c_str());
  intermedio->Close();
}

// void Intermediate::connect_server() {
//   VSocket* intermediate;
//   int connect_result;
//   struct sockaddr_in other;
//   memset(&other, 0, sizeof(other));
//   other.sin_family = AF_INET;
//   other.sin_port = htons(PORT);
//   other.sin_addr.s_addr = INADDR_ANY;
//   char buffer[MAX];
//   char* hello = (char*)"New intermediate severs is up and running";
//   intermediate = new Socket('d');
//   connect_result
//       = intermediate->sendTo((void*)hello, strlen(hello), (void*)&other);
//   printf("Message sent.\n");

//   connect_result = intermediate->recvFrom((void*)buffer, MAX, (void*)&other);
//   buffer[connect_result] = '\0';
//   printf("Message received: %s\n", buffer);
//   intermediate->Close();
// }

// void Intermediate::listen_server() { }