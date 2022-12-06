#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char * argv[]) {
    if (argc != 5) {
        printf("Formato incorrecto. Prueba comando1 argumento1 comando2 argumento2\n");
        return -1;
    }

    else {
        int fd[2];
        if (pipe(fd) == 0) {
            switch(fork()) {
                case -1:
                    perror("fork()");
                    return -1;

                case 0:
                    if (dup2(fd[0], 0) != -1) {
                        if (close(fd[1]) == 0) {
                            execlp(argv[3], argv[3], argv[4], NULL);
                            perror("execlp() child");
                        }

                        else {
                            perror("close() child");
                            return -1;
                        }
                    }

                    else {
                        perror("dup2() child");
                        return -1;
                    }

                default:
                    if (dup2(fd[1], 1) != -1) {
                        if (close(fd[0]) == 0) {
                            execlp(argv[1], argv[1], argv[2], NULL);
                            perror("execlp() parent");
                        }

                        else {
                            perror("close() parent");
                            return -1;
                        }
                    }

                    else {
                        perror("dup2() parent");
                        return -1;
                    }
            }

            return 1;
        }

        else {
            perror("pipe()");
            return -1;
        }
    }
}