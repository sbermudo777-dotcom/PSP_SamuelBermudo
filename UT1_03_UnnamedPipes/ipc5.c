#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Se añade para usar strcpy y strcat
#include <sys/wait.h>
#include <unistd.h>

int main() {

    // Declaramos las variables
    pid_t pid;
    int pipe1[2]; // Pipe1: hijo escribe DNI, padre lee
    int pipe2[2]; // Pipe2: padre escribe letra, hijo lee
    char buffer[100];
    char dniStr[10];
    int dni;
    char letra[] = "TRWAGMYFPDXBNJZSQVHLCKE";
    char letraStr[2];

    // Creamos los pipes
    pipe(pipe1);
    pipe(pipe2);

    pid = fork();

    if (pid == 0) {   // Proceso hijo P2 (solicita DNI, escribe en pipe1, lee de pipe2)
        close(pipe1[0]); // Cerramos lectura en pipe1
        close(pipe2[1]); // Cerramos escritura en pipe2

        // Solicitamos el número de DNI
        printf("Introduce el número de tu DNI: ");
        scanf("%s", dniStr);
        write(pipe1[1], dniStr, strlen(dniStr) + 1);

        // Leemos la letra del pipe2
        read(pipe2[0], buffer, sizeof(buffer));
        printf("la letra del NIF es %s\n", buffer);

        // Cerramos los descriptores
        close(pipe1[1]);
        close(pipe2[0]);

    } else {          // Proceso padre P1 (lee de pipe1, calcula letra, escribe en pipe2)
        close(pipe1[1]); // Cerramos escritura en pipe1
        close(pipe2[0]); // Cerramos lectura en pipe2

        // Leemos el DNI del pipe1
        read(pipe1[0], buffer, sizeof(buffer));
        dni = atoi(buffer);
        dni %= 23;

        // Obtenemos la letra
        sprintf(letraStr, "%c", letra[dni]);

        // Escribimos la letra en pipe2
        write(pipe2[1], letraStr, strlen(letraStr) + 1);

        wait(NULL);

        // Cerramos los descriptores
        close(pipe1[0]);
        close(pipe2[1]);
    }

    return 0;
}