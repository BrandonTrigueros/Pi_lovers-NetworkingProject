#include <iostream>
#include <string>
#include <map>
#include <vector>

class Intermedio {
    private:
    std::string route_table;
    std::map<std::string, std::vector<std::string>> pieces_map;
    public:
    void addPiece(std::string piece);
    void deletePiece(std::string piece);
    void parseTable();
    void actTable();
};