#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void main() {
    pid_t pid1, pid2;

    printf("Padre: AAA \n");

    pid1 = fork(); // Crea el primer hijo

    if (pid1 == 0) {
        printf("Hijo1: BBB \n");
    } else {
        pid2 = fork(); // Crea el segundo hijo
        if (pid2 == 0) {
            printf("Hijo2: CCC \n");
        } else {
            int status;
            waitpid(pid1, &status, 0); // Espera al hijo1
            waitpid(pid2, &status, 0); // Espera al hijo2
            printf("Padre: CCC \n");
        }
    }

    exit(0);
}