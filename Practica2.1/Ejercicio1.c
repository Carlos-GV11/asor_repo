#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {

    int rt = setuid(0);

    if (rt == 0) {
        return 1;
    }

    else {
        perror("setuid()");
        return -1;
    }
}