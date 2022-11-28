#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main() {
    sigset_t block_set;
    if (sigemptyset(&block_set) == 0) {
        if (sigaddset(&block_set, SIGINT) == 0 && sigaddset(&block_set, SIGTSTP) == 0) {
            if (sigprocmask(SIG_BLOCK, &block_set, NULL) == 0) {
                // char * s_sleep_secs = getenv("SLEEP_SECS");
                // if (strcmp(s_sleep_secs, "null") == 0) {
                    // int sleep_secs = atoi(s_sleep_secs);
                    sleep(20);
                    sigset_t pending_set;
                    if (sigpending(&pending_set) == 0) {
                        switch (sigismember(&pending_set, SIGINT)) { // Ctrl + C
                            case 1:
                                sigdelset(&block_set, SIGINT);
                                printf("La señal SIGINT ha sido recibida\n");
                                break;
                            case 0:
                                printf("La señal SIGINT no ha sido recibida\n");
                                break;
                            case -1:
                                perror("sigismember()");
                                return -1;
                        }

                        switch (sigismember(&pending_set, SIGTSTP)) { // Ctrl + Z
                            case 1:
                                sigdelset(&block_set, SIGTSTP);
                                printf("La señal SIGTSTP ha sido recibida\n");
                                break;
                            case 0:
                                printf("La señal SIGTSTP no ha sido recibida\n");
                                break;
                            case -1:
                                perror("sigismember()");
                                return -1;
                        }

                        if (sigprocmask(SIG_UNBLOCK, &block_set, NULL) == 0) {
                            return 1;
                        }

                        else {
                            perror("sigprocmask()");
                            return -1;
                        }
                    }

                    else {
                        perror("sigpending()");
                        return -1;
                    }
             // }   

             /* else {
                    perror("getenv()");
                    return -1;
                } */
            }

            else {
                perror("sigprocmask()");
                return -1;
            }
        }

        else {
            perror("sigaddset()");
            return -1;
        }
    }

    else {
        perror("sigemptyset()");
        return -1;
    }
}