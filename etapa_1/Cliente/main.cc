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
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

std::string castHTML(const std::string& htmlResponse) {
  std::string htmlString(htmlResponse);
  std::regex tagRegex("\\s{2,}|<[^>]+>|\\n"); // Regular expression to match HTML tags
  std::string fixedHTML = std::regex_replace(htmlString, tagRegex, ""); // Replaces <div> ..... </diV with ""
  fixedHTML.erase(0, 391);
  fixedHTML = std::regex_replace(fixedHTML, std::regex("   "), ""); // Replaces "  " with "\n"
  fixedHTML = std::regex_replace(fixedHTML, std::regex("  "), "\n"); // Replaces "  " with "\n"
  return fixedHTML;
}

int getLegoParts(std::string htmlResponse) {
  std::string::size_type keywordPosition = 0;
  keywordPosition = htmlResponse.find("figura");
  int legoParts = std::stoi(htmlResponse.substr(keywordPosition + 6));
  return legoParts;
}

std::string formatResponse(std::string htmlResponse) {
  std::regex totalRegex("Total de piezas para armar esta figura\\d+");
  htmlResponse = std::regex_replace(htmlResponse, totalRegex, std::string(""));
  std::regex multipleNewlinesRegex("\\n{2,}");
  htmlResponse = std::regex_replace(htmlResponse, multipleNewlinesRegex, "\n");
  return htmlResponse;
}

int main(int argc, char* argv[]) {
  // system("clear");
  if (argc > 1) {
    const char* osv4 = "163.178.104.187";
    VSocket* client;
    VSocket* client2;
    char bufferArray[100000];
    char bufferArray2[100000];
    std::string animal; std::string request = ""; std::string htmlResponse; std::string finalResponse = "";
    int legoParts = 0;
    bool figureFoud = false;

    // Get the animal and legoPart from command line arguments
    animal = argv[1];
    // Construct the HTTP request using std::stringstream
    std::stringstream requestStream;

    std::transform(animal.begin(), animal.end(), animal.begin(), ::toupper);
    std::cout << CYAN << "\n\tLEGO PIECES FOR " << animal << "\n" << RESET;
    std::transform(animal.begin(), animal.end(), animal.begin(), ::tolower);

    for (int requestNumber = 0; requestNumber < 2; requestNumber++) {
      // Create an SSL socket and connect to the server
      client = new SSLSocket();			// Create an IPv4 TCP SSL socket
      client->Connect(osv4, 443); 

      memset(bufferArray, 0, 100000);
      requestStream.str("");
      requestStream.clear();
      requestStream << "GET /lego/list.php?figure=" << animal << "&part=" << (requestNumber + 1) <<  " HTTP/1.1\r\nhost: redes.ecci\r\n\r\n";
      request = requestStream.str();

      client->Write(request.c_str());
      client->Read(bufferArray, 100000);
      client->Write(request.c_str());
      client->Read(bufferArray, 100000);
      htmlResponse = castHTML(bufferArray);

      if (htmlResponse.empty()) {
        std::cout << RED << "\n    Error 404! Figure NOT found\n" << RESET << std::endl;
      } else if (htmlResponse.find("Illegal request") != std::string::npos) {
        std::cout << RED << "\n    Error 404! Illegal request\n" << RESET << std::endl;
      } else {
        figureFoud = true;
        legoParts += getLegoParts(htmlResponse);
        finalResponse += htmlResponse;
        //std::cout << htmlResponse << std::endl;
      }

      delete client; // Free the memory allocated for the socket
    }

    if (figureFoud) {
      std::cout << formatResponse(finalResponse) << std::endl;
      std::cout << GREEN << "  Piezas necesarias para armar la figura: " << legoParts << "\n" << RESET;
    }
  
  } else {
    std::cout << RED << "\n\tUsage: ./main.out <animal> \n" << RESET << std::endl;
  }
  return 0;  
}