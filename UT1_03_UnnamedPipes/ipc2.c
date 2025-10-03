#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Se añade para usar strcpy y strcat
#include <sys/wait.h>
#include <unistd.h>

int main() {

    // Declaramos las variables
    pid_t pid;
    int fd[2]; // Descriptor de archivos. 0:lectura, 1:escritura
    char buffer[1000];
    char numeroStr[50];
    char mensaje[1000] = "";
    int suma = 0;
    int numero = 0;
    char sumaStr[20];

    pipe(fd); // Creamos el pipe
    pid = fork();

    if (pid == 0) {   // Proceso hijo
        close(fd[1]); // Cerramos el descriptor de escritura
        read(fd[0], buffer, 800);
        printf("\nLectura del mensaje del padre:\n");
        printf(buffer);
    } else {          // Proceso padre
        close(fd[0]); // Cerramos el descriptor de lectura
        while (1) {
            printf("Introduce un número: ");
            scanf("%s", numeroStr); // Scanner
            numero = atoi(numeroStr);
            suma += numero;

            if (strcmp(numeroStr, "+") == 0) { // Rompe el bucle infinito
                strcat(mensaje, "\nRecibido carácter + ");
                break;
            } else {
                // 1. Copiamos la primera parte
                strcat(mensaje, "\nNúmero a sumar: ");
                // 2. Concatenamos
                strcat(mensaje, numeroStr);
            }
        }

        sprintf(sumaStr, "%d", suma);
        strcat(mensaje, "\nLa suma total es igual a: ");
        strcat(mensaje, sumaStr);
        write(fd[1], mensaje, 800);
        wait(NULL);
    }
}