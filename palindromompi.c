#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main() {
   char palabra[100];
   int i, longitud;
   int es_palindromo = 1;

   int num_procesos, rango;
   // Inicializar MPI
   MPI_Init(NULL, NULL);
   // Obtener el número de procesos
   MPI_Comm_size(MPI_COMM_WORLD, &num_procesos);
   // Obtener el rango del proceso actual
   MPI_Comm_rank(MPI_COMM_WORLD, &rango);

   // Verificar que el número de procesos sea 1
   if (num_procesos != 1) {
      if (rango == 0) {
         printf("Este programa debe ser ejecutado con un solo proceso\n");
      }
      MPI_Finalize();
      return 1;
   }

   // Solicitar al usuario que ingrese una palabra en el proceso 0
   if (rango == 0) {
      printf("Ingrese una palabra: ");
      scanf("%s", palabra);
   }

   // Transmitir la palabra desde el proceso 0 a todos los procesos
   MPI_Bcast(&palabra, 100, MPI_CHAR, 0, MPI_COMM_WORLD);

   // Calcular la longitud de la palabra
   longitud = strlen(palabra);

   // Verificar si la palabra es un palíndromo
   for (i = 0; i < longitud / 2; i++) {
      if (palabra[i] != palabra[longitud - i - 1]) {
         es_palindromo = 0;
         break;
      }
   }

   // Imprimir el resultado en el proceso 0
   if (rango == 0) {
      if (es_palindromo) {
         printf("%s Es palindromo\n", palabra);
      } else {
         printf("%s No es Palindromo\n", palabra);
      }
   }

   // Finalizar MPI
   MPI_Finalize();
   return 0;
}
