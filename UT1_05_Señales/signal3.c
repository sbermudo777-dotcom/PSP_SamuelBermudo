#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Manejador de la señal SIGINT
void fun_signal(int signum) {
    FILE *f = fopen("salidas.txt",
                    "a"); // Clase file, añade texto sin sobreescribir (append)
    if (f == NULL) {
        perror("Error al abrir el fichero 'salidas.txt'");
        exit(1);
    }

    // Obtener la hora actual
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    char hora[9]; // HH:MM:SS
    strftime(hora, sizeof(hora), "%H:%M:%S", tm);

    // Escribir en el fichero
    fprintf(f, "Señal SIGINT recibida a las %s\n", hora);
    fclose(f);

    printf("\nSeñal SIGINT recibida a las %s (registrada en salidas.txt)\n",
           hora);
}

int main() {
    // Asignar el manejador de señal
    signal(SIGINT, fun_signal);

    printf("Programa signal3 ejecutándose... (usa Ctrl+C para probar)\n");
    printf("Presiona Ctrl+ para terminar el programa.\n");

    // Bucle infinito
    while (1) {
        pause(); // Esperar señales
    }

    return 0;
}
