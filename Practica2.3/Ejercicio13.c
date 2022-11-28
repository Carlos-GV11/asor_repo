#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int sigusr1_rcv = 0;

void handler(int signal) {
    if (signal == SIGUSR1) sigusr1_rcv = 1;
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("Número incorrecto de parámetros a función...\n");
    }

    else {
        struct sigaction act;
        act.sa_handler = handler;
        if (sigaction(SIGUSR1, &act, NULL) == 0) {
            int secs = atoi(argv[1]);
            while (secs > 0 && sigusr1_rcv == 0) {
                secs--;
                sleep(1);
                printf("%d segundos restantes...\n", secs);
            }
            if (secs == 0) {
                printf("Se va a borrar el archivo...\n");
                if (unlink(argv[0]) == -1) {
                    perror("unlink()");
                    return -1;
                }
                else {
                    printf("¡Archivo borrado!\n");
                    return 1;
                }
            }
            else {
                printf("Se ha recibido la señal SIGUSR1. El archivo no se borrará. \n");
                sigset_t set;
                sigsuspend(&set);
            }
        }
        else {
            perror("sigaction()");
            return -1;
        }
    }
}