/**
 * Online version: https://godbolt.org/z/xra44E9vb
 */

#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define INCREMENTS 10000

int counter = 0;

int main(void)
{
    // Utilizziamo la direttiva del preprocessore pragma per dire al compilatore di invocare openmp e
    // che questa sezione di codice deve essere eseguita in parallelo con un numero di threads pari a NUM_THREADS
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int i;

        for(i = 0; i < INCREMENTS; i++)
        {
            // Qui diciamo che siamo in una sezione critica
            // OpenMP si occuperà di gestirla
            #pragma omp critical
            {
                // ora solo un thread lavora su counter
                counter++;
            }
        }
    }

    printf("Final value of shared var: %d\n", counter);

    return 0;
}
