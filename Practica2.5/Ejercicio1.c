#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main (int argc, char * argv[]) {
  if (argc < 2) {
    printf("Formato incorrecto. Introduce una dirección IPv4 o IPv6 como comando\n");
    return -1;
  }

  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = 0;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_protocol = 0;
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  struct addrinfo *result;
  if (getaddrinfo(argv[1], NULL, &hints, &result) != 0) {
      perror("getaddrinfo()");
      return -1;
  }

  struct addrinfo *iterator;
  for (iterator = result; iterator != NULL; iterator = iterator->ai_next) {
    switch(iterator->ai_family) {
      case AF_INET:;
        struct sockaddr_in *info = iterator->ai_addr;
        char ip[INET_ADDRSTRLEN + 1] = "";
        inet_ntop(AF_INET, &(info->sin_addr), ip, INET_ADDRSTRLEN + 1);
				printf("%s\t", ip);
        break;

      case AF_INET6:;
        struct sockaddr_in6 *info6 = iterator->ai_addr;
        char ipv6[INET6_ADDRSTRLEN + 1] = "";
        inet_ntop(AF_INET6, &(info6->sin6_addr), ipv6, INET6_ADDRSTRLEN + 1);
				printf("%s\t", ipv6);
        break;

      default:
        printf("Error al leer ai_family.\n");
        break;
    }
		printf("%i\t%i\t\n", iterator->ai_family, iterator->ai_socktype);
	}

  freeaddrinfo(result);
  return 1;
}