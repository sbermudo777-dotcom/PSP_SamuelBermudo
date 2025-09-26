#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void main() {
    pid_t pid1, pid2, pid3;
    pid_t actual_pid;
    int status; // Para el padre P1 e hijo P2 (Ambos padres)

    /////////////////////
    //// PROCESO P1 ////
    ////////////////////
    pid1 = fork(); // P1 crea P2

    if (pid1 == -1) { // Ha ocurrido un error
        printf("Error: No se ha podido crear el proceso hijo...\n");
        exit(-1);
    }

    if (pid1 == 0) {
        /////////////////////
        //// PROCESO P2 ////
        ////////////////////
        pid2 = fork(); // P2 crea P3

        if (pid2 == -1) { // Ha ocurrido un error
            printf("Error: No se ha podido crear el proceso hijo...\n");
            exit(-1);
        }

        if (pid2 == 0) {
            /////////////////////
            //// PROCESO P3 ////
            ////////////////////
            pid3 = fork(); // P3 crea P4

            if (pid3 == -1) { // Ha ocurrido un error
                printf("Error: No se ha podido crear el proceso hijo...\n");
                exit(-1);
            }

            if (pid3 == 0) { // Proceso P4
                printf("Soy el proceso P4, mi PID es %d y el PID de mi padre "
                       "es %d.\n",
                       getpid(), getppid());
                printf("La suma de nuestros PID es %d.\n",
                       getpid() + getppid());
            } else {                       // Proceso P3
                waitpid(pid3, &status, 0); // Espera a P2
                printf("Soy el proceso P3, mi PID es %d y el PID de mi padre "
                       "es %d.\n",
                       getpid(), getppid());
                printf("La suma de nuestros PID es %d.\n",
                       getpid() + getppid());
            }

        } else {                       // Proceso P2
            waitpid(pid2, &status, 0); // Espera a P3
            printf(
                "Soy el proceso P2, mi PID es %d y el PID de mi padre es %d.\n",
                getpid(), getppid());
            printf("La suma de nuestros PID es %d.\n", getpid() + getppid());
        }

    } else {                       // Proceso P1
        waitpid(pid1, &status, 0); // Espera a P2
        printf("Soy el proceso P1, mi PID es %d y el PID de mi padre es %d.\n",
               getpid(), getppid());
        printf("La suma de nuestros PID es %d.\n", getpid() + getppid());
    }

    exit(0);
}