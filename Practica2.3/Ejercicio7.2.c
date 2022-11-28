#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("Se han indicado muy pocos argumentos para la función\n");
        return -1;
    }
    else {
        int rs = execvp(argv[1], argv + 1);
        if (rs == -1) {
            perror("execvp()");
            return -1;
        }
        else {
            printf("El comando terminó de ejecutarse\n");
            return 1;
        }
    }
}