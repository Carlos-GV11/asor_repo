#include <stdio.h>
#include <time.h>
#include <errno.h>

int main() {

    time_t t = time(0);
    struct tm *tm = localtime(&t);

    if (tm != NULL) {
        printf("Año: %d \n", tm->tm_year + 1900);
        return 1;
    }

    else {
        perror("localtime()");
        return -1;
    }

}