/**
*  Para IPv6 esta prueba solo funciona utilizando un equipo de la red interna de la ECCI,
*  por lo que deberán realizarlo en la ECCI o conectarse por la VPN para completarla
*  La dirección IPv6 provista es una dirección privada
*
*  También deben prestar atención al componente que esta luego del "%" en la dirección y que hace
*  referencia a la interfaz de red utilizada para la conectividad: "enp0s31f6"
*
*  Puede obtener las direcciones de sus tarjetas de red con el comando "ip addr"
*
*  Uso:
*
*    ./tcp-cli.out ipVer[4|6] SSL[0|1]
**/
#include "Client.h"

int main(int argc, char* argv[]) {
  Client client;
  if (client.createSocket(argc, argv)) {
    client.printTitle();
    client.run();
    client.printResponse();
  }
  return 0;  
}