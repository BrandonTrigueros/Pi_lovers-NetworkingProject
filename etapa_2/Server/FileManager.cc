#include "FileManager.h"

void FileManager::Read(std::string* buffer, const char* file_path) {
  std::ifstream file;
  std::string line;
  std::cout << "PATH: " << file_path << std::endl;
  file.open(file_path);
  if (file.is_open()) {
    while (std::getline(file, line)) {
      *buffer += line;
      *buffer += "\n";
    }
    file.close();
  } else {
    std::cout << "Error opening file!" << std::endl;
  }
}