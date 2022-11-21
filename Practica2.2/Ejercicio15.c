#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("No se han introducido argumentos suficientes para la función.\n");
        return -1;
    }

    else if (argc > 2) {
        printf("Se han introducido demasiados argumentos para la función.\n");
        return -1;
    }

    else {
        char * ruta = argv[1];
        int fd = open(ruta, O_RDWR);
        if (fd != -1) {
            int rs = lockf(fd, F_LOCK, 0);
            if (rs == 0) {
                char date[100];
                time_t t = time(0);
                struct tm *tm = localtime(&t);
                strftime(date, 100, "%H:%M", tm);
                printf("Se ha conseguido bloquear el fichero. Hora actual: %s \n", date);
                sleep(10);
                int rs = lockf(fd, F_ULOCK, 0);
                if (rs == 0) {
                    printf("Se ha conseguido desbloquear el fichero.\n");
                    sleep(10);
                    printf("Programa finalizado\n");
                    return 1;
                }
                else {
                    perror("lockf()");
                    return -1;
                }    
            }
            else {
                perror("lockf()");
                return -1;
            }
        }
        else {
            perror("open()");
            return -1;
        }
    }
}
   
