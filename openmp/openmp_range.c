/**
 * Online version: https://godbolt.org/z/z3M8EMWPr
 */

#include <stdio.h>
#include <time.h> // per tenere traccia del tempo di esecuzione
#include <stdint.h> // per int64_t, più grande di int che non basta per i risultati

// Includiamo la libreria di openmp
#include <omp.h>

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
// con openmp abbiamo molta più flessibilità
// possiamo infatti definirla come vogliamo, senza restrizioni
// nel nostro caso la funzione non restituisce niente e prende il puntatore alla struttura RangeData su cui lavora il thread
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

    // Utilizziamo la direttiva del preprocessore pragma per dire al compilatore di invocare openmp e
    // che questa sezione di codice deve essere eseguita in parallelo con un numero di threads pari a NUM_THREADS
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        ThreadFunc(&rangesData[omp_get_thread_num()]);
    }

    end = clock();

    printf("Elapsed time: %.2lf milliseconds\n", ((double) end - start) / (CLOCKS_PER_SEC / 1000));

    for(i = 0; i < NUM_THREADS; ++i)
        printf("Thread %d calculated sum between %d and %d: %lld\n", i, rangesData[i].start, rangesData[i].end, rangesData[i].sum);

    return 0;
}

void ThreadFunc(RangeData* rangeData)
{
    int i;

    rangeData->sum = 0;

    for(i = rangeData->start; i <= rangeData->end; ++i)
        rangeData->sum += i;
}
