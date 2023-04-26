#include <stdio.h>
#include <omp.h>

#define ROWS 100
#define COLS 100

int main() {
    // Declaración de las tres matrices y los índices para iterar sobre ellas
    int matriz1[ROWS][COLS], matriz2[ROWS][COLS], matriz3[ROWS][COLS];
    int i, j;

    // Llenar la primera matriz con números del 1 al 10000
    #pragma omp parallel for private(j)
    for (i = 0; i < ROWS; i++) { // Recorre las filas de la matriz1
        for (j = 0; j < COLS; j++) { // Recorre las columnas de la matriz1
            matriz1[i][j] = i * COLS + j + 1; // Asigna a cada posición el valor correspondiente
        }
    }

    // Llenar la segunda matriz con números del 1 al 10000
    #pragma omp parallel for private(j)
    for (i = 0; i < ROWS; i++) { // Recorre las filas de la matriz2
        for (j = 0; j < COLS; j++) { // Recorre las columnas de la matriz2
            matriz2[i][j] = i * COLS + j + 1; // Asigna a cada posición el valor correspondiente
        }
    }

    // Llenar la tercera matriz con el producto de cada número consigo mismo
    #pragma omp parallel for private(j)
    for (i = 0; i < ROWS; i++) { // Recorre las filas de la matriz3
        for (j = 0; j < COLS; j++) { // Recorre las columnas de la matriz3
            matriz3[i][j] = matriz1[i][j] * matriz2[i][j]; // Multiplica el valor de la matriz1 con el valor correspondiente en la matriz2
        }
    }

    // Imprimir la primera matriz
    printf("Matriz 1:\n");
    for (i = 0; i < ROWS; i++) { // Recorre las filas de la matriz1
        for (j = 0; j < COLS; j++) { // Recorre las columnas de la matriz1
            printf("%d\t", matriz1[i][j]); // Imprime el valor de la posición actual
        }
        printf("\n"); // Salta a la siguiente fila
    }

    // Imprimir la segunda matriz
    printf("\nMatriz 2:\n");
    for (i = 0; i < ROWS; i++) { // Recorre las filas de la matriz2
        for (j = 0; j < COLS; j++) { // Recorre las columnas de la matriz2
            printf("%d\t", matriz2[i][j]); // Imprime el valor de la posición actual
        }
        printf("\n"); // Salta a la siguiente fila
    }

    // Imprimir la tercera matriz
    printf("\nMatriz 3:\n");
    for (i = 0; i < ROWS; i++) { // Recorre las filas de la matriz3
        for (j = 0; j < COLS; j++) { // Recorre las columnas de la matriz3
            printf("%d\t", matriz3[i][j]); // Imprime el valor
        }
        printf("\n"); // Salta a la siguiente fila
    }

    return 0;
}




