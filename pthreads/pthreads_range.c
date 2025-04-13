#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREADS 8
#define RANGE_SIZE 100000

typedef struct
{
    int start;
    int end;
    long sum;
} RangeData;

void* ThreadFunc(void* arg);

int main(void)
{
    int i;
    clock_t start, end;
    pthread_t threads[NUM_THREADS];
    RangeData rangesData[NUM_THREADS];

    for(i = 0; i < NUM_THREADS; ++i)
    {
        rangesData[i].start = i * RANGE_SIZE;
        rangesData[i].end = rangesData[i].start + RANGE_SIZE;
    }

    printf("Beginning calculations in parallel ...\n");

    start = clock();

    for(i = 0; i < NUM_THREADS; ++i)
    {
        if(pthread_create(&threads[i], NULL, &ThreadFunc, &rangesData[i]) != 0)
        {
            printf("There was an error creating a thread!\n");
            return 1;
        }
    }

    for(i = 0; i < NUM_THREADS; ++i)
    {
        if(pthread_join(threads[i], NULL) != 0)
        {
            printf("There was an error creating a thread!\n");
            return 1;
        }
    }

    end = clock();

    printf("Elapsed time: %.2lf milliseconds\n", ((double) end - start) / (CLOCKS_PER_SEC / 1000));

    for(i = 0; i < NUM_THREADS; ++i)
        printf("Thread %d calculated sum between %d and %d: %ld\n", i, rangesData[i].start, rangesData[i].end, rangesData[i].sum);

    return 0;
}

void* ThreadFunc(void* arg)
{
    RangeData* rangeData = (RangeData*) arg;
    int i;

    rangeData->sum = 0;

    for(i = rangeData->start; i <= rangeData->end; ++i)
        rangeData->sum += i;

    return NULL;
}
