#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/*
  fechaHora: Función para obtener la fecha y hora actual
  en el formato dd/mm/yyyy hh:mm:ss.
 */
void fechaHora(char *buffer, size_t buffer_size) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buffer, buffer_size, "%d/%m/%Y %H:%M:%S", tm);
}

/*
  fun_signal es la función manejadora (handler) de la señal SIGINT.
  Muestra la hora de finalización y termina el programa.
 */
void fun_signal(int signum) {
    char buffer[30];
    fechaHora(buffer, sizeof(buffer));
    printf("\nFin del proceso %d: %s\n", getpid(), buffer);

    // Restaura la acción por defecto y termina
    signal(SIGINT, SIG_DFL);
    exit(0);
}

int main() {
    char inicio_buffer[30];
    pid_t pid = getpid();

    signal(SIGINT, fun_signal); // Registro del manejador para SIGINT

    // Mostrar hora de inicio
    fechaHora(inicio_buffer, sizeof(inicio_buffer));
    printf("Inicio del proceso %d: %s\n", pid, inicio_buffer);

    // Bucle infinito para mantener el proceso vivo y esperando la señal
    printf("Esperando la señal SIGINT (Ctrl+C)...\n");
    while (1) {
        sleep(1);
    }

    return 0; // Inalcanzable
}
