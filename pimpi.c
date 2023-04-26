#include <stdio.h>
#include <mpi.h>
#include <math.h>

#define NUM_STEPS 1000000

int main(int argc, char *argv[]) {
    int num_steps = NUM_STEPS;
    int rank, size;
    double pi = 0.0;
    double step = 1.0 / num_steps;
    double x;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int num_steps_per_process = num_steps / size;
    int start = rank * num_steps_per_process;
    int end = start + num_steps_per_process;

    for (int i = start; i < end; i++) {
        x = (i + 0.5) * step;
        pi += 4.0 / (1.0 + x * x);
    }

    double sum;
    MPI_Reduce(&pi, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double result = sum * step;
        printf("El valor de pi con 1000 decimales es: %.1000f\n", (int) (log10(num_steps) + 1), result);
    }

    MPI_Finalize();

    return 0;
}

