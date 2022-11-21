#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

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
        struct stat buf;
        int rs = stat(argv[1], &buf);

        if (rs == 0) {
            if (S_ISREG(buf.st_mode)) {
                char ruta_sym[100]; strcpy(ruta_sym, argv[1]);
                char ruta_lnk[100]; strcpy(ruta_lnk, argv[1]);
                int sl = symlink(argv[1], strcat(ruta_sym, ".sym"));
                int hl = link(argv[1], strcat(ruta_lnk, ".hard"));
                if (sl == 0 && hl == 0) {
                    printf("ls -l | grep .sym \n");
                    system("ls -l | grep .sym");
                    printf("ls -l | grep .hard \n");
                    system("ls -l | grep .hard");
                    return 1;
                }
                else {
                    perror("symlink() | link()");
                }
                
            }
            else {
                printf("No se ha recibido una ruta a un fichero.\n");
                return -1;
            }
        }
        else {
            perror("stat()");
            return -1;
        }
    }
}