#include "intermedio.h"

Intermedio::Intermedio(){}

std::vector<std::string> Intermedio::split(const std::string &s, char delimiter) {
  std::cout << "Separando el siguiente string: " << s << "\nEn base al siguiente caracter: " << delimiter << std::endl;
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  std::cout << "Cantidad de segmentos " << tokens.size() << std::endl;
  return tokens;
}

void Intermedio::addPiece(std::string piece) {

}

void Intermedio::deletePiece(std::string piece) {
 
}

void Intermedio::parseTable() {
  // Separa la tabla por los '$'
  std::vector<std::string> segmentos = split(this->route_table, '$');
  for (unsigned long i = 0; i < segmentos.size(); i++) {
    std::cout << segmentos[i] << std::endl;
  }

  for (const std::string& segmento : segmentos) {
    if (!segmento.empty()) {
      // Separa cada segmento por los '@'
      std::vector<std::string> parts = split(segmento, '@');
      if (!parts.empty()) {
        // La primera parte es el nombre de la figura
        std::string figure = parts[0];
        // Lo demás son las IPs
        std::vector<std::string> ips(parts.begin() + 1, parts.end());
        // Add to the map
        this->pieces_map[figure] = ips;
      }
    }
  }

  for (const auto& pair : this->pieces_map) {
    std::cout << "Figura: " << pair.first << std::endl;
    std::cout << "IPs: ";
    for (const std::string& ip : pair.second) {
      std::cout << ip << " ";
    }
    std::cout << std::endl;
  }
}

void Intermedio::actTable(std::string nuevaTabla) {
  this->route_table = nuevaTabla;
  this->parseTable();
}