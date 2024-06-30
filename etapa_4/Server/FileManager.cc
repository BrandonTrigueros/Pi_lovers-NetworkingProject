#include "FileManager.h"

std::string FileManager::Read(std::string file_path) {
  file_path = "./Legos/" + file_path + ".txt";
  std::cout << "File path: "<< file_path << std::endl;
  std::ifstream legoFile;
  std::string line;
  std::string serverResponse = "";
  legoFile.open(file_path);
  if (legoFile.is_open()) {
    while (std::getline(legoFile, line)) {
      serverResponse += line;
      serverResponse += "\n";
    }
    legoFile.close();
  } else {
    std::cout << "Error opening file!" << std::endl;
  }

  return serverResponse;
}