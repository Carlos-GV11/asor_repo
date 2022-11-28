#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main() {
    pid_t pid = fork();
    switch (pid) {
        case -1:
            perror("fork()");
            exit(1);
        case 0:
            printf("");
            pid_t pid_hijo = getpid();
            printf("[PID, PPID, PGID, SID] del proceso hijo: [%d, %d, %d, %d]\n", pid_hijo, getppid(), getpgid(pid_hijo), getsid(pid_hijo));
            int rs = chdir("/tmp");
            if (rs == -1) {
                perror("chdir()");
                exit(1);
            }
            else {
                char buf[200]; getcwd(buf, 200);
                printf("Directorio de trabajo actual: %s\n", buf);
            }
            char c_pid[10]; sprintf(c_pid, "%d", pid_hijo);
            char com[100]; strcat(strcat(strcpy(com, "ps -p "), c_pid), " -o pid,s");
            //system(com);
            break;
        default:
            //sleep(1);
            printf("");
            pid_t pid_padre = getpid();
            printf("[PID, PPID, PGID, SID] del proceso padre: [%d, %d, %d, %d]\n", pid_padre, getppid(), getpgid(pid_padre), getsid(pid_padre));
            break;
    }
    return 0;
}