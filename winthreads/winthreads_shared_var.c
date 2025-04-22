/**
 * Online version: https://godbolt.org/z/znro99WEM
 */

#include <stdio.h>
#include <windows.h>

#define NUM_THREADS 4
#define INCREMENTS 10000

int counter = 0;

// dichiaramo un oggetto di sezione critica (mutex)
CRITICAL_SECTION critSection;

DWORD WINAPI ThreadFunc(LPVOID arg);

int main(void)
{
    int i;
    HANDLE threads[NUM_THREADS];

    // inizializziamo la sezione critica
    InitializeCriticalSection(&critSection);

    for(i = 0; i < NUM_THREADS; ++i)
    {
        threads[i] = CreateThread(NULL, 0, &ThreadFunc, NULL, 0, NULL);

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

    // distruggiamo la sezione critica
    DeleteCriticalSection(&critSection);

    printf("Final value of shared var: %d\n", counter);

    return 0;
}

DWORD WINAPI ThreadFunc(LPVOID arg)
{
    int i;

    for(i = 0; i < INCREMENTS; i++)
    {
        // entriamo nella sezione critica: facciamo lock sul mutex
        // ora solo un thread lavora su counter
        EnterCriticalSection(&critSection);
        counter++;
        // usciamo dalla sezione critica: facciamo unlock sul mutex
        LeaveCriticalSection(&critSection);
    }

    return 0;
}
