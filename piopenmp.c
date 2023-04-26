#include <stdio.h>
#include <omp.h>
#include <math.h>

#define NUM_STEPS 1000000

int main() {
    double pi = 0.0;
    double step = 1.0 / NUM_STEPS; // Tamaño del paso
    double x;

    #pragma omp parallel for reduction(+:pi) private(x) // Reducción en paralelo de pi y variable privada x
    for (int i = 0; i < NUM_STEPS; i++) {
        x = (i + 0.5) * step; // Calcular el valor de x
        pi += 4.0 / (1.0 + x*x); // Agregar el término a la suma de pi
    }

    pi *= step; // Multiplicar la suma por el tamaño del paso

    printf("El valor de pi con 1000 decimales es: %.1000f\n", (int) (log10(NUM_STEPS)+1), pi); // Imprimir el valor de pi con 1000 decimales
    
    return 0;
}

