#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* Variable global para almacenar el PID del proceso */
pid_t global_pid;

/*
  obtener_fecha_hora: Función auxiliar para obtener la fecha y hora actual
  en el formato dd/mm/yyyy hh:mm:ss.
 */
void obtener_fecha_hora(char *buffer, size_t size) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buffer, size, "%d/%m/%Y %H:%M:%S", tm);
}

/*
  fun_signal es la función manejadora (handler) de la señal SIGINT.
  Muestra la hora de finalización y termina el programa.
 */
void fun_signal(int signum) {
    char buffer[30];
    obtener_fecha_hora(buffer, sizeof(buffer));

    printf("\nFin del proceso %d: %s\n", global_pid, buffer);

    // Restaura la acción por defecto y termina (o simplemente termina con exit)
    signal(SIGINT, SIG_DFL);
    exit(0);
}

int main() {
    char inicio_buffer[30];

    global_pid = getpid();

    signal(SIGINT, fun_signal); // Registro del manejador para SIGINT

    // Mostrar hora de inicio
    obtener_fecha_hora(inicio_buffer, sizeof(inicio_buffer));
    printf("Inicio del proceso %d: %s\n", global_pid, inicio_buffer);

    // Bucle infinito para mantener el proceso vivo y esperando la señal
    while (1) {
        sleep(1);
    }

    return 0; // Inalcanzable
}
