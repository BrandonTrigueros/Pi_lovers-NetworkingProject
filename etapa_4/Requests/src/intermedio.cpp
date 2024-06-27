#include "intermedio.h"

Intermedio::Intermedio(){}

std::vector<std::string> Intermedio::split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

void Intermedio::addPiece(std::string piece) {
  std::vector<std::string> parts = split(piece, '@');
  if (parts.size() < 2) {
    std::cerr << "Invalid piece format" << std::endl;
    return;
  }
  std::string figura = parts[0];
  std::string ip = parts[1];
  // Si la figura ya existe, solo agregar la IP
  if (pieces_map.find(figura) != pieces_map.end()) {
    pieces_map[figura].push_back(ip);
  } else {
    // Si la figura no existe, agregar la figura y la IP
    pieces_map[figura] = {ip};
  }
  // Reconstruir el route_table
    route_table.clear();
    for (const auto& pair : pieces_map) {
        route_table += "$" + pair.first;
        for (const std::string& ip : pair.second) {
            route_table += "@" + ip;
        }
    }
    route_table += "$";  // Asegurar el formato de cierre

    // Imprimir la tabla actualizada
    std::cout << "Tabla actualizada: " << route_table << std::endl;
}

void Intermedio::deletePiece(std::string piece) {
 
}

void Intermedio::parseTable() {
  this->pieces_map.clear();
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