#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main (int argc, char * argv[]) {
  if (argc < 4) {
    printf("Formato incorrecto. Introduce una dirección IPv4 o IPv6, un puerto y un comando t, d o q como comandos\n");
    return -1;
  }

  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo *result;
  if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {
    perror("getaddrinfo()");
    return -1;
  }

  int sd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  freeaddrinfo(result);

  struct sockaddr_storage client_addr;
  socklen_t client_addrlen = sizeof(client_addr);
  sendto(sd, argv[3], 2, 0, result->ai_addr, result->ai_addrlen);

  printf("%s\n", argv[3]);
  if (argv[3] == 'd' || argv[3] == 't') {
    char buf[50];
    ssize_t c = recvfrom(socketUDP, buf, 50, 0, (struct sockaddr *) &client_addr, &client_addrlen);
    buf[c] = '\0';
    printf("%s\n", buf);
  }

  return 0;
}