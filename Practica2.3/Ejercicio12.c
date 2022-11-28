#include <signal.h>
#include <stdio.h>
#include <errno.h>

int sigint_cont = 0;
int sigtstp_cont = 0;

void handler(int signal) {
    if (signal == SIGINT) sigint_cont++;
    if (signal == SIGTSTP) sigtstp_cont++;
}

int main() {
    struct sigaction act;
    act.sa_handler = handler;
    if (sigaction(SIGINT, &act, NULL) == 0 && sigaction(SIGTSTP, &act, NULL) == 0) {
        sigset_t set;
        while (sigint_cont + sigtstp_cont != 10) {
            sigsuspend(&set);
        }
        printf("Número de señales SIGINT recibidas: %d\n", sigint_cont);
        printf("Número de señales SIGTSTP recibidas: %d\n", sigtstp_cont);
        return 1;
    }

    else {
        perror("sigaction()");
        return -1;
    }
}