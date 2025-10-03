#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void main() {
    pid_t pid2, pid3, pid4;
    int status;
    int acumulado = (int)getpid();

    // El proceso padre ejecuta fork()
    pid2 = fork(); // P1 crea P2
    pid3 = fork(); // P1 crea P3 y P2 crea P5

    if (pid2 == -1) { // Ha ocurrido un error
        printf("Error: No se ha podido crear el proceso hijo...\n");
        exit(-1);
    }

    if (pid2 > 0 && pid3 > 0) {
        // El proceso P1 define una variable acumulado igual al número de su pid
        waitpid(pid2, &status, 0); // Espera a P2
        waitpid(pid3, &status, 0); // Espera a P3
        printf("Soy el Padre P1: Finalizando.\n");
    } else {
        if (pid2 == 0 && pid3 > 0) {   // Solamente entra P2
            waitpid(pid3, &status, 0); // Espera a P5
            if (getpid() % 2 == 0) {
                acumulado += 10;
            } else {
                acumulado -= 100;
            }
            printf("Soy el hijo P2 (%d), mi padre es P1 (%d).\n", getpid(),
                   getppid());
            printf("Acumulado = %d\n", acumulado);
        } else if (pid2 > 0 && pid3 == 0) { // Solamente entra P3
            pid4 = fork();                  // P3 crea P4

            if (pid4 == -1) { // Ha ocurrido un error
                printf("Error: No se ha podido crear el proceso hijo...\n");
                exit(-1);
            }

            if (pid2 > 0 && pid3 == 0 && pid4 > 0) { // Solamente entra P3
                waitpid(pid4, &status, 0);           // Espera a P4
                if (getpid() % 2 == 0) {
                    acumulado += 10;
                } else {
                    acumulado -= 100;
                }
                printf("Soy el hijo P3 (%d), mi padre es P1 (%d).\n", getpid(),
                       getppid());
                printf("Acumulado = %d\n", acumulado);

            } else {
                if (getpid() % 2 == 0) {
                    acumulado += 10;
                } else {
                    acumulado -= 100;
                }
                printf("Soy el hijo P4 (%d), mi padre es P3 (%d).\n", getpid(),
                       getppid());
                printf("Acumulado = %d\n", acumulado);
            }

        } else if (pid2 == 0 && pid3 == 0) { // Solamente entra P5
            if (getpid() % 2 == 0) {
                acumulado += 10;
            } else {
                acumulado -= 100;
            }
            printf("Soy el hijo P5 (%d), mi padre es P2 (%d).\n", getpid(),
                   getppid());
            printf("Acumulado = %d\n", acumulado);
        }
    }
    exit(0);
}