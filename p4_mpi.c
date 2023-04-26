#include <stdio.h>
#include <mpi.h> // Incluir la biblioteca MPI

#define ROWS 100
#define COLS 100

int main(int argc, char** argv) {
    int matriz1[ROWS][COLS], matriz2[ROWS][COLS], matriz3[ROWS][COLS];
    int i, j, contador = 1;
    int rank, size;

    MPI_Init(&argc, &argv); // Inicializar MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener el rango del proceso actual
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener el tamaño del comunicador
    
    // Llenar la primera matriz con números del 1 al 10000
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            matriz1[i][j] = contador++;
        }
    }

    contador = 1;

    // Llenar la segunda matriz con números del 1 al 10000
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            matriz2[i][j] = contador++;
        }
    }

    contador = 1;
    // Llenar la tercera matriz con el producto de cada número consigo mismo
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            matriz3[i][j] = (matriz1[i][j])*matriz2[i][j];
        }
        // Reiniciar el contador para la siguiente fila
    }

    // Imprimir la primera matriz
    if (rank == 3) { // Solo el proceso 3 imprime la primera matriz
        printf("Matriz 1:\n");
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLS; j++) {
                printf("%d\t", matriz1[i][j]);
            }
            printf("\n");
        }
    }

    // Imprimir la segunda matriz
    if (rank == 3) { // Solo el proceso 3 imprime la segunda matriz
        printf("\nMatriz 2:\n");
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLS; j++) {
                printf("%d\t", matriz2[i][j]);
            }
            printf("\n");
        }
    }

    // Imprimir la tercera matriz
    if (rank == 3) { // Solo el proceso 3 imprime la tercera matriz
        printf("\nMatriz 3:\n");
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLS; j++) {
                printf("%d\t", matriz3[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize(); // Finalizar MPI
    return 0;
}

