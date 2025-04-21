/**
 * Online version: https://godbolt.org/z/11Ex4x44P
 */

#include <stdio.h>
#include <time.h> // per tenere traccia del tempo di esecuzione
#include <stdint.h> // per int64_t, più grande di int che non basta per i risultati

// Includiamo la libreria di Windows
#include <windows.h>

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

// prototipo della funzione che verrà eseguita da ogni nthread
// deve necessariamente resiture DWORD (int senza segno) e prendere un puntatore void (l'argomento passato al thread)
// nel nostro caso passeremo il puntatore alla struttura RangeData su cui il thread lavora
DWORD WINAPI ThreadFunc(LPVOID arg);

int main(void)
{
    int i;
    clock_t start, end;

    // Creiamo un array di handle per i thread
    HANDLE threads[NUM_THREADS];
    RangeData rangesData[NUM_THREADS];

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
        // parametri:
        // - puntatore agli attributi di sicurezza del thread (nel nostro caso vanno bene quelli default quindi lasciamo NULL)
        // - dimensione dello stack del thread (0 lascia a quella di default)
        // - puntatore alla funzione che deve essere eseguita dal thread
        // - puntatore all'argomento da passare alla funzione
        // - flag di creazione del thread (0 per lasciare tutto di default)
        // - puntatore alla variabile dove deve essere memorizzato il tid del thread
        threads[i] = CreateThread(NULL, 0, &ThreadFunc, &rangesData[i], 0, NULL);

        if(threads[i] == NULL)
        {
            printf("There was an error creating a thread!\n");
            return 1;
        }
    }

    // Aspettiamo che tutti i thread finiscano
    WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);

    // Chiudiamo gli handle dei thread
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
