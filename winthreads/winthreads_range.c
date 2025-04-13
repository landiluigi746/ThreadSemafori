#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <windows.h>

#define NUM_THREADS 8
#define RANGE_SIZE 100000

typedef struct
{
    int start;
    int end;
    int64_t sum;
} RangeData;

DWORD WINAPI ThreadFunc(LPVOID arg);

int main(void)
{
    int i;
    clock_t start, end;
    HANDLE threads[NUM_THREADS];
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
        threads[i] = CreateThread(NULL, 0, &ThreadFunc, &rangesData[i], 0, NULL);

        if(threads[i] == NULL)
        {
            printf("There was an error creating a thread!\n");
            return 1;
        }
    }

    WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);

    for(i = 0; i < NUM_THREADS; ++i)
    {
        if(CloseHandle(threads[i]) == 0)
        {
            printf("There was an error joining a thread\n");
            return 1;
        }
    }

    end = clock();

    printf("Elapsed time: %.2lf milliseconds\n", ((double) end - start) / (CLOCKS_PER_SEC / 1000));

    for(i = 0; i < NUM_THREADS; ++i)
        printf("Thread %d calculated sum between %d and %d: %lld\n", i, rangesData[i].start, rangesData[i].end, rangesData[i].sum);

    return 0;
}

DWORD WINAPI ThreadFunc(LPVOID arg)
{
    RangeData* rangeData = (RangeData*) arg;
    int i;

    rangeData->sum = 0;

    for(i = rangeData->start; i <= rangeData->end; ++i)
        rangeData->sum += i;

    return 0;
}
