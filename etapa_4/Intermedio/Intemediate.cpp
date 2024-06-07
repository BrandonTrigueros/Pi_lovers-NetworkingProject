#include "Intermediate.h"

void Intermediate::run() {
  // Se conecta al servidor
  // connect_server();
  // Escucha al servidor
  // listenServer();
  // Escucha a los clientes
  intermediate_client();
}

void Intermediate::connect_server() {
  VSocket * intermediate;
  int connect_result;
  struct sockaddr_in other;
  memset( &other, 0, sizeof( other ) );
  other.sin_family = AF_INET;
  other.sin_port = htons(PORT);
  other.sin_addr.s_addr = INADDR_ANY;
  char buffer[MAX];
  char *hello = (char *) "New intermediate severs is up and running";
  intermediate = new Socket('d');
  connect_result = intermediate->sendTo((void *) hello, strlen(hello), (void *) &other);
  printf("Message sent.\n");

  connect_result = intermediate->recvFrom( (void *) buffer, MAX, (void *) & other );
  buffer[connect_result] = '\0';
  printf("Message received: %s\n", buffer);
  intermediate->Close();
}


void Intermediate::listen_server() {

}

void Intermediate::intermediate_client() {
  std::thread *worker;
  VSocket *connection_socket, *intermediate;
  connection_socket = new Socket('s');
  connection_socket->Bind(PORT);  // Port to access this mirror server
  connection_socket->Listen(5);  // Set backlog queue to 5 conections
  std::cout << "Intermediate listening..." << std::endl;
  while (true) {
    intermediate = connection_socket->Accept();
    worker = new std::thread(listen_client, (void*)intermediate);
  }
  worker->join();
}

void Intermediate::listen_client(void* socket) {
  char request[MAX];//HOLA AMIGOS
  std::string html_text;
  std::string http_response;
  std::string lego_name;
  std::string file_path;
  VSocket* intermediate = (VSocket*)socket;
  std::cout << "Antes de read" << std::endl;
  if (intermediate != nullptr){
    std::cout << "Intermedio no es nulo" << std::endl;
  }
  intermediate->Read(request, MAX);
  std::cout << "REQUEST: " << request << std::endl;
  // ToDo: Connect the server and get the respose
  http_response = "HTTP/1.1 404 Not Found\r\nContent-Length: "
    + std::to_string(html_text.length())
    + "\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
  html_text = "HELLO WORLD";
  intermediate->Write(http_response.c_str());
  intermediate->Write(html_text.c_str());
  intermediate->Close();
}



