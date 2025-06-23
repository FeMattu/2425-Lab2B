# Riepilogo funzioni di libreria C

## Funzioni sui segnali

#### int kill(pid_t pid, int sig)
Invia il segnale 'sig' al processo indicato.

- `pid` (pid_t): identificatore di processo.
- `sig` (int): numero del segnale.

**Restituisce**: int.

#### int pause(void)
Sospende il processo fino alla ricezione di un segnale.



**Restituisce**: int.

#### unsigned int sleep(unsigned int seconds)
Sospende l'esecuzione per un numero di secondi.

- `seconds` (unsigned int): numero di secondi.

**Restituisce**: unsigned.

#### int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
Imposta un gestore per il segnale specificato.

- `signum` (int): parametro signum.
- `act` (const struct sigaction *): nuova azione per il segnale.
- `oldact` (struct sigaction *): azione precedente.

**Restituisce**: int.

#### int sigaddset(sigset_t *set, int signum)
Aggiunge un segnale all'insieme.

- `set` (sigset_t *): insieme di segnali.
- `signum` (int): parametro signum.

**Restituisce**: int.

#### int sigdelset(sigset_t *set, int signum)
Rimuove un segnale dall'insieme.

- `set` (sigset_t *): insieme di segnali.
- `signum` (int): parametro signum.

**Restituisce**: int.

#### int sigemptyset(sigset_t *set)
Inizializza l'insieme di segnali a vuoto.

- `set` (sigset_t *): insieme di segnali.

**Restituisce**: int.

#### int sigfillset(sigset_t *set)
Imposta tutti i segnali nell'insieme.

- `set` (sigset_t *): insieme di segnali.

**Restituisce**: int.

#### int sigqueue(pid_t pid, int sig, const union sigval value)
Invia un segnale con valore associato ad un processo.

- `pid` (pid_t): identificatore di processo.
- `sig` (int): numero del segnale.
- `value` (const union sigval): valore.

**Restituisce**: int.

#### int sigwait(const sigset_t *set, int *sig)
Attende in modo sincrono uno dei segnali indicati.

- `set` (const sigset_t *): insieme di segnali.
- `sig` (int *): numero del segnale.

**Restituisce**: int.

#### int sigwaitinfo(const sigset_t *set, siginfo_t *info)
Come sigwait ma restituisce informazioni aggiuntive.

- `set` (const sigset_t *): insieme di segnali.
- `info` (siginfo_t *): parametro info.

**Restituisce**: int.

#### int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset)
Modifica o legge la maschera dei segnali del thread corrente.

- `how` (int): operazione richiesta.
- `set` (const sigset_t *restrict): insieme di segnali.
- `oldset` (sigset_t *restrict): vecchio insieme di segnali.

**Restituisce**: int.

## Funzioni di sincronizzazione

### Semafori

#### int sem_close(sem_t *sem)
Chiude il descrittore di un semaforo aperto con sem_open.

- `sem` (sem_t *): semaforo da utilizzare.

**Restituisce**: int.

#### int sem_destroy(sem_t *sem)
Distrugge un semaforo inizializzato staticamente.

- `sem` (sem_t *): semaforo da utilizzare.

**Restituisce**: int.

#### int sem_init(sem_t *sem, int pshared, unsigned int value)
Inizializza un semaforo anonimo.

- `sem` (sem_t *): semaforo da utilizzare.
- `pshared` (int): visibilità tra processi.
- `value` (unsigned int): valore.

**Restituisce**: int.

#### sem_t *sem_open(const char *name, int oflag, ...)
Apre o crea un semaforo nominato.

- `name` (const char *): nome dell'oggetto.
- `oflag` (int): parametro oflag.
- `...`: argomenti variadic.

**Restituisce**: sem_t.

#### int sem_post(sem_t *sem)
Incrementa il valore del semaforo (sblocco).

- `sem` (sem_t *): semaforo da utilizzare.

**Restituisce**: int.

#### int sem_unlink(const char *name)
Rimuove un semaforo nominato dal filesystem.

- `name` (const char *): nome dell'oggetto.

**Restituisce**: int.

#### int sem_wait(sem_t *sem)
Decrementa il semaforo bloccando se il valore è zero.

- `sem` (sem_t *): semaforo da utilizzare.

**Restituisce**: int.

### Lock (mutex)

#### int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr)
Inizializza un mutex.

- `mutex` (pthread_mutex_t *restrict): mutex associato.
- `attr` (const pthread_mutexattr_t *restrict): attributi opzionali.

**Restituisce**: int.

#### int pthread_mutex_lock(pthread_mutex_t *mutex)
Acquisisce un mutex bloccandosi se necessario.

- `mutex` (pthread_mutex_t *): mutex associato.

**Restituisce**: int.

#### int pthread_mutex_unlock(pthread_mutex_t *mutex)
Rilascia un mutex precedentemente acquisito.

- `mutex` (pthread_mutex_t *): mutex associato.

**Restituisce**: int.

#### int pthread_mutex_destroy(pthread_mutex_t *mutex)
Distrugge un mutex.

- `mutex` (pthread_mutex_t *): mutex associato.

**Restituisce**: int.

### Variabili di condizione

#### int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr)
Inizializza una variabile di condizione.

- `cond` (pthread_cond_t *restrict): variabile di condizione.
- `attr` (const pthread_condattr_t *restrict): attributi opzionali.

**Restituisce**: int.

#### int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex)
Attende su una variabile di condizione sbloccando il mutex associato.

- `cond` (pthread_cond_t *restrict): variabile di condizione.
- `mutex` (pthread_mutex_t *restrict): mutex associato.

**Restituisce**: int.

#### int pthread_cond_signal(pthread_cond_t *cond)
Risveglia un thread in attesa sulla variabile di condizione.

- `cond` (pthread_cond_t *): variabile di condizione.

**Restituisce**: int.

#### int pthread_cond_broadcast(pthread_cond_t *cond)
Risveglia tutti i thread in attesa sulla variabile di condizione.

- `cond` (pthread_cond_t *): variabile di condizione.

**Restituisce**: int.

#### int pthread_cond_destroy(pthread_cond_t *cond)
Distrugge la variabile di condizione.

- `cond` (pthread_cond_t *): variabile di condizione.

**Restituisce**: int.

### Barriere

#### int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned int count)
Inizializza una barriera di sincronizzazione.

- `barrier` (pthread_barrier_t *restrict): barriera di sincronizzazione.
- `attr` (const pthread_barrierattr_t *restrict): attributi opzionali.
- `count` (unsigned int): numero di byte da elaborare.

**Restituisce**: int.

#### int pthread_barrier_wait(pthread_barrier_t *barrier)
Attende che tutti i thread raggiungano la barriera.

- `barrier` (pthread_barrier_t *): barriera di sincronizzazione.

**Restituisce**: int.

#### int pthread_barrier_destroy(pthread_barrier_t *barrier)
Distrugge una barriera di sincronizzazione.

- `barrier` (pthread_barrier_t *): barriera di sincronizzazione.

**Restituisce**: int.

### Thread

#### int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
Crea un nuovo thread eseguendo 'start_routine'.

- `thread` (pthread_t *): identificatore del thread.
- `attr` (const pthread_attr_t *): attributi opzionali.
- `start_routine` (void *(*) (void *)): funzione eseguita dal thread.
- `arg` (void *): argomento passato alla funzione.

**Restituisce**: int.

#### int pthread_join(pthread_t thread, void **retval)
Attende la terminazione del thread specificato.

- `thread` (pthread_t): identificatore del thread.
- `retval` (void **): valore di ritorno del thread.

**Restituisce**: int.

#### void pthread_exit(void *retval)
Termina il thread corrente restituendo un valore.

- `retval` (void *): valore di ritorno del thread.

**Restituisce**: void.

#### int pthread_detach(pthread_t thread)
Segnala che il thread può liberare autonomamente le proprie risorse alla terminazione.

- `thread` (pthread_t): identificatore del thread.

**Restituisce**: int.

#### int sched_yield(void)
Cede volontariamente la CPU ad altri thread.



**Restituisce**: int.

## Funzioni di lettura/scrittura su file

### POSIX

#### int open(const char *pathname, int flags, ...)
Apre un file e restituisce un file descriptor.

- `pathname` (const char *): percorso del file.
- `flags` (int): flag di apertura.
- `...`: argomenti variadic.

**Restituisce**: int.

#### int close(int fd)
Chiude il file descriptor 'fd'.

- `fd` (int): file descriptor su cui operare.

**Restituisce**: int.

#### ssize_t read(int fd, void *buf, size_t count)
Legge dati da un file descriptor.

- `fd` (int): file descriptor su cui operare.
- `buf` (void *): buffer di memoria.
- `count` (size_t): numero di byte da elaborare.

**Restituisce**: ssize_t.

#### ssize_t write(int fd, const void *buf, size_t count)
Scrive dati su un file descriptor.

- `fd` (int): file descriptor su cui operare.
- `buf` (const void *): buffer di memoria.
- `count` (size_t): numero di byte da elaborare.

**Restituisce**: ssize_t.

#### int pipe(int pipefd[2])
Crea una pipe anonima e restituisce due file descriptor.

- `pipefd` (int [2]): array con i due descrittori della pipe.

**Restituisce**: int.

#### int mkfifo(const char *pathname, mode_t mode)
Crea una FIFO con il nome indicato.

- `pathname` (const char *): percorso del file.
- `mode` (mode_t): modalità di apertura o permessi.

**Restituisce**: int.

#### int ftruncate(int fd, off_t length)
Tronca o estende il file aperto al nuovo 'length'.

- `fd` (int): file descriptor su cui operare.
- `length` (off_t): parametro length.

**Restituisce**: int.

### Standard C

#### FILE *fopen(const char *path, const char *mode)
Apre il file indicato e restituisce uno stream.

- `path` (const char *): percorso del file.
- `mode` (const char *): modalità di apertura o permessi.

**Restituisce**: FILE.

#### int fclose(FILE *stream)
Chiude lo stream di file indicato.

- `stream` (FILE *): puntatore a FILE.

**Restituisce**: int.

#### size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
Legge dati dallo stream in memoria.

- `ptr` (void *): puntatore a memoria.
- `size` (size_t): dimensione in byte.
- `nmemb` (size_t): numero di elementi.
- `stream` (FILE *): puntatore a FILE.

**Restituisce**: size_t.

#### size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
Scrive dati in un file dallo stream.

- `ptr` (const void *): puntatore a memoria.
- `size` (size_t): dimensione in byte.
- `nmemb` (size_t): numero di elementi.
- `stream` (FILE *): puntatore a FILE.

**Restituisce**: size_t.

#### int fprintf(FILE *stream, const char *format, ...)
Scrive dati formattati nello stream.

- `stream` (FILE *): puntatore a FILE.
- `format` (const char *): stringa di formato.
- `...`: argomenti variadic.

**Restituisce**: int.

#### int fscanf(FILE *stream, const char *format, ...)
Legge dati formattati dallo stream.

- `stream` (FILE *): puntatore a FILE.
- `format` (const char *): stringa di formato.
- `...`: argomenti variadic.

**Restituisce**: int.

#### int printf(const char *format, ...)
Stampa dati formattati su stdout.

- `format` (const char *): stringa di formato.
- `...`: argomenti variadic.

**Restituisce**: int.

#### int scanf(const char *format, ...)
Legge input formattato da stdin.

- `format` (const char *): stringa di formato.
- `...`: argomenti variadic.

**Restituisce**: int.

#### int fflush(FILE *stream)
Svuota il buffer dello stream.

- `stream` (FILE *): puntatore a FILE.

**Restituisce**: int.

#### int fseek(FILE *stream, long offset, int whence)
Imposta la posizione corrente nello stream.

- `stream` (FILE *): puntatore a FILE.
- `offset` (long): spiazzamento.
- `whence` (int): punto di riferimento.

**Restituisce**: int.

#### long ftell(FILE *stream)
Restituisce la posizione corrente nello stream.

- `stream` (FILE *): puntatore a FILE.

**Restituisce**: long.

#### void rewind(FILE *stream)
Riporta la posizione dello stream all'inizio del file.

- `stream` (FILE *): puntatore a FILE.

**Restituisce**: void.

#### ssize_t getline(char **lineptr, size_t *n, FILE *stream)
Legge una riga dallo stream allocando buffer se necessario.

- `lineptr` (char **): puntatore al buffer della linea.
- `n` (size_t *): dimensione del buffer.
- `stream` (FILE *): puntatore a FILE.

**Restituisce**: ssize_t.

#### int puts(const char *s)
Stampa una stringa seguita da newline su stdout.

- `s` (const char *): parametro s.

**Restituisce**: int.

#### int asprintf(char **strp, const char *fmt, ...)
Scrive l'output formattato in una stringa allocata dinamicamente.

- `strp` (char **): puntatore alla stringa allocata.
- `fmt` (const char *): stringa di formato.
- `...`: argomenti variadic.

**Restituisce**: int.

## Gestione memoria e IPC

### Allocazione memoria

#### void *malloc(size_t size)
Alloca 'size' byte di memoria.

- `size` (size_t): dimensione in byte.

**Restituisce**: void.

#### void free(void *ptr)
Libera la memoria allocata con malloc/realloc.

- `ptr` (void *): puntatore a memoria.

**Restituisce**: void.

#### void *realloc(void *ptr, size_t size)
Ridimensiona un blocco di memoria allocato.

- `ptr` (void *): puntatore a memoria.
- `size` (size_t): dimensione in byte.

**Restituisce**: void.

#### void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
Mappa un file o dispositivo in memoria.

- `addr` (void *): parametro addr.
- `length` (size_t): parametro length.
- `prot` (int): protezione della mappatura.
- `flags` (int): flag di apertura.
- `fd` (int): file descriptor su cui operare.
- `offset` (off_t): spiazzamento.

**Restituisce**: void.

#### int munmap(void *addr, size_t length)
Annulla una precedente mappatura di memoria.

- `addr` (void *): parametro addr.
- `length` (size_t): parametro length.

**Restituisce**: int.

### Memoria condivisa

#### int shm_open(const char *name, int oflag, mode_t mode)
Apre o crea un oggetto di memoria condivisa POSIX.

- `name` (const char *): nome dell'oggetto.
- `oflag` (int): parametro oflag.
- `mode` (mode_t): modalità di apertura o permessi.

**Restituisce**: int.

#### int shm_unlink(const char *name)
Rimuove un oggetto di memoria condivisa.

- `name` (const char *): nome dell'oggetto.

**Restituisce**: int.

## Controllo dei processi

#### pid_t fork(void)
Crea un nuovo processo duplicando quello corrente.



**Restituisce**: pid_t.

#### int execl(const char *path, const char *arg, ...)
Sostituisce il processo corrente eseguendo il programma indicato in 'path'.

- `path` (const char *): percorso del file.
- `arg` (const char *): argomento passato alla funzione.
- `...`: argomenti variadic.

**Restituisce**: int.

#### pid_t wait(int *wstatus)
Attende la terminazione di un processo figlio.

- `wstatus` (int *): stato di uscita.

**Restituisce**: pid_t.

#### void exit(int status)
Termina il processo restituendo 'status'.

- `status` (int): parametro status.

**Restituisce**: void.

#### pid_t getpid(void)
Restituisce l'identificatore del processo corrente.



**Restituisce**: pid_t.

#### pid_t getppid(void)
Restituisce l'identificatore del processo padre.



**Restituisce**: pid_t.

#### pid_t gettid(void)
Restituisce l'identificatore del thread corrente (Linux).



**Restituisce**: pid_t.

## Stringhe e caratteri

#### int atoi(const char *nptr)
Converte la stringa 'nptr' in un intero.

- `nptr` (const char *): parametro nptr.

**Restituisce**: int.

#### int strcmp(const char *s1, const char *s2)
Confronta due stringhe.

- `s1` (const char *): parametro s1.
- `s2` (const char *): parametro s2.

**Restituisce**: int.

#### size_t strlen(const char *s)
Calcola la lunghezza della stringa.

- `s` (const char *): parametro s.

**Restituisce**: size_t.

#### char *strdup(const char *s)
Duplica la stringa indicata allocando memoria.

- `s` (const char *): parametro s.

**Restituisce**: char.

#### char *strtok(char *restrict s, const char *restrict delim)
Estrae token da una stringa in base ai delimitatori.

- `s` (char *restrict): parametro s.
- `delim` (const char *restrict): parametro delim.

**Restituisce**: char.

#### char *strerror(int errnum)
Restituisce una stringa descrittiva dell'errore.

- `errnum` (int): parametro errnum.

**Restituisce**: char.

#### int strerror_r(int errnum, char *buf, size_t buflen)
Scrive in 'buf' una descrizione dell'errore 'errnum'.

- `errnum` (int): parametro errnum.
- `buf` (char *): buffer di memoria.
- `buflen` (size_t): parametro buflen.

**Restituisce**: int.

## Matematica e numeri casuali

#### int abs(int x)
Restituisce il valore assoluto di 'x'.

- `x` (int): parametro x.

**Restituisce**: int.

#### double sqrt(double x)
Calcola la radice quadrata di 'x'.

- `x` (double): parametro x.

**Restituisce**: double.

#### int rand(void)
Restituisce un numero pseudo-casuale.



**Restituisce**: int.

#### long int random(void)
Restituisce un numero pseudo-casuale (interfaccia BSD).



**Restituisce**: long.

#### void srand(unsigned int seed)
Imposta il seed per la sequenza generata da rand.

- `seed` (unsigned int): parametro seed.

**Restituisce**: void.

#### void srandom(unsigned int seed)
Imposta il seed per random.

- `seed` (unsigned int): parametro seed.

**Restituisce**: void.

## Utilità varie

#### void perror(const char *s)
Stampa il messaggio di errore relativo all'ultima chiamata fallita.

- `s` (const char *): parametro s.

**Restituisce**: void.

#### void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
Ordina un array usando l'algoritmo quicksort.

- `base` (void *): array da ordinare.
- `nmemb` (size_t): numero di elementi.
- `size` (size_t): dimensione in byte.
- `compar` (int (*)(const void *, const void *)): funzione di confronto.

**Restituisce**: void.

#### time_t time(time_t *tloc)
Restituisce l'ora corrente.

- `tloc` (time_t *): parametro tloc.

**Restituisce**: time_t.
