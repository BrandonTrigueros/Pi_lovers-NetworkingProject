#include "FileManager.h"

void FileManager::Read( char* buffer, const char* file_path ) {
  std::ifstream file;
  char line[ 256 ];
  file.open( file_path );
  if ( file.is_open() ) {
    while ( file.getline( line, 256 ) ) {
      strcat(buffer, line);
      strcat(buffer, "\n");
    }
    file.close();
  } else { 
    std::cout << "Error opening file"  << std::endl;
  }
}