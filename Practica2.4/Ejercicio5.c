#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("Formato incorrecto. Pruebe ./Ejercicio5 tuberia1 tuberia2\n");
        return -1;
    }
    else {
         if (mkfifo(argv[1], 0777) == -1 || mkfifo(argv[2], 0777) == -1) {
            perror("mkfifo()");
            return -1;
        }
        else {
            int fd1 = open(argv[1], O_RDONLY | O_NONBLOCK);
            int fd2 = open(argv[2], O_RDONLY | O_NONBLOCK);
            if (fd1 == -1 || fd2 == -1) {
                perror("open()");
                return -1;
            }
            else {
                fd_set readfds;
                FD_ZERO(&readfds);
                FD_SET(fd1, &readfds);
                FD_SET(fd2, &readfds);

                int ready;
                while((ready = select((fd1 > fd2) ? fd1 + 1 : fd2 + 1, &readfds, NULL, NULL, NULL)) != -1) {
                    if (ready != 0) {
                        int pipe;
                        if (FD_ISSET(fd1, &readfds)) {
                            pipe = fd1;
                        }
                        else {
                            pipe = fd2;
                        }
                        char buf[256];
                        ssize_t size = 255;
                        while (size == 255) {
                            size = read(pipe, buf, 255);
                            buf[size] = '\0';
                            printf("Pipe con fd %d: %s", pipe, buf);
                        }

                        if (pipe == fd1) {
                            close(fd1);
                            fd1 = open(argv[1], O_RDONLY | O_NONBLOCK);
                            if (fd1 == -1) {
                                perror("open() fd1");
                                close(fd1);
                                close(fd2);
                                return -1;
                            }
                        }

                        else {
                            close(fd2);
                            fd2 = open(argv[2], O_RDONLY | O_NONBLOCK);
                            if (fd2 == -1) {
                                perror("open() fd2");
                                close(fd2);
                                close(fd1);
                                return -1;
                            }
                        }
                    }
                }

                perror("select()");
                close(fd1);
                close(fd2);
                return -1;

            }
        }
    }
}