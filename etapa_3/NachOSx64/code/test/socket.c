#include "syscall.h"

int main() {
  int id;
  char buffer1[512];
  char* request1 = (char*)"NachOS legoFigures/get-BobOmb";

  id = Socket(AF_INET_NachOS, SOCK_STREAM_NachOS);
  Connect(id, "127.0.0.0", 1233);
  Write(request, 512, id);
  Read(buffer, 512, id);
  Write(buffer, 512, 1);
  Close(id);

  char buffer2[512];
  char* request2 = (char*)"NachOS legoFigures/get-Dragon";
  id = Socket(AF_INET_NachOS, SOCK_STREAM_NachOS);
  Connect(id, "127.0.0.0", 1233);
  Write(request, 512, id);
  Read(buffer, 512, id);
  Write(buffer, 512, 1);
  Close(id);

  char buffer3[512];
  char* request3 = (char*)"NachOS legoFigures/get-Car";
  id = Socket(AF_INET_NachOS, SOCK_STREAM_NachOS);
  Connect(id, "127.0.0.0", 1233);
  Write(request, 512, id);
  Read(buffer, 512, id);
  Write(buffer, 512, 1);
  Close(id);

  char buffer4[512];
  char* request4 = (char*)"NachOS legoFigures/get-DogHouse";
  id = Socket(AF_INET_NachOS, SOCK_STREAM_NachOS);
  Connect(id, "127.0.0.0", 1233);
  Write(request, 512, id);
  Read(buffer, 512, id);
  Write(buffer, 512, 1);
  Close(id);

  char buffer4[512];
  char* request4 = (char*)"NachOS legoFigures/get-DogHouse";
  id = Socket(AF_INET_NachOS, SOCK_STREAM_NachOS);
  Connect(id, "127.0.0.0", 1233);
  Write(request, 512, id);
  Read(buffer, 512, id);
  Write(buffer, 512, 1);
  Close(id);

  char buffer5[512];
  char* request5 = (char*)"NachOS legoFigures/get-TieFighter";
  id = Socket(AF_INET_NachOS, SOCK_STREAM_NachOS);
  Connect(id, "127.0.0.0", 1233);
  Write(request, 512, id);
  Read(buffer, 512, id);
  Write(buffer, 512, 1);
  Close(id);

  char buffer6[512];
  char* request6 = (char*)"NachOS legoFigures/get-Cat";
  id = Socket(AF_INET_NachOS, SOCK_STREAM_NachOS);
  Connect(id, "127.0.0.0", 1233);
  Write(request, 512, id);
  Read(buffer, 512, id);
  Write(buffer, 512, 1);
  Close(id);
}