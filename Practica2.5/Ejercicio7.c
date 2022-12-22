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
  connect(sd, (struct sockaddr *)result->ai_addr, result->ai_addrlen);
  freeaddrinfo(result);

  char buf_in[255];
  char buf_out[255];
  ssize_t c;

  while (1) {
    c = read(0, buf_in, 254);
    buf_in[c] = '\0';
    send(sd, buf_in, c, 0);

    if ((buf_in[1] == 'q') && (c == 2)) {
      printf("Conexión terminada\n");
      return 1;
    }

    c = recv(sd, buf_out, 254, 0);
    buf_out[c] = '\0';
    printf("[OUT]:%s\n", buf_out);
  }

  close(sd);
  return 1;
}