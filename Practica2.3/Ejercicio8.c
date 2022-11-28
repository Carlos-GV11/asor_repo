#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("Se han indicado muy pocos argumentos para la función\n");
        return -1;
    }
    else {
        pid_t pid = fork();
        switch (pid) {
            case -1:
                perror("fork()");
                exit(1);
            case 0:
                printf("Se está ejecutando el proceso hijo...\n");

                int rs1 = chdir("/tmp");
                if (rs1 == -1) {
                    perror("chdir()");
                    exit(1);
                }

                int fd0 = open("/dev/null", O_CREAT | O_RDWR, 00666);
                int fd1 = open("/tmp/daemon.out", O_CREAT | O_RDWR, 00666);
                int fd2 = open("/tmp/daemon.err", O_CREAT | O_RDWR, 00666);
                if (fd0 == -1 || fd1 == -1 || fd2 == -1) {
                    perror("open()");
                    exit(1);
                }
                else {
                    int dp0 = dup2(fd0, 0);
                    int dp1 = dup2(fd1, 1);
                    int dp2 = dup2(fd2, 2);
                    if (dp0 == -1 || dp1 == -1 || dp2 == -1) {
                        perror("dup2()");
                        exit(1);
                    }
                }

                int rs2 = execvp(argv[1], argv + 1);
                if (rs2 == -1) {
                    perror("execvp()");
                    exit(1);
                }
                break;
            default:
                printf("Se está ejecutando el proceso padre...\n");
                break;
        }
        return 0;
    }
}
