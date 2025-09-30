#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void main() {
    pid_t pid1, pid2, pid3, pid4;
    pid_t abuelo_pid;
    int status;

    // El proceso padre ejecuta fork()
    pid1 = fork(); // Crea P2

    if (pid1 == -1) { // Ha ocurrido un error
        printf("Error: No se ha podido crear el proceso hijo...\n");
        exit(-1);
    }

    // =======================================
    // SECCIÓN DEL PROCESO PADRE ORIGINAL (P1)
    // =======================================
    if (pid1 > 0) {
        waitpid(pid1, &status, 0); // Espera a P2
        printf("Soy el Padre P1 (%d): Finalizando.\n", getpid());
    } else { // Entra al proceso P2
        // ==============
        // SECCIÓN DE P2
        // ==============
        // Almacenar el PID del padre
        abuelo_pid = getppid(); // PID de P1

        pid2 = fork(); // P2 crea P3
        pid3 = fork(); // P2 crea P4 y P3 crea P5

        if (pid2 == -1 || pid3 == -1) { // Ha ocurrido un error
            printf("Error: No se ha podido crear el proceso hijo...\n");
            exit(-1);
        }

        if (pid1 == 0 && pid2 > 0 && pid3 > 0) { // Solo proceso P2
            waitpid(pid2, &status,
                    0); // P2 espera a P3 (PID de P3 está en pid2)
            waitpid(pid3, &status,
                    0); // P2 espera a P4 (PID de P4 está en pid3)
            printf("Proceso Hijo P2 (%d): Esperando a mis hijos P3 (%d) y "
                   "P4 (%d)...\n",
                   getpid(), pid2, pid3);
        } else if (pid1 == 0 && pid2 == 0 && pid3 > 0) { // Solo entra P3
            // ==============
            // SECCIÓN DE P3
            // ==============
            waitpid(pid3, &status,
                    0); // P3 espera a P5 (PID de P5 está en pid3)
            printf("Proceso Hijo P3 (%d), el PID de mi abuelo es (%d)...\n",
                   getpid(), abuelo_pid);
        } else if (pid1 == 0 && pid2 > 0 && pid3 == 0) { // Solo entra P4
            // ==============
            // SECCIÓN DE P4
            // ==============
            pid4 = fork();    // P4 crea P6
            if (pid1 == -1) { // Ha ocurrido un error
                printf("Error: No se ha podido crear el proceso hijo...\n");
                exit(-1);
            }

            if (pid4 > 0) { // Solo proceso P4
                waitpid(pid4, &status,
                        0); // P4 espera a P6
                printf("Proceso Hijo P4 (%d), el PID de mi abuelo es (%d)...\n",
                       getpid(), abuelo_pid);
            } else {
                // ==============
                // SECCIÓN DE P6
                // ==============
                printf("Proceso Hijo P6 (%d)...\n", getpid());
            }
        } else if (pid1 == 0 && pid2 == 0 && pid3 == 0) { // Solo entra P5
            // ==============
            // SECCIÓN DE P5
            // ==============
            printf("Proceso Hijo P5 (%d)...\n", getpid());
        }
    }

    exit(0);
}