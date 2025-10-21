#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// fun_signal es la función manejadora para SIGINT (Ctrl+C).
void fun_signal(int signum) {
    printf("\nSeñal SIGINT (%d) recibida. Finalizando el proceso %d.\n", signum,
           getpid());
    exit(0);
}

int main() {
    pid_t pid = getpid();
    int segundos_transcurridos = 0;

    // Registro del manejador para SIGINT (Salida limpia)
    signal(SIGINT, fun_signal);

    printf(
        "Inicio del proceso %d. El contador se actualizará cada %d segundos.\n",
        pid, 5);
    printf("Presione Ctrl+C para terminar el programa.\n");

    // El bucle infinito usa sleep() para la espera
    while (1) {
        sleep(5); // Bloquea el proceso durante 5 segundos
        segundos_transcurridos +=
            5; // Una vez despierto, incrementamos el contador
        printf("Han transcurrido %d segundos\n", segundos_transcurridos);
    }

    return 0; // Inalcanzable
}
