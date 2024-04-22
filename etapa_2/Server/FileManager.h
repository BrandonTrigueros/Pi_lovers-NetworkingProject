
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
    void Read( char* buffer, const char* file_path );

};

#endif
