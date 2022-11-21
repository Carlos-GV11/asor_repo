#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

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
            int rs1 = dup2(fd, 1);
            int rs2 = dup2(fd, 2);
            if (rs1 != -1 || rs2 != -1) {
                printf("Escribiendo por salida estándar\n");
                printf("Esta salida debe redirigirse al fichero\n");
                setuid(0);
                perror("Último error guardado en errno");
                return 1;
            }
            else {
                perror("dup2()");
                return -1;
            }
        }
        else {
            perror("open()");
            return -1;
        }
    }
}