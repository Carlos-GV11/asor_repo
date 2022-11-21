#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("No se han introducido argumentos suficientes para la función.\n");
        return -1;
    }

    else if (argc > 2) {
        printf("Se han introducido demasiados argumentos para la función.\n");
        return -1;
    }

    else {
        char * ruta = argv[1];
        DIR * dir = opendir(ruta);
        if (dir != NULL) {
            struct dirent *d;
            short len = 0;
            while ((d = readdir(dir)) != NULL)  {
                printf("%s ", d->d_name);
                char ruta[100]; strcat(strcat(strcpy(ruta, argv[1]), "/"), d->d_name);
                switch (d->d_type) {
                    case DT_REG:
                        printf("");
                        struct stat buf1;
                        int rs1 = stat(ruta, &buf1);
                        if (rs1 == 0) {
                            if (buf1.st_mode & S_IXUSR && buf1.st_mode & S_IXGRP && buf1.st_mode & S_IXOTH) {
                                printf("*"); 
                            }
                        }
                        else {
                            perror("stat()");
                        }    
                    break;
                    case DT_LNK:
                        printf("");
                        char buf2[200];
                        int rs2 = readlink(ruta, buf2, 200);
                        if (rs2 != -1) {
                            printf("-> %s", buf2);
                        }
                        else {
                            perror("readlink()");
                        }
                    break;
                    case DT_DIR:  
                        printf("/");  
                    break;
                }
                len += d->d_reclen;
                printf("\n");
            }
            printf("Total length: %d\n", len);
            closedir(dir);
            return 1;
        }
        else {
            perror("dir()");
            return -1;
        }
    }
}