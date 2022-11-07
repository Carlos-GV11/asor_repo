#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    
    int rt = setuid(0);

    if (rt == 0) {
        return 1;
    }

    else {
        printf("Código de error %d: %s \n", errno, strerror(errno));
        // perror("setuid()");
        return -1;
    }
}