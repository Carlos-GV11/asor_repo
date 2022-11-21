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
            int rs = dup2(fd, 1);
            if (rs != -1) {
                printf("Escribiendo por salida estándar\n");
                printf("Esta salida debe redirigirse al fichero\n");
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