#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main() {
    int i;
    printf("RAND_MAX is %u\n", RAND_MAX);
    srand(time(0)); // Inicializa el generador de números aleatorios con el tiempo actual

    printf("random values from 0 to RAND_MAX\n");
    for(i = 0; i < 8; i++)
        printf("%d\n", rand()); // Imprime números aleatorios entre 0 y RAND_MAX

    printf("random values from 1 to 20\n");
    for(i = 0; i < 8; i++)
        printf("%d\n", (rand() % 20) + 1); // Imprime números aleatorios entre 1 y 20
}
