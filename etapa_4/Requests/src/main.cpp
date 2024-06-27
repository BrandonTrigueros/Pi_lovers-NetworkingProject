#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "intermedio.h"

int main() {
  std::string route_table = "$horse0@123.123.123.123@222.222.222.222$dragon1@000.000.000.000$horse1@111.111.111.111$dragon0@192.168.0.1$";
  std::map<std::string, std::vector<std::string>> pieces_map;
  Intermedio myIntermedio;
  myIntermedio.actTable(route_table);
  return 0;
}