#include "Server.h"

/*
    TODO: 
    - Create server threads
    - Read files
    - Set port
    - Write response
    - Accept connections
    - join threads
*/ 

void Server::Run() {
  std::thread * worker;
  VSocket * server_socket, * client;
  std::cout << "Server running" << std::endl;

  server_socket = new Socket( 's' );

  server_socket->Bind( PORT );		// Port to access this mirror server
  server_socket->Listen( 5 );		// Set backlog queue to 5 conections

  //while ( true ) {
    // Wait for a client conection
    client = server_socket->Accept();
    // Create a new thread to handle client request
    std::cout << "Client connected" << std::endl;
    worker = new std::thread( task, (void*)client );
  //}
  worker->join();
}

void Server::task( void* socket ) {
  char request[ BUFSIZE ];
  char html_text[ 100000 ];
  std::string animal_name;
  std::string animal_part;
  std::string file_path;
  VSocket * client = (VSocket*)socket;
  // Receive request from client
  client->Read( request, BUFSIZE );
  // TODO: Get animal name from request, by the moment we will use a fixed name
  // TODO: Get animal part from request, by the moment we will use a fixed part
  std::cout << request << std::endl;
  animal_name = "Dragon";
  animal_part = "01";
  file_path = "Legos/" + animal_name + animal_part + ".txt";
  // Read file based on request
  FileManager file_manager;
  file_manager.Read( html_text, file_path.c_str() );
  // std::cout << html_text << std::endl;
  // Write response to client
  client->Write( html_text );
  client->Close();
}