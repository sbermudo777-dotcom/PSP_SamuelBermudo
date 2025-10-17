#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) { // fifo12

    // Declaración de variables
    int fp1, fp2;
    int p, bytesleidos;
    char buffer[4];
    int indice = 0;
    char numeroStr[3];
    int numeroInt;
    int factorialInt = 1;
    char factorial[20];

    p = mkfifo("FIFO2", 0666); // Permiso de lectura y escritura

    // LECTURA DEL PIPE FIFO1 Y CONVERSIÓN DEL NÚMERO A ENTERO
    fp1 = open("FIFO1", 0); // (Lectura en FIFO1)
    printf("OBTENIENDO Informacion del FIFO1...\n");
    printf("El número aleatorio generado es...");
    while ((bytesleidos = read(fp1, buffer, 1)) > 0 && indice < 2) {
        printf("%c", buffer[0]);
        numeroStr[indice] = buffer[0];
        indice++;
    }
    close(fp1);
    
    // ESCRITURA DEL SEGUNDO PIPE Y FACTORIAL DEL NÚMERO GENERADO
    fp2 = open("FIFO2", 1); // Escritura en FIFO2

    numeroInt = atoi(numeroStr); // Conversión de la cadena a entero
    for (int i = 1; i <= numeroInt; i++) {
        factorialInt *= i;
    }

    // Escribiendo en el pipe FIFO1
    printf("\nMandando información al fifo11...\n");
    sprintf(factorial, "%d\n", factorialInt); // entero a cadena de carácteres
    write(fp2, factorial, strlen(factorial));
    close(fp2);

    return (0);
}
