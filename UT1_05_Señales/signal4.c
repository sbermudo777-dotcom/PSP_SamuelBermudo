#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Variables globales para controlar la alarma
int repeticiones = 0; // Número total de veces que sonará
int restantes = 0;    // Cuántas veces faltan
int intervalo = 0;    // Intervalo entre alarmas en segundos

// Manejador de la señal SIGALRM
void fun_signal(int signum) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char hora[9];
    strftime(hora, sizeof(hora), "%H:%M:%S", tm);

    printf("Señal de alarma recibida a las %s\n", hora);

    restantes--;
    if (restantes > 0) {
        alarm(intervalo); // Programar la siguiente alarma
    } else {
        printf("Alarma desactivada\n");
        exit(0);
    }
}

int main() {
    // Solicitar datos al usuario
    printf("¿Cuántas veces sonará la alarma?: ");
    scanf("%d", &repeticiones);

    printf("¿Cada cuántos segundos se repetirá la alarma?: ");
    scanf("%d", &intervalo);

    // Inicializar variables
    restantes = repeticiones;

    // Asignar el manejador de la señal SIGALRM
    signal(SIGALRM, fun_signal);

    printf("Alarma activada\n");

    // Activar la primera alarma
    alarm(intervalo);

    // Bucle de espera hasta que todas las alarmas se activen
    while (1) {
        pause(); // Espera señales
    }

    return 0;
}
