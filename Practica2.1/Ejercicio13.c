#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>

int main() {

    struct timeval tv;

    int rs = gettimeofday(&tv, NULL);

    if (rs != -1) {
        int i;
        long usec_before = tv.tv_usec;
        
        for (i = 0; i < 1000000; i++) {}
        rs = gettimeofday(&tv, NULL);
        
        if (rs != -1)  {
            long usec_after = tv.tv_usec, usec_diff = usec_after - usec_before;
            
            printf("Hora en microsegundos antes de iniciar el bucle: %ld \n", usec_before);
            printf("Hora en microsegundos después de finalizar el bucle: %ld \n", usec_after);
            printf("Microsegundos que tarda el bucle en ejecutarse: %ld \n", usec_diff);
            return 1;
        } else {
            perror("gettimeofday()");
            return -1;
        }
    } else {
        perror("gettimeofday()");
        return -1;
    }
}