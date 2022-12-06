#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main() {
    int p_h[2];
    int h_p[2];

    if (pipe(p_h) == 0 && pipe(h_p) == 0) {
        switch(fork()) {
            case -1:
                perror("fork()");
                return -1;

            case 0: 
                if (close(p_h[1]) == 0 && close(h_p[0]) == 0) {
                    char msg_read[256];
                    char msg_parent[1];
                    
                    int n;
                    for (n = 1; n <= 10; n++) {
                        ssize_t msg_bytes = read(p_h[0], msg_read, 256);
                        if (msg_bytes != -1) {
                            msg_read[msg_bytes] = '\0';
                            printf("Child recieved: %s", msg_read);
                            printf("Child waiting 1 sec...\n");
                            sleep(1);

                            if (n == 10) {
                                msg_parent[0] = 'q';
                            }
                            else {
                                msg_parent[0] = 'l';
                            }

                            if (write(h_p[1], msg_parent, 1) == -1) {
                                perror("write() on pipe child");
                                return -1;
                            }
                            else {
                                printf("Child sent char: %s\n\n", msg_parent);
                            }
                        }

                        else {
                            perror("read() on pipe child");
                            return -1;
                        }
                    }
                    break;
                }
                else {
                    perror("close() child");
                    return -1;
                }

            default:
                if (close(p_h[0]) == 0 && close(h_p[1]) == 0) {
                    char msg_write[256];
                    char msg_child[1] = {'s'};

                    while (msg_child[0] != 'q') { 
                        char buf[20];
                        strcat(strcat(strcpy(buf, "Parent recieved: "), msg_child), "\n");
                        write(1, buf, 20);

                        write(1, "Parent write a message: ", 24);
                        ssize_t msg_bytes = read(0, msg_write, 255);
                        if (msg_bytes != -1) {
                            msg_write[msg_bytes] = '\0';
                            if (write(p_h[1], msg_write, msg_bytes + 1) != -1) {
                                if (read(h_p[0], msg_child, 1) == -1) {
                                    perror("read() on pipe parent");
                                    return -1;
                                }
                            }
                            else {
                                perror("write() on pipe parent");
                                return -1;
                            }
                        }

                        else {
                            perror("read() on stdin parent");
                            return -1;
                        }
                    }
                    printf("Parent recieved: q\n");
                    printf("Parent stops writing...\n");
                    break;
                }

                else {
                    perror("close() parent");
                    return -1;
                }
        }

        return 1;
    }
    else {
        perror("pipe()");
        return -1;
    }
}