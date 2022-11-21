#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    umask(0027);
    int rs = open("fichero_ejercicio7", O_RDWR | O_CREAT, 00645);

    if (rs != -1) {
        printf("ls -l fichero_ejercicio7\n");
        system("ls -l fichero_ejercicio7");
        system("rm fichero_ejercicio7");
        return 1;
    }

    else {
        perror("open()");
        return -1;
    }
}