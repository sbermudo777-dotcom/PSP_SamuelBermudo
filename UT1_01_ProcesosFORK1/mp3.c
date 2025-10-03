#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid_P2, pid_P3;

    pid_P2 = fork(); // P1 crea a P2

    if (pid_P2 == -1) {
        printf("No se ha podido crear el proceso hijo P2...\n");
        exit(-1);
    }

    if (pid_P2 == 0) { // Proceso P2
        sleep(10);
        printf("Despierto\n");
    } else {             // Proceso P1
        pid_P3 = fork(); // P1 crea a P3

        if (pid_P3 == -1) {
            printf("No se ha podido crear el proceso hijo P3...\n");
            exit(-1);
        }

        if (pid_P3 == 0) { // Proceso P3
            printf(
                "Soy el proceso 3. Mi PID es %d, el PID de mi padre es: %d.\n",
                getpid(), getppid());
        } else { // Proceso P1 espera a ambos hijos
            int status;
            waitpid(pid_P2, &status, 0); // espera a P2
            waitpid(pid_P3, &status, 0); // espera a P3

            printf("Soy el proceso 1. Mi PID es %d, los PID de mis hijos son: "
                   "%d y %d.\n",
                   getpid(), pid_P2, pid_P3);
        }
    }

    exit(0);
}