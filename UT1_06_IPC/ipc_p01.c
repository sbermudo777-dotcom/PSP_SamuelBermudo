#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() { // ipc_p01.c

    // Declarando variables
    int pipe1[2], pipe2[2];
    pid_t pid_p2, pid_p3;
    int status;

    // Creando el Pipe 1
    pipe(pipe1);

    // Creando proceso P2 (hijo de P1)
    pid_p2 = fork();
    if (pid_p2 < 0) { // Error
        perror("Error creando P2");
        exit(1);
    }

    if (pid_p2 == 0) {   // Proceso P2
        
        close(pipe1[1]); // Cerramos el descriptor de escritura

        // Declaramos las variables de lectura
        int op, op1, op2, result;
        
        read(pipe1[0], &op, sizeof(int));
        read(pipe1[0], &op1, sizeof(int));
        read(pipe1[0], &op2, sizeof(int));
        close(pipe1[0]); // Cerramos el descriptor de lectura

        // Creando el Pipe 2
        if (pipe(pipe2) == -1) {
            perror("Error creando Pipe 2");
            exit(1);
        }

        // Creando proceso P3 (hijo de P2)
        pid_p3 = fork();
        if (pid_p3 < 0) {
            perror("Error creando P3");
            exit(1);
        }

        if (pid_p3 == 0) { // Proceso P3
            close(pipe2[1]);
            int res;
            read(pipe2[0], &res, sizeof(int));
            close(pipe2[0]);
            printf("Proceso P3 pid = %d - Proceso padre pid = %d\n", getpid(),
                   getppid());
            printf("El resultado de la operación %d es %s\n", res,
                   (res % 2 == 0) ? "par" : "impar");
            printf("Termina proceso P3\n");
            exit(0);
        } else { // Proceso P2 (padre de P3)
            close(pipe2[0]);
            switch (op) {
            case 1:
                result = op1 + op2;
                break;
            case 2:
                result = op1 - op2;
                break;
            case 3:
                result = op1 * op2;
                break;
            case 4:
                result = op1 / op2;
                break;
            }
            printf("Proceso P2 pid = %d - Proceso padre pid = %d\n", getpid(),
                   getppid());
            printf("Operación: %d %s %d = %d\n", op1,
                   (op == 1)   ? "+"
                   : (op == 2) ? "-"
                   : (op == 3) ? "*"
                               : "/",
                   op2, result);
            write(pipe2[1], &result, sizeof(int));
            close(pipe2[1]);
            wait(NULL); // Espera a que P3 termine
            printf("Termina proceso P2\n");
            exit(0);
        }
    } else { // Proceso P1 (padre de P2) muestra el menú de la calculadora

        close(pipe1[0]); // Cerrando el descriptor de lectura

        // Declarando variables donde se almacenarán los mensajes
        int opcion, operando1, operando2;

        // Salida por pantalla para el Menú
        printf("Proceso P1 = %d", getpid());
        printf("**CALCULADORA **\n");
        printf("1. Sumar\n2. Restar\n3. Multiplicar\n4. División\n");
        printf("Seleccione la opción deseada: ");
        scanf("%d", &opcion);
        printf("Introduce el primer operando: ");
        scanf("%d", &operando1);
        printf("Introduce el segundo operando: ");
        scanf("%d", &operando2);

        // Escribiendo en el pipe 1 para comunicarse con P2
        write(pipe1[1], &opcion, sizeof(int));
        write(pipe1[1], &operando1, sizeof(int));
        write(pipe1[1], &operando2, sizeof(int));
        close(pipe1[1]); // Cerramos el descriptor de escritura

        waitpid(pid_p2, &status, 0); // Espera a que P2 termine

        printf("Termina proceso P1\n");
    }

    return 0;
}
