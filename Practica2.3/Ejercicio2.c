#include <sched.h>
#include <stdio.h>
#include <errno.h>

int main() {
    int rs = sched_getscheduler(0);
    if (rs >= 0) {
        printf("Política de planificación ");
        switch(rs) {
            case SCHED_FIFO: printf("FIFO\n");            break;
            case SCHED_RR: printf("Round-robin\n");       break;
            case SCHED_OTHER: printf("por defecto\n");    break;
            default: printf("desconocida\n");             break;
        }
        printf("Valores [máximo, mínimo] de la prioridad para la política de planificación: [%d, %d]\n", sched_get_priority_max(rs), sched_get_priority_min(rs));
        return 1;
    } 
    else {
        perror("sched_getscheduler()");
        return -1;
    }
}