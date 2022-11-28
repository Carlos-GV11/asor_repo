#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
    pid_t pid = getpid();
    printf("[PID, PPID, PGID, SID] del proceso: [%d, %d, %d, %d]\n", pid, getppid(), getpgid(pid), getsid(pid));
    printf("Número máximo de ficheros que puede abrir el proceso: %ld\n", sysconf(_SC_OPEN_MAX));

    char buf[200]; getcwd(buf, 200);
    printf("Directorio de trabajo actual: %s\n", buf);
    return 1;
}