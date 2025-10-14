#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) { // fifo22

    // Declaración de variables
    int fp;
    int p, bytesleidos;
    char buffer[20];
    char numeroStr[4];
    int numeroInt;
    int factorialInt = 1;
    char factorial[4];
    int indice = 0;

    // LECTURA DEL PIPE02
    fp = open("PIPE02", 0); // (Lectura en PIPE02)
    printf("OBTENIENDO Información de fifo21...\n");
    printf("El número aleatorio generado es...");
    while ((bytesleidos = read(fp, buffer, 1)) > 0 && indice < 2) {
        printf("%c", buffer[0]);
        numeroStr[indice] = buffer[0];
        indice++;
    }
    close(fp);

    // ESCRITURA DEL PIPE Y FACTORIAL DEL NÚMERO GENERADO
    fp = open("PIPE02", 1); // Escritura en PIPE02

    numeroInt = atoi(numeroStr); // Conversión de la cadena a entero
    for (int i = 1; i <= numeroInt; i++) {
        factorialInt *= i;
    }

    // Escribiendo en el pipe PIPE02
    printf("\nMandando información a fifo21...\n");
    sprintf(factorial, "%d\n", factorialInt); // entero a cadena de carácteres
    write(fp, factorial, strlen(factorial));
    close(fp);

    numeroStr[indice] = '\0'; // Añadir terminador nulo

    return (0);
}