/**
 * Online version: https://godbolt.org/z/nM8sqjczz
 */

#include <stdio.h>
#include <threads.h>

#define NUM_THREADS 4
#define INCREMENTS 10000

int counter = 0;
mtx_t mutex;

int ThreadFunc(void* arg);

int main(void)
{
    int i;
    thrd_t threads[NUM_THREADS];

    if(mtx_init(&mutex, mtx_plain) != thrd_success)
    {
        printf("Error initializing mutex");
        return 1;
    }

    for(i = 0; i < NUM_THREADS; ++i)
    {
        if(thrd_create(&threads[i], &ThreadFunc, NULL) != thrd_success)
        {
            printf("There was an error creating a thread!\n");
            return 1;
        }
    }

    for(i = 0; i < NUM_THREADS; ++i)
    {
        if(thrd_join(threads[i], NULL) != thrd_success)
        {
            printf("There was an error joining a thread!\n");
            return 1;
        }
    }

    mtx_destroy(&mutex);

    printf("Final value of shared var: %d\n", counter);

    return 0;
}

int ThreadFunc(void* arg)
{
    int i;

    for(i = 0; i < INCREMENTS; i++)
    {
        mtx_lock(&mutex);
        counter++;
        mtx_unlock(&mutex);
    }

    return 0;
}