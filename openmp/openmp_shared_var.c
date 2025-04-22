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
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int i;

        for(i = 0; i < INCREMENTS; i++)
        {
            #pragma omp critical
            {
                counter++;
            }
        }
    }

    printf("Final value of shared var: %d\n", counter);

    return 0;
}
