#ifndef FileManager_h
#define FileManager_h

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

class FileManager {

  public:
    FileManager() = default;
    ~FileManager() = default;
    void Read( std::string* buffer, const char* file_path );

};

#endif
