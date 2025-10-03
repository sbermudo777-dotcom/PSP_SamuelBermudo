#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Se añade para usar strcpy y strcat
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main() {

    // Declaramos las variables
    pid_t pid;
    int fd[2]; // Descriptor de archivos. 0:lectura, 1:escritura
    char buffer[50];
    time_t t;
    // Buffer para construir el mensaje
    char mensaje[50];

    time(&t); // Otenemos la fecha y hora actual
    pipe(fd); // Creamos el pipe

    pid = fork(); // Se crea el proceso hijo

    if (pid == 0) { // Proceso hijo (lee)
        close(fd[1]);
        read(fd[0], buffer, 40);
        printf("Soy el proceso hijo con pid %d\n", getpid());
        printf(buffer);
    } else {          // Proceso padre (escribe)
        close(fd[0]); // Cerramos el descriptor de lectura por parte del padre
        time_t t = time(NULL);
        // 1. Copiamos la primera parte
        strcpy(mensaje, "Fecha/hora: ");
        // 2. Concatenamos la fecha/hora (ctime(&t) ya incluye un \n)
        strcat(mensaje, ctime(&t));
        write(fd[1], mensaje, 40);
        wait(NULL); // Espera a que termine el proceso hijo para que le de
                    // tiempo a leer el mensaje del padre
    }
}
