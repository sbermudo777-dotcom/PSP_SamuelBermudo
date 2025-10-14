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
    char buffer[3];
    int indice = 0;
    char numeroStr[3];
    int numeroInt;
    int factorialInt = 1;
    char factorial[20];

    p = mkfifo("FIFO1", 0666); // Permiso de lectura y escritura

    // LECTURA DEL PIPE Y CONVERSIÓN DEL NÚMERO A ENTERO
    fp1 = open("FIFO1", 0); // (Lectura en FIFO1)
    printf("OBTENIENDO Informacion...");
    while ((bytesleidos = read(fp1, buffer, 1)) > 0 && indice < 2) {
        printf("%c", buffer[0]);
        numeroStr[indice] = buffer[0];
        indice++;
    }
    close(fp1);
    numeroStr[indice] = '\0'; // ¡Añadir terminador nulo!

    // ESCRITURA DEL SEGUNDO PIPE Y FACTORIAL DEL NÚMERO GENERADO
    fp2 = open("FIFO2", 1); // Gestión del pipe FIFO2 (Escritura en FIFO2)

    numeroInt = atoi(numeroStr); // Conversión de la cadena a entero
    for (int i = 1; i <= numeroInt; i++) {
        factorialInt *= i;
    }

    // Escribiendo en el pipe FIFO1
    printf("Mandando información al fifo11...\n");
    printf("El factorial del número aleatorio generado es...");
    sprintf(factorial, "%d\n", factorialInt); // entero a cadena de carácteres
    write(fp2, factorial, strlen(factorial));
    close(fp2);

    return (0);
}
