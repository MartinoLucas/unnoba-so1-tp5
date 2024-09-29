#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pidP = getpid();  // Guardamos el PID del proceso padre original
    pid_t pid = 1;        // Inicializamos con un valor distinto de 0 para entrar en el bucle

    // Creamos los tres procesos hijos a partir del proceso padre original
    for (int i = 0; i < 3 && pid > 0; i++) {
        pid = fork();  // Intentamos hacer fork
        if (pid < 0) {
            perror("Error al hacer fork");
            exit(EXIT_FAILURE);
        }
        
        if (pid == 0) {
            // Código de los procesos hijos
            printf("Soy el hijo %d con PID: %d, hijo de: %d\n", i + 1, getpid(), getppid());

            // Si es el segundo hijo (segundo índice) crea dos niveles adicionales
            if (i == 1) {
                for (int j = 0; j < 2; j++) {
                    pid = fork();  // Creamos el hijo y nieto del segundo hijo
                    if (pid < 0) {
                        perror("Error al hacer fork");
                        exit(EXIT_FAILURE);
                    }

                    if (pid == 0) {
                        // Código para el nieto y bisnieto del segundo hijo
                        printf("Soy un subproceso con PID: %d, hijo de: %d\n", getpid(), getppid());
                    } else {
                        wait(NULL); // Espera que el hijo termine antes de seguir
                        break; // El proceso padre de esta rama termina el ciclo
                    }
                }
            }
            exit(0);  // Los hijos originales deben terminar aquí
        }
    }

    // El proceso padre espera a que todos sus hijos directos terminen
    if (getpid() == pidP) {
        for (int i = 0; i < 3; i++) {
            wait(NULL);  // Espera que los tres hijos originales terminen
        }
    }

    // Mensaje final del proceso padre original
    if (getpid() == pidP) {
        printf("Soy el proceso padre original con PID: %d. Todos mis hijos han terminado.\n", getpid());
    }

    return 0;
}

