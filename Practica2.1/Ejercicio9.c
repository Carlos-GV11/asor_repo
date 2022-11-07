#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    printf("Identificador de usuario real UID: %d \n", getuid());
    printf("Identificador de usuario efectivo EUID: %d \n", geteuid());

    return 1;
}