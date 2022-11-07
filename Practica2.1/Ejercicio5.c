#include <stdio.h>
#include <sys/utsname.h>
#include <errno.h>

int main() {

    struct utsname buf;

    int rt = uname(&buf);

    if (rt != -1) {
        printf("Operating system name: %s \n", buf.sysname);
        printf("Host name: %s \n", buf.nodename);
        printf("Operating system release: %s \n", buf.release);
        printf("Operating system version: %s \n", buf.version);
        printf("Hardware identifier: %s \n", buf.machine);
        return 1;
    }

    else {
        perror("uname()");
        return -1;
    }
}
