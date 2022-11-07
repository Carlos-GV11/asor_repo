#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <errno.h>

int main() {

    struct passwd *pw = getpwuid(getuid());

    if (pw != NULL) {
        printf("Nombre de usuario: %s \n", pw->pw_name);
        printf("Directorio home: %s \n", pw->pw_dir);
        printf("Descripción del usuario: %s \n", pw->pw_gecos);
        return 1;
    }

    else {
        perror("getpwuid()");
        return -1;
    }
}