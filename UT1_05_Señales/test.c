#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> // Necesario para wait

// Variables globales para la comunicación (no es lo ideal, pero simple para el ejemplo)
int pipe_fd[2];
char buffer[50];

// Handler para P1 (Números Impares)
void handler_p1(int sig) {
    if (sig == SIGUSR1) {
        // P1 lee del pipe solo cuando se le notifica
        close(pipe_fd[1]);
        read(pipe_fd[0], buffer, sizeof(buffer));
        if (atoi(buffer) % 2 != 0) {
            printf("Número impar %s recibido por el proceso P1 con pid %d\n",
                   buffer, getpid());
        } else {
            // Esto solo ocurre si la señal se envió por error o si el read fue incompleto
             printf("P1 (%d) recibió la señal equivocada para un número par\n", getpid());
        }
    }
    // Una vez leído, el proceso puede terminar o esperar nuevas señales
    exit(0); 
}

// Handler para P2 (Números Pares)
void handler_p2(int sig) {
    if (sig == SIGUSR2) {
        // P2 lee del pipe solo cuando se le notifica
        close(pipe_fd[1]);
        read(pipe_fd[0], buffer, sizeof(buffer));
        if (atoi(buffer) % 2 == 0) {
            printf("Número par %s recibido por el proceso P2 con pid %d\n",
                   buffer, getpid());
        } else {
            // Esto solo ocurre si la señal se envió por error
             printf("P2 (%d) recibió la señal equivocada para un número impar\n", getpid());
        }
    }
    exit(0);
}

int main() {
    // Declaraciones corregidas
    pid_t pid1, pid2;
    int numero = 0;
    char numeroStr[20]; // CORREGIDO: Declarado como array

    // Creamos el pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Creacion de los procesos hijos (forma limpia)
    pid1 = fork();
    if (pid1 > 0) { // Si es el Padre
        pid2 = fork();
    }
    
    // --- LÓGICA DE PROCESOS ---

    if (pid1 == 0) { // Proceso Hijo 1 (Impares)
        signal(SIGUSR1, handler_p1); // Registra el handler
        signal(SIGUSR2, SIG_IGN);   // Ignora la señal de P2
        
        close(pipe_fd[1]); // Cierra el descriptor de escritura
        printf("P1 (%d) esperando la señal SIGUSR1...\n", getpid());
        
        // El hijo se suspende, liberando la CPU, hasta que recibe CUALQUIER señal
        pause(); 
        
        // Si sale de pause() sin terminar, es porque el handler ya hizo su trabajo.
        // Se puede añadir un bucle 'while(1) pause()' si esperara más trabajo.
        // En este caso, el handler termina el proceso.

    } else if (pid2 == 0) { // Proceso Hijo 2 (Pares)
        signal(SIGUSR2, handler_p2); // Registra el handler
        signal(SIGUSR1, SIG_IGN);   // Ignora la señal de P1

        close(pipe_fd[1]); // Cierra el descriptor de escritura
        printf("P2 (%d) esperando la señal SIGUSR2...\n", getpid());
        
        // El hijo se suspende hasta que recibe la señal
        pause();
        
    } else { // Proceso Padre
        close(pipe_fd[0]); // Cerramos el descriptor de lectura
        
        printf("Introduce un número: ");
        if (scanf("%d", &numero) != 1) {
            fprintf(stderr, "Error leyendo número.\n");
            exit(EXIT_FAILURE);
        }
        
        // Escribir en el pipe
        sprintf(numeroStr, "%d", numero); // Convertimos el entero a cadena
        write(pipe_fd[1], numeroStr, strlen(numeroStr) + 1); // +1 para incluir el '\0'
        
        // Enviar la señal al hijo correspondiente
        if (numero % 2 != 0) {
            printf("Padre (%d) envía SIGUSR1 a P1 (%d).\n", getpid(), pid1);
            kill(pid1, SIGUSR1);
        } else {
            printf("Padre (%d) envía SIGUSR2 a P2 (%d).\n", getpid(), pid2);
            kill(pid2, SIGUSR2);
        }
        
        close(pipe_fd[1]); // Cerramos el descriptor de escritura (crucial para la terminación)
        
        // El padre espera a que ambos hijos terminen
        wait(NULL); 
        wait(NULL);
        printf("Padre termina.\n");
    }

    return 0;
}
