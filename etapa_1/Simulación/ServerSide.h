#ifndef SERVERSIDE_H
#define SERVERSIDE_H

#include <iostream>
#include <pthread.h>
#include <map>
#include <string> 
#include <algorithm>
#include <cctype>
#include "./ThreadData.h"
// #include "legoFigures.h"
  void* server(void*);
  bool validatePartRequest(std::string);
  bool compareRequest(std::string);

  void setErrorPartMessage(sharedData*);
  void setErrorFigureMessage(sharedData*);

  int getLegoPart(std::string);
  std::string getLegoPieces(const std::string&, int);

#endif // SERVERSIDE_H