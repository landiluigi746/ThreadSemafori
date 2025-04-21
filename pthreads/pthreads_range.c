/**
 * Online version: https://godbolt.org/z/87YEnbMM4
 */

#include <stdio.h>
#include <time.h> // per tenere traccia del tempo di esecuzione
#include <stdint.h> // per int64_t, più grande di int che non basta per i risultati

// Includiamo la libreria pthread
#include <pthread.h>

// Definiamo il numero di thread da creare
#define NUM_THREADS 8

// Definiamo la grandezza del range di numeri su cui lavorano i thread
#define RANGE_SIZE 100000

// Creiamo una struttura che contiene i dati su cui lavorano i thread
typedef struct
{
    int start; // inizio del range
    int end; // fine del range
    int64_t sum; // somma totale (calcolata dai thread)
} RangeData;

// prototipo della funzione che verrà eseguita da ogni thread
// deve necessariamente resiture un puntatore void e prendere un puntatore void (l'argomento passato al thread)
// nel nostro caso passeremo il puntatore alla struttura RangeData su cui il thread lavora
void* ThreadFunc(void* arg);

int main(void)
{
    int i;
    clock_t start, end;

    // Creiamo un array di thread
    pthread_t threads[NUM_THREADS];
    RangeData rangesData[NUM_THREADS];

    // Inizializziamo i dati per i thread
    for(i = 0; i < NUM_THREADS; ++i)
    {
        rangesData[i].start = i * RANGE_SIZE;
        rangesData[i].end = rangesData[i].start + RANGE_SIZE;
    }

    printf("Beginning calculations in parallel ...\n");

    start = clock();

    // Creiamo i thread (vengono avviati automaticamente)
    for(i = 0; i < NUM_THREADS; ++i)
    {
        // Parametri:
        // - puntatore a pthread_t che deve essere inizializzato
        // - puntatore agli attributi da dare al thread (non necessari nel nostro caso)
        // - puntatore alla funzione che deve essere eseguita dal thread, che deve essere del tipo void* (void* arg)
        // - puntatore all'argomento da passare alla funzione
        if(pthread_create(&threads[i], NULL, &ThreadFunc, &rangesData[i]) != 0)
        {
            printf("There was an error creating a thread!\n");
            return 1;
        }
    }

    // Aspettiamo che tutti i thread finiscano
    for(i = 0; i < NUM_THREADS; ++i)
    {
        if(pthread_join(threads[i], NULL) != 0)
        {
            printf("There was an error joining a thread!\n");
            return 1;
        }
    }

    end = clock();

    // Calcoliamo e stampiamo il tempo passato
    printf("Elapsed time: %.2lf milliseconds\n", ((double) end - start) / (CLOCKS_PER_SEC / 1000));

    // Stampiamo i risultati finali
    for(i = 0; i < NUM_THREADS; ++i)
        printf("Thread %d calculated sum between %d and %d: %lld\n", i, rangesData[i].start, rangesData[i].end, rangesData[i].sum);

    return 0;
}

// Codice della funzione eseguita dai thread
void* ThreadFunc(void* arg)
{
    RangeData* rangeData = (RangeData*) arg;
    int i;

    rangeData->sum = 0;

    for(i = rangeData->start; i <= rangeData->end; ++i)
        rangeData->sum += i;

    return NULL;
}
