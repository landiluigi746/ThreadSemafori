/**
 * Online version: https://godbolt.org/z/jhvMhEWbG
 */

#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define INCREMENTS 10000

int counter = 0;

// creiamo un mutex globale e lo inizializziamo
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* ThreadFunc(void* arg);

int main(void)
{
    int i;
    pthread_t threads[NUM_THREADS];

    for(i = 0; i < NUM_THREADS; ++i)
    {
        if(pthread_create(&threads[i], NULL, &ThreadFunc, NULL) != 0)
        {
            printf("There was an error creating a thread!\n");
            return 1;
        }
    }

    for(i = 0; i < NUM_THREADS; ++i)
    {
        if(pthread_join(threads[i], NULL) != 0)
        {
            printf("There was an error joining a thread!\n");
            return 1;
        }
    }

    printf("Final value of shared var: %d\n", counter);

    return 0;
}

void* ThreadFunc(void* arg)
{
    int i;

    for(i = 0; i < INCREMENTS; i++)
    {
        // entriamo nella sezione critica: facciamo lock sul mutex
        // ora solo un thread lavora su counter
        pthread_mutex_lock(&mutex);
        counter++;
        // usciamo dalla sezione critica: facciamo unlock sul mutex
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}
