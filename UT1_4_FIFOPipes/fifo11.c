#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h> // Tambien sirve para generar números aleatorios
#include <unistd.h>

int main() { // fifo11
    // Declaramos las variables
    int fp1, fp2;
    int p, bytesleidos;
    char buffer[20];
    char numero[3];
    time_t t;
    int aleatorio;

    p = mkfifo("FIFO1", 0666); // Permiso de lectura y escritura

    fp1 = open("FIFO1", 1); // Escritura en FIFO1

    // Generando número aleatorio
    srand((unsigned)time(&t));
    aleatorio = rand() % 11; // Aleatorio entre 0 y 10

    // Escribiendo en el pipe FIFO1
    printf("Mandando información al fifo12...\n");
    sprintf(numero, "%d", aleatorio); // entero a cadena de carácteres
    write(fp1, numero, strlen(numero));
    close(fp1);

    // Leyendo el pipe FIFO2
    fp2 = open("FIFO2", 0); // (Lectura en FIFO2)
    bytesleidos = read(fp2, buffer, 1);
    printf("OBTENIENDO Informacion del FIFO2...\n");
    printf("El factorial del número aleatorio generado es...");
    while (bytesleidos > 0) {
        printf("%c", buffer[0]);
        bytesleidos = read(fp2, buffer, 1); // leo  otro  byte
    }
    close(fp2);

    return 0;
}
