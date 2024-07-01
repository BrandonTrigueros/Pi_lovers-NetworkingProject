#ifndef FileManager_h
#define FileManager_h

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

class FileManager
{

public:
  FileManager() = default;
  ~FileManager() = default;
  std::string Read(std::string);
};

#endif
