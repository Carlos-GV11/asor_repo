#include <stdio.h>
#include <time.h>
#include <errno.h>

int main() {

    time_t t = time(0);

    if (t != -1) {
        printf("Hora en segundos desde el Epoch: %ld \n", t);
        return 1;
    }

    else {
        perror("time()");
        return -1;
    }

}