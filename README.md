# ThreadSemafori

Questo repository contiene il codice realizzato per il lavoro di gruppo "Thread e semafori in C" svolto in TPS nell'anno scolastico 2024/2025.

## Componenti del team

- Luigi Landi
- Francesco Gaeta
- Nicolò Guariniello
- Christian Aiello

## Panoramica

Il nostro compito era quello di mostrare come utilizzare thread e sincronizzarli con il linguaggio C.
Il codice è diviso in due parti:

-  Esempio solo thread (Range): Più thread (specificabili attraverso una macro) eseguono il calcolo indipendente di una somma di un range di numeri
-  Esempio thread + sincronizzazione (Shared var): Più thread (specificabili attraverso una macro) incrementano un contatore condiviso per tot volte. Questo richiede l'utilizzo di meccanismi di sincronizzazione come mutex e semafori.

Abbiamo scelto di mostrare più possibilità di gestione di thread e sincronizzazione in C:

- OpenMP (cartella openmp): un'interfaccia che diversi compilatori (principalmente gcc, clang e msvc) offrono per semplificare la programmazione multithreading in C e in C++. Si basa sull'utilizzo della direttiva del preprocessore ```#pragma``` per dare direttive al compilatore su come gestire delle parti di codice (es. eseguirla in parallelo, sincronizzare in un determinato punto ecc...). 
- Pthreads (Posix Threads, cartella pthreads): una libreria standard per la programmazione multithreading implementata in sistemi Unix-like.
- C11 threads (cartella stdhreads): implementazione standard della programmazione multithreading introdotta con lo standard C11. Offre un'interfaccia simile ma più semplice rispetto a Pthreads.
- Win32 Threads (cartella winthreads): implementazione della programmazione multithreading in sistemi Windows, inclusa con la Windows API.
- Semafori Unix (usati solo nell'esempio con sincornizzazione, usando pthreads per i thread): implemenatazione standard per sistemi Unix-like di semafori contatori (ma che noi usiamo come semafori binari).

## Riferimenti al codice

- Esempio solo thread:
  - [OpenMP](openmp/openmp_range.c)
  - [Pthreads](pthreads/pthreads_range.c)
  - [C11 threads](stdthreads/stdthreads_range.c)
  - [Windows threads](winthreads/winthreads_range.c)

- Esempio sincronizzazione:
  - [Non sincronizzato](openmp/openmp_shared_var_nosync.c)
  - [OpenMP](openmp/openmp_shared_var.c)
  - [Pthreads](pthreads/pthreads_shared_var.c)
  - [C11 threads](stdthreads/stdthreads_shared_var.c)
  - [Windows threads](winthreads/winthreads_shared_var.c)
  - [Semafori Unix](semaphore/semaphore_shared_var.c)

## Compilare ed eseguire

Per facilitare la compilazione è incluso un Makefile, utilizzabile in un terminale con ```make```.

Le regole definite sono del tipo <metodo>_<esempio>, per esempio:
- openmp_range
- winthreads_shared_var
- pthreads_shared_var

Di default vengono compilati tutti gli esempi tranne quelli che utilizzano i thread di windows (scelta fatta al fine di garantire compatibilità con Linux).

Per compilare gli esempi che utilizzano l'API di Windows "invocare" il Makefile utilizzando le regole che compilano gli esempi per windows.
```bash
make winthreads_range
make winthreads_shared_var
```

Gli esempi vengono compilati nella cartella del loro "metodo" di realizzazione dei thread, per esempio:
- openmp/opemp_range (.exe se compiliamo su windows)
- stdthreads/stdthreads_shared_var (.exe se compiliamo su windows)

Esecuzione:

- Linux:
```bash
./<metodo>/<esempio>
```

- Windows:
```cmd
.\<metodo>\<esempio>
```

## Conclusioni

Analizzando il codice possiamo notare come il metodo più semplice di realizzare la programmazione multithreading in C è OpenMP, in quanto con poche linee di codice possiamo gestire i thread e la loro sincronizzazione. Dobbiamo però ricordare che non tutti i compilatori implementano OpenMP.

Tra i metodi più "classici" (pthreads, c11 threads e win32 threads) quello più semplice da utilizzare e che garantisce più compatibilità è la libreria standard per i thread di C11. Anche questa però non è implementata in tutti i compilatori in quanto è una funzionalità standard opzionale.

I restanti sono invece adatti quando sappiamo di dover lavorare su un sistema operativo specifico e, possono offrire più controllo sulla gestione e sincronizzazione dei thread.
