#include "syscall.h"

int main() {
  int id;
  char buffer[512];
  char * request = (char *) "NachOS legoFigures/get-BobOmb";

  id = Socket(AF_INET_NachOS, SOCK_STREAM_NachOS);
  Connect(id, "127.0.0.0", 1233);
  Write(request, 512, id);
  Read(buffer, 512, id);
  Write(buffer, 512, 1);
  Close(id);
}