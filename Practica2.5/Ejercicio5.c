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
 if (argc < 3) {
    printf("Formato incorrecto. Introduce una dirección IPv4 o IPv6 y un puerto como comandos\n");
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
  if (bind(sd, result->ai_addr, result->ai_addrlen) != 0) {
    perror("bind()");
    return -1;
  }
  freeaddrinfo(result);
  signal(SIGCHLD, hler);
  
  char comando[2];
  char host[NI_MAXHOST];
  char serv[NI_MAXSERV];

  struct sockaddr_storage client_addr;
  socklen_t client_addrlen = sizeof(client_addr);

  int i = 0;
  int status;

  for (i = 0; i < 2; i++) {
    pid_t pid = fork();
    if (pid == 0) {
      while(1) {
        ssize_t c = recvfrom(sd, comando, 2, 0, (struct sockaddr *) &client_addr, &client_addrlen);
        comando[1] = '\0';

        getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
        printf("%i byte(s) de %s:%s cuyo PID: %d\n", bytes, host, serv, getpid());

        time_t tiempo = time(NULL);
        struct tm *tm = localtime(&tiempo);
        char buf[50];

        switch(comando[0]) {
          case 't':
            size_t bytes = strftime(buf, 49, "%I:%M:%S %p", tm);
            buf[bytes] = '\0';
            sendto(sd, buf, bytes, 0, (struct sockaddr *) &client_addr, client_addrlen);
            break;
          
          case 'd':
            size_t bytes = strftime(buf, 49, "%Y-%m-%d", tm);
            buf[bytes] = '\0';
            sendto(sd, buf, bytes, 0, (struct sockaddr *) &client_addr, client_addrlen);
            break;
          
          case 'q':
            printf("Terminado el proceso servidor...\n");
            return 1;

          default:
            printf("Comando no soportado.\n");
            break;
        }
      }
    }

    else {
      pid = wait(&status);
    }
  }

  return 1;
}