#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

class Intermedio {
    private:
    std::vector<std::string> split(const std::string &s, char delimiter);
    public:
    Intermedio();
    std::string route_table;
    std::map<std::string, std::vector<std::string>> pieces_map;
    void actTable(std::string nuevaTabla);
    void addPiece(std::string piece);
    void deletePiece(std::string piece);
    void parseTable();
    void printTable();
};