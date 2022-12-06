#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("Formato incorrecto. Pruebe ./Ejercicio4 tuberia\n");
        return -1;
    }
    else {
        if (mkfifo(argv[1], 0777) == -1) {
            perror("mkfifo()");
            return -1;
        }
        else {
            printf("Tubería creada correctamente. Ábrela en otro terminal...\n");
            int fd = open(argv[1], O_WRONLY);
            if (fd == -1) {
                perror("open()");
                return -1;
            }
            else {
                if (write(fd, argv[0], strlen(argv[0])) == -1) {
                    perror("write()");
                    return -1;
                }
                else {
                    printf("Se ha escrito correctamente en la tubería. Eliminando...\n");
                    close(fd);
                    unlink(argv[1]);
                    return 1;
                }
            }
        }
    }
}