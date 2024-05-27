#include "syscall.h"

int main() {
  int id;
  char a[512];
  char * request = (char *) "NachOS legoFigures/get-Dragon-01";

  id = Socket(AF_INET_NachOS, SOCK_STREAM_NachOS);
  Connect(id, "127.0.0.0", 1233);
  Write(request, 512, id);
  Read(a, 512, id);
  Write(a, 512, 1);
  Close(id);
}