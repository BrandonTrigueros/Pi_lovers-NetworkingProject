#include "ServerSide.h"

// Variables definitions
//std::string protocolRequest = "http://legoFigures/get-";

// Define LEGO animals
std::string legoFigures [] = {"giraffe", "elephant", "lion", "monkey", "spiderman", 
  "porsche911", "eiffelTower"};

// Define LEGO pieces
std::map<std::string, std::string> giraffe {
  {"body", "2x4 brick"},
  {"head", "1x1 brick"},
  {"legs", "1x2 bricks"},
  {"neck", "1x3 brick"},
  {"spots", "1x1 round plate"},
  {"tail", "1x1 cone piece"}
};

std::map<std::string, std::string> elephant {
  {"body", "2x6 brick"},
  {"ears", "2x2 inverted slope bricks"},
  {"head", "2x2 brick"},
  {"legs", "1x4 bricks"},
  {"trunk", "1x2 slope brick"},
};

std::map<std::string, std::string> lion {
  {"body", "2x6 brick"},
  {"head", "2x2 brick"},
  {"legs", "1x2 bricks"},
  {"mane", "1x1 round plate"},
  {"tail", "1x1 cone piece"}
};

std::map<std::string, std::string> monkey {
  {"arms", "1x2 bricks with clip"},
  {"body", "2x4 brick"},
  {"head", "1x2 brick"},
  {"legs", "1x2 bricks"},
  {"tail", "1x1 cone piece"}
};

std::map<std::string, std::string> spiderman {
  {"arms", "1x2 bricks with clip"},
  {"body", "2x4 brick"},
  {"head", "1x1 round plate"},
  {"legs", "1x2 bricks"},
  {"mask", "1x2 slope brick with print"},
  {"web", "1x1 round plate with connector"}
};

std::map<std::string, std::string> porsche911 {
  {"body", "2x8 bricks"},
  {"doors", "1x4 bricks"},
  {"roof", "2x6 flat plate"},
  {"wheels", "2x2 round plate"},
  {"windshield", "1x4 slope brick"}
};

std::map<std::string, std::string> eiffelTower {
  {"arches", "1x4 slope bricks"},
  {"base", "4x4 bricks"},
  {"legs", "1x1 bricks"},
  {"middle section", "1x2 bricks"},
  {"platform", "4x4 flat plate"},
  {"upper section", "1x1 bricks"}
};

#define REDTEXT "\033[1;31m"
#define GREENTEXT "\033[1;32m"
#define CYANTEXT "\033[1;36m"
#define RESET "\033[0m"

std::string getFigure(std::string userRequest) {
  size_t firstDashPos = userRequest.find('-');
  size_t secondDashPos = userRequest.find('-', firstDashPos + 1);
  std::string textBetweenDashes = userRequest.substr(firstDashPos + 1, secondDashPos - firstDashPos - 1);
  return textBetweenDashes;
}
void* server(void* data) {
  privateData* pData = (privateData*) data;
  sharedData* sData = pData->sData;

  std::string legoFigure = "";
  while (!sData->closeServer) {
    sem_wait(&sData->serverSemaphore);
    if (validatePartRequest(sData->legoPart)) { 
      legoFigure = getFigure(sData->userRequest);
    
      if (compareRequest(sData->userRequest)) {
        sData->serverResponse = "";
        sData->closeServer = true;
        break;
      } else {
        bool legoFound = false;
        for (const auto& lego : legoFigures) {
          if (legoFigure == lego) {
            legoFound = true;
            break;
          }
        }

        if (legoFound) {
          int legoPiece = 0;
          legoPiece = getLegoPart(sData->legoPart);
          sData->serverResponse = getLegoPieces(legoFigure, legoPiece);
        } else {
          setErrorFigureMessage(sData);
        }
        sem_post(&sData->userSemaphore);
      }
    } else {
      setErrorPartMessage(sData);
      sem_post(&sData->userSemaphore);
    }
  }
  return nullptr;
}


bool validatePartRequest(std::string legoPart) {
  return (legoPart == "first" || legoPart == "second" || legoPart == "full");
}

bool compareRequest(std::string userRequest) {
  return (userRequest.find("get-q") != std::string::npos || userRequest.find("get-Q") != std::string::npos);
}

void setErrorPartMessage(sharedData* sData) {
  sData->serverResponse = "";
  sData->serverResponse += REDTEXT;
  sData->serverResponse += "\tERROR 404! - Invalid lego part request!";
  sData->serverResponse += RESET;
  sData->serverResponse += "\n";
}

void setErrorFigureMessage(sharedData* sData) {
  sData->serverResponse = "";
  sData->serverResponse += REDTEXT;
  sData->serverResponse += "\tERROR 404! - Invalid lego figure request!";
  sData->serverResponse += RESET;
  sData->serverResponse += "\n";
}

int getLegoPart(std::string legoPart) {
  if (legoPart == "first") {
    return 1;
  } else if (legoPart == "second") {
    return 2;
  } else if (legoPart == "full") {
    return 3;
  }
  return -1;
}

std::string getLegoPieces(const std::string& legoFigure, int legoPart) {  
  std::map<std::string, std::string> legoPieces;

  if (legoFigure == "giraffe") {
    legoPieces = giraffe;
  } else if (legoFigure == "elephant") {
    legoPieces = elephant;
  } else if (legoFigure == "lion") {
    legoPieces = lion;
  } else if (legoFigure == "monkey") {
    legoPieces = monkey;
  } else if (legoFigure == "spiderman") {
    legoPieces = spiderman;
  } else if (legoFigure == "porsche911") {
    legoPieces = porsche911;
  } else if (legoFigure == "eiffelTower") {
    legoPieces = eiffelTower;
  }

  auto firstPiece = legoPieces.begin();
  auto lastPiece = legoPieces.end();

  // Determine the iteration range
  if (legoPart == 1) {
    firstPiece = legoPieces.begin();
    lastPiece = std::next(firstPiece, legoPieces.size() / 2);
  } else if (legoPart == 2) {
    firstPiece = std::next(firstPiece, legoPieces.size() / 2);
    lastPiece = legoPieces.end();
  } else if (legoPart == 3) {
    firstPiece = legoPieces.begin();
    lastPiece = legoPieces.end();
  }

  std::string requestResponse;
  requestResponse = "\n   LEGO: " + legoFigure + " parts" + "\n";
  requestResponse += GREENTEXT;

  // Iterate in the established range
  for (auto it = firstPiece; it != lastPiece; ++it) {
    requestResponse += "\t" + it->first + ":" + it->second + "\n";
  }
  requestResponse += RESET;

  return requestResponse;
}