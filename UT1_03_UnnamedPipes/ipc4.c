#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Se añade para usar strcpy y strcat
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main() {

    // Declaramos las variables
    pid_t pid;
    int pipe1[2]; // Pipe1: padre escribe, hijo lee
    int pipe2[2]; // Pipe2: hijo escribe, padre lee
    char buffer[100];
    int numero;
    long factorial = 1;
    int i;
    time_t t;

    // Creamos los pipes
    pipe(pipe1);
    pipe(pipe2);

    pid = fork();

    if (pid == 0) {   // Proceso hijo P2 (lee de pipe1, calcula, escribe en pipe2)
        close(pipe1[1]); // Cerramos escritura en pipe1
        close(pipe2[0]); // Cerramos lectura en pipe2

        // Leemos el número del pipe1
        read(pipe1[0], buffer, sizeof(buffer));
        numero = atoi(buffer);

        // Calculamos el factorial
        for (i = 1; i <= numero; i++) {
            factorial *= i;
        }

        // Convertimos el factorial a cadena y escribimos en pipe2
        sprintf(buffer, "%d != %ld", numero, factorial);
        write(pipe2[1], buffer, strlen(buffer) + 1);

        // Cerramos los descriptores
        close(pipe1[0]);
        close(pipe2[1]);

    } else {          // Proceso padre P1 (escribe en pipe1, lee de pipe2)
        close(pipe1[0]); // Cerramos lectura en pipe1
        close(pipe2[1]); // Cerramos escritura en pipe2

        // Generamos número aleatorio entre 0 y 10
        srand((unsigned) time(&t));
        numero = rand() % 11;

        // Mostramos mensaje y escribimos el número en pipe1
        printf("El proceso padre genera el numero %d en el pipe1\n", numero);
        sprintf(buffer, "%d", numero);
        write(pipe1[1], buffer, strlen(buffer) + 1);

        // Leemos el resultado del pipe2
        read(pipe2[0], buffer, sizeof(buffer));

        // Mostramos el resultado
        printf("El factorial calculado por el proceso hijo: %s\n", buffer);

        wait(NULL);

        // Cerramos los descriptores
        close(pipe1[1]);
        close(pipe2[0]);
    }

    return 0;
}