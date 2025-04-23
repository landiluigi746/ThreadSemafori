/**
 * Online version: https://godbolt.org/z/rcjqThzb5
 */

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define NUM_THREADS 4
#define INCREMENTS 10000

int counter = 0;

// dichiaramo il semaforo
sem_t semaphore;

void* ThreadFunc(void* arg);

int main(void)
{
    int i;
    pthread_t threads[NUM_THREADS];

    // inizializziamo il semaforo con valore di 1 (libero)
    if(sem_init(&semaphore, 0, 1) != 0)
    {
        printf("Error while initializing semaphore\n");
        return 1;
    }

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

    // distruggiamo il semaforo
    if(sem_destroy(&semaphore) != 0)
    {
        printf("Error while destroying semaphore\n");
        return 1;
    }

    return 0;
}

void* ThreadFunc(void* arg)
{
    int i;

    for(i = 0; i < INCREMENTS; i++)
    {
        // entriamo nella sezione critica: facciamo wait sul semaforo
        // ora solo un thread lavora su counter, gli altri aspetteranno
        // che il semaforo torni libero
        sem_wait(&semaphore);
        counter++;
        // usciamo dalla sezione critica: facciamo post sul semaforo e
        // entra un altro thread
        sem_post(&semaphore);
    }

    return NULL;
}
