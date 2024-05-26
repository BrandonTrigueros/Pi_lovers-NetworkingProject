#include "syscall.h"

int main() {
  int id;
  char a[1024];
  char * request = (char *) "GET /lego/list.php?figure=giraffe HTTP/1.1\r\nhost: redes.ecci\r\n\r\n";

  id = Socket(AF_INET_NachOS, SOCK_STREAM_NachOS);
  Connect(id, "163.178.104.187", 80);
  Write(request, strlen( request ), id);
  Read(a, 1024, id);
  Write(a, 1024, 1);
  Close(id);
}