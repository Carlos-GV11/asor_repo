#include <stdio.h>
#include <time.h>
#include <locale.h>

int main() {

    char date[200];
    time_t t = time(0);
    struct tm *tm = localtime(&t);

    setlocale(LC_ALL, "");
    strftime(date, 200, "%A, %d de %B de %Y, %H:%M", tm);
    printf("Fecha de hoy: %s \n", date);
    
    return 1;

}