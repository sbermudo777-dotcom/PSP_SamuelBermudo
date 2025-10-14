#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(void) { // fifo21

    // Declaración de variables
    int fp;
    int p, bytesleidos;
    char buffer[20];
    char numero[4];
    time_t t;
    int aleatorio;

    // Creando el pipe PIPE02
    p = mkfifo("PIPE02", 0666); // Permiso de lectura y escritura

    // Escritura en PIPE02
    fp = open("PIPE02", 1);

    // Generando número aleatorio
    srand((unsigned)time(&t));
    aleatorio = rand() % 11; // Aleatorio entre 0 y 10

    // Escribiendo en el pipe PIPE02
    printf("Mandando información al fifo22...\n");
    sprintf(numero, "%d", aleatorio); // entero a cadena de carácteres
    write(fp, numero, strlen(numero));
    close(fp);

    // Leyendo el pipe PIPE02
    fp = open("PIPE02", 0); // (Lectura en PIPE02)
    bytesleidos = read(fp, buffer, 1);
    printf("OBTENIENDO Informacion del PIPE02...\n");
    printf("El factorial del número aleatorio generado es...");
    while (bytesleidos > 0) {
        printf("%c", buffer[0]);
        bytesleidos = read(fp, buffer, 1); // leo  otro  byte
    }

    close(fp);

    // ELIMINAR LOS FIFOS
    unlink("PIPE02");
    printf("PIPE02 eliminado al finalizar la ejecución de fifo21.\n");

    return (0);
}