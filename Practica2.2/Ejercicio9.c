#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

int main() {
    struct stat buf;
    int rs = stat(".", &buf);

    if (rs == 0) {
        printf("Número [major, minor] del dispositivo: [%lx,%lx]\n", (long) major(buf.st_dev), (long) minor(buf.st_dev));
        printf("Número de inodo del fichero: %ld\n", (long) buf.st_ino);
        printf("Tipo de fichero: ");
        switch (buf.st_mode & S_IFMT) {
            case S_IFDIR:  printf("Directorio\n");         break;
            case S_IFLNK:  printf("Enlace simbólico\n");   break;
            case S_IFREG:  printf("Fichero ordinario\n");  break;
            default:       printf("Desconocido\n");        break;
        }
        printf("Hora en la que se accedió al fichero por última vez: %s", ctime(&buf.st_atime));
        return 1;
    }

    else {
        perror("stat()");
        return -1;
    }
}

