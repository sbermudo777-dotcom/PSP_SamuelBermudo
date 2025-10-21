#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// Manejador de la señal SIGALRM
// void fun_signal(int signum) { exit(0); }

int main() {

    // Declarar las variables
    pid_t pid1, pid2; // pid hijo1 e hijo2
    int fd[2];
    int numero = 0;
    char numeroStr[20];
    int status;

    // Creamos el pipe
    pipe(fd);

    // Creacion de los procesos hijos
    pid1 = fork();
    if (pid1 > 0) { // Solo el proceso padre P hace el segundo fork
        pid2 = fork();
    }

    // Comunicación mediante el pipe
    if (pid1 == 0) {  // Proceso hijo 1
        close(fd[1]); // Cerramos el descriptor de escritura
        read(fd[0], numeroStr, sizeof(numeroStr));
        close(fd[0]);
        if (atoi(numeroStr) % 2 != 0) {
            printf("Número impar %s recibido por el proceso P1 con pid %d\n",
                   numeroStr, getpid());
        }
    } else if (pid2 == 0) { // Proceso hijo 2
        close(fd[1]);       // Cerramos el descriptor de escritura
        read(fd[0], numeroStr, sizeof(numeroStr));
        close(fd[0]);
        if (atoi(numeroStr) % 2 == 0) {
            printf("Número par %s recibido por el proceso P2 con pid %d\n",
                   numeroStr, getpid());
        }
    } else {          // Proceso padre
        close(fd[0]); // Cerramos el descriptor de lectura por parte del padre
        printf("Introduce un número: ");
        scanf("%d", &numero);
        sprintf(numeroStr, "%d", numero); // Convertimos el entero a cadena
        write(fd[1], numeroStr, strlen(numeroStr) + 1);
        close(fd[1]);
        waitpid(pid1, &status, 0);
        waitpid(pid2, &status, 0);
    }

    // Asignar el manejador de la señal SIGALRM
    /*signal(SIGALRM, fun_signal);

    // Bucle de espera hasta que todas las alarmas se activen
    while (1) {
        pause(); // Espera señales
    }*/

    return 0;
}
