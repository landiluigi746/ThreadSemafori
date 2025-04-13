#include <stdio.h>
#include <time.h>
#include <omp.h>

#define NUM_THREADS 8
#define RANGE_SIZE 100000

typedef struct
{
    int start;
    int end;
    long sum;
} RangeData;

void ThreadFunc(RangeData* rangeData);

int main(void)
{
    int i;
    clock_t start, end;
    RangeData rangesData[NUM_THREADS];

    for(i = 0; i < NUM_THREADS; ++i)
    {
        rangesData[i].start = i * RANGE_SIZE;
        rangesData[i].end = rangesData[i].start + RANGE_SIZE;
    }

    printf("Beginning calculations in parallel ...\n");

    start = clock();

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        ThreadFunc(&rangesData[omp_get_thread_num()]);
    }

    end = clock();

    printf("Elapsed time: %.2lf milliseconds\n", ((double) end - start) / (CLOCKS_PER_SEC / 1000));

    for(i = 0; i < NUM_THREADS; ++i)
        printf("Thread %d calculated sum between %d and %d: %ld\n", i, rangesData[i].start, rangesData[i].end, rangesData[i].sum);

    return 0;
}

void ThreadFunc(RangeData* rangeData)
{
    int i;

    rangeData->sum = 0;

    for(i = rangeData->start; i <= rangeData->end; ++i)
        rangeData->sum += i;
}
