#include <stdio.h>
#include <mpi.h>

#define N 1000 // número de elementos en la serie

int main(int argc, char *argv[]) {
    int rank, size, i, j;
    int start, end;
    unsigned long long fib[N] = {0}; // array que contendrá los elementos de la serie de Fibonacci
    MPI_Init(&argc, &argv); // inicializar MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // obtener el rango del proceso actual
    MPI_Comm_size(MPI_COMM_WORLD, &size); // obtener el número total de procesos
    if (N < size) { // comprobar si hay más procesos que elementos en la serie
        size = N; // si es así, limitar el número de procesos a N
    }
    start = rank * (N / size); // calcular el índice de inicio de la sección de la serie que se calculará
    end = (rank + 1) * (N / size); // calcular el índice final de la sección de la serie que se calculará
    if (rank == size - 1) { // si este es el último proceso, asegurarse de que termine en N
        end = N;
    }
    // Inicializar los primeros dos elementos de la serie
    if (start == 0) { // si este es el primer proceso
        fib[start] = 0; // el primer elemento es 0
        if (N > 1) { // si hay al menos dos elementos en la serie
            fib[start + 1] = 1; // el segundo elemento es 1
            start += 2; // avanzar el índice de inicio dos posiciones
        } else {
            start += 1; // si solo hay un elemento, avanzar el índice de inicio una posición
        }
    }
    // Calcular la serie de Fibonacci
    for (i = start; i < end; i++) {
        fib[i] = fib[i-1] + fib[i-2]; // calcular cada elemento de la serie basado en los dos anteriores
    }
    // Enviar el último valor al proceso siguiente
    if (rank < size - 1) { // si este no es el último proceso
        MPI_Send(&fib[end-1], 1, MPI_UNSIGNED_LONG_LONG, rank+1, 0, MPI_COMM_WORLD); // enviar el último valor al siguiente proceso
    }
    // Recibir el último valor del proceso anterior
    if (rank > 0) { // si este no es el primer proceso
        MPI_Recv(&fib[start-1], 1, MPI_UNSIGNED_LONG_LONG, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // recibir el último valor del proceso anterior
    }
    // Imprimir la serie de Fibonacci
    if (rank == 0) { // si este es el primer proceso
        for (i = 0; i < N; i++) {
            printf("%llu ", fib[i]); // imprimir cada elemento de la serie
        }
        printf("\n"); // imprimir un salto de línea al final
    }
    MPI_Finalize(); // finalizar MPI
    return 0; // terminar el programa
}

