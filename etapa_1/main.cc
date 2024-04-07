/**
*  Para IPv6 esta prueba solo funciona utilizando un equipo de la red interna de la ECCI,
*  por lo que deberán realizarlo en la ECCI o conectarse por la VPN para completarla
*  La dirección IPv6 provista es una dirección privada
*
*  También deben prestar atención al componente que esta luego del "%" en la dirección y que hace
*  referencia a la interfaz de red utilizada para la conectividad: "enp0s31f6"
*
*  Puede obtener las direcciones de sus tarjetas de red con el comando "ip addr"
*
*  Uso:
*
*    ./tcp-cli.out ipVer[4|6] SSL[0|1]
**/

#include <algorithm>
#include <cctype>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <regex>
#include <iostream>

#include "VSocket.h"
#include "Socket.h"
#include "SSLSocket.h"

#define RED "\033[1;31m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

std::string castHTML(const char* htmlResponse) {
  std::string htmlString(htmlResponse);
  std::regex tagRegex("\\s{2,}|<[^>]+>|\\n"); // Regular expression to match HTML tags
  // std::regex tagRegex("(CI-0123 Proyecto integrador redes y sistemas operativos \\(PIRO\\)|<TD ALIGN=center> \\d|Descripción|Cantidad|\\/|Regresar|Imagen|[\\{\\}]+|window\\.location\\( \"\\/lego\\/index\\.php\" \\);|function home\\(\\) {|\\s{2,}|<[^>]+>)");
  std::string fixedHTML = std::regex_replace(htmlString, tagRegex, ""); // Replaces <div> ..... </diV with ""
  fixedHTML.erase(0, 391);
  
  return fixedHTML;
}

int main(int argc, char* argv[]) {
  const char* osv4 = "163.178.104.187";

  VSocket* client;
  VSocket* client2;
  char bufferArray[100000];
  char bufferArray2[100000];
  std::string animal;
  std::string request1 = "";
  std::string request2 = "";
  memset(bufferArray, 0, 100000);
  memset(bufferArray2, 0, 100000);

  if (argc > 1) {
    // Get the animal and legoPart from command line arguments
    animal = argv[1];
    
    // Construct the HTTP request using std::stringstream
    std::stringstream requestStream;
    std::stringstream requestStream2;
    requestStream << "GET /lego/list.php?figure=" << animal << "&part=1 HTTP/1.1\r\nhost: redes.ecci\r\n\r\n";
    request1 = requestStream.str();
    
    // Create an SSL socket and connect to the server
    client = new SSLSocket();			// Create an IPv4 TCP SSL socket
    client->Connect(osv4, 443);
    client->Write(request1.c_str());
    client->Read(bufferArray, 100000);
    client->Write(request1.c_str());
    client->Read(bufferArray, 100000);
    std::string htmlResponse = castHTML(bufferArray);
    
    if (htmlResponse.empty()) {
      std::cout << RED << "\n\tError 404! Figure NOT found\n" << RESET << std::endl;
    } else if (htmlResponse.find("Illegal request") != std::string::npos) {
      std::cout << RED << "\n\tError 404! Illegal request\n" << RESET << std::endl;
    } else {
      std::transform(animal.begin(), animal.end(), animal.begin(), ::toupper);
      std::cout << CYAN << "\n\tLEGO PIECES FOR " << animal << "\n" << RESET << htmlResponse << std::endl << std::endl;
    }
    delete client; // Free the memory allocated for the socket

  } else {
    std::cout << RED << "\n\tUsage: ./main.out <animal> \n" << RESET << std::endl;
  }
  return 0;  
}