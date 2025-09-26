#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void main() {
    pid_t pid1, pid2;
    pid_t actual_pid;
    int status; // Para el padre P1 e hijo P2 (Ambos padres)

    // Ambos procesos ejecutan fork()
    pid1 = fork(); // Crea P2 (Hijo 1)
    pid2 = fork(); // Crea P3 y P4

    if (pid1 == -1 || pid2 == -1) { // Ha ocurrido un error
        fprintf("Error: No se ha podido crear el proceso hijo...\n");
        exit(-1);
    }

    // Almacenar el PID actual para la lógica par/impar
    actual_pid = getpid(); // Para los 4 procesos

    // ==========================================================
    // SECCIÓN DEL PROCESO PADRE ORIGINAL (P1)
    // P1: pid1 > 0 (PID de P2)  &&  pid2 > 0 (PID de P3)
    // ==========================================================
    if (pid1 > 0 && pid2 > 0) {
        printf("Soy el Padre P1 (%d): Esperando a mis hijos P2 (%d) y "
               "P3 (%d)...\n",
               actual_pid, pid1, pid2);

        waitpid(pid1, &status, 0); // Espera a P2
        waitpid(pid2, &status, 0); // Espera a P3

        printf("Soy el Padre P1: Finalizando.\n");

        // ==========================================================
        // SECCIÓN DEL HIJO 1 (P2)
        // P2: pid1 == 0  &&  pid2 > 0 (PID de P4, su hijo)
        // ==========================================================
    } else if (pid1 == 0 && pid2 > 0) {
        waitpid(pid2, &status, 0); // P2 espera a P4 (PID de P4 está en pid2)
        if (actual_pid % 2 == 0) {
            printf("Proceso Hijo P2: Mi PID es %d y el PID de mi "
                   "padre es %d\n",
                   actual_pid, getppid());
        } else {
            printf("Proceso Hijo P2: Mi PID es %d\n", actual_pid);
        }

        printf("Proceso Hijo P2 (%d): Mi hijo P4 ha terminado. Finalizando.\n",
               actual_pid);

        // ==========================================================
        // SECCIÓN DEL HIJO 2 (P3)
        // P3: pid1 > 0 (PID de P2)  &&  pid2 == 0
        // ==========================================================
    } else if (pid1 > 0 && pid2 == 0) {

        // Lógica de impresión (aplicada al PID de P3)
        if (actual_pid % 2 == 0) {
            printf("Proceso Hijo P3: Mi PID es %d y el PID de mi "
                   "padre es %d\n",
                   actual_pid, getppid());
        } else {
            printf("Proceso Hijo P3: Mi PID es %d\n", actual_pid);
        }

        // ==========================================================
        // SECCIÓN DEL NIETO (P4)
        // P4: pid1 == 0  &&  pid2 == 0
        // ==========================================================
    } else { // if (pid1 == 0 && pid2 == 0)

        // Lógica de impresión (aplicada al PID de P4)
        if (actual_pid % 2 == 0) {
            printf("Proceso Nieto P4: Mi PID es %d y el PID de mi "
                   "padre es %d\n",
                   actual_pid, getppid());
        } else {
            printf("Proceso Nieto P4: Mi PID es %d\n", actual_pid);
        }
    }

    exit(0);
}
