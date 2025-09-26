#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void main() {
    pid_t pid_fork, pid_hijo;

    pid_fork = fork();

    if (pid_fork == -1) // Ha ocurrido un error
    {
        printf("No se ha podido crear el proceso hijo...\n");
        exit(-1);
    }

    if (pid_fork == 0) // Nos encontramos en el Proceso hijo
    {
        printf("Soy el proceso hijo.\n");
        printf("Alumno: Samuel Bermudo\n");
    } else // Nos encontramos en el Proceso padre
    {
        pid_hijo = wait(NULL); // espera la finalización del proceso hijo

        printf("Soy el proceso padre:\n");
        printf("Mi PID es %d, el PID de mi hijo es: %d.\n", getpid(), pid_fork);
    }

    exit(0);
}