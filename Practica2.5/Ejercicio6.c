#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char * argv[]) {
  if (argc < 3) {
    printf("Formato incorrecto. Introduce una dirección IPv4 o IPv6 y un puerto como comandos.\n");
    return -1;
  }

  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo *result;
  if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {
    perror("getaddrinfo()");
    return -1;
  }

  int sd = socket(result->ai_family, result->ai_socktype, 0);
  bind(sd, result->ai_addr, result->ai_addrlen);
  freeaddrinfo(result);
  listen(sd, 5);

  struct sockaddr_storage cli;
  socklen_t clen = sizeof(cli);

  char buf[80];
  int clisd;
  char host[NI_MAXHOST];
  char serv[NI_MAXSERV];
  ssize_t c;

  while (1) {
    clisd = accept(sd, (struct sockaddr *) &cli, &clen);
    while (1) {
      getnameinfo((struct sockaddr *)&cli, clen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);
      printf("Conexión desde %s:%s\n", host, serv);

      c = recv(clisd, buf, 79, 0);
      buf[c] = '\0';

      if ((buf[0] == 'q') && (c == 2)) {
        printf("Conexión terminada\n");
        return 1;
      }
      send(clisd, buf, c, 0);
    }
  }

  close(clisd);
  return 1;
}