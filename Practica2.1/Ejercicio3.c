#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    
    int err;

    for (err = 0; err <= 255; err++) {
        printf("Código de error %d: %s \n", err, strerror(err));
    }
    
    return 1;
}