#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Se añade para usar strcpy y strcat
#include <sys/wait.h>
#include <time.h> // Tambien sirve para generar números aleatorios
#include <unistd.h>

int main() {

    // Declaramos las variables
    pid_t pid;
    int fd[2]; // Descriptor de archivos. 0:lectura, 1:escritura
    char buffer[1000];
    char suma[1000], resta[30], producto[30], division[30];
    time_t t;
    int aleatorio1, aleatorio2;
    int i;

    pipe(fd); // Creamos el pipe
    pid = fork();

    if (pid == 0) {   // Proceso hijo (escribe)
        close(fd[0]); // Cerramos el descriptor de lectura
        // Generamos numero aleatorio entre 1 y 50
        // int aleatorio = min + rand() % (max - min + 1);
        srand((unsigned)time(&t));
        aleatorio1 = 1 + rand() % 50;
        aleatorio2 = 1 + rand() % 50;

        // Operaciones
        sprintf(suma, "%d + %d = %d\n", aleatorio1, aleatorio2,
                aleatorio1 + aleatorio2);
        sprintf(resta, "%d - %d = %d\n", aleatorio1, aleatorio2,
                aleatorio1 - aleatorio2);
        sprintf(producto, "%d * %d = %d\n", aleatorio1, aleatorio2,
                aleatorio1 * aleatorio2);
        sprintf(division, "%d / %d = %d\n", aleatorio1, aleatorio2,
                aleatorio1 / aleatorio2);
        // Concatenaciones
        strcat(suma, resta);
        strcat(suma, producto);
        strcat(suma, division);
        write(fd[1], suma, 800);

    } else {          // Proceso padre (lee)
        close(fd[1]); // Cerramos el descriptor de escritura
        wait(NULL);
        read(fd[0], buffer, 800);
        printf("\nLectura del mensaje del hijo:\n");
        printf(buffer);
    }
}