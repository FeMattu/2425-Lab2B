# Riepilogo funzioni di libreria C

## Funzioni sui segnali

#### int kill(pid_t pid, int sig)
Invia il segnale 'sig' al processo indicato.

- `pid` (pid_t): identificatore di processo. Il tipo `pid_t` viene utilizzato per specificare un valore numerico.
- `sig` (int): numero del segnale. Il tipo `int` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (10segnali/segnali.c:21):
```c
kill(getpid(),SIGUSR1); // manda SIGUSR1 a se stesso
```


#### int pause(void)
Sospende il processo fino alla ricezione di un segnale.



**Restituisce**: int.

Esempio (10segnali/segnali.c:66):
```c
pause();    // attende un segnale
```


#### unsigned int sleep(unsigned int seconds)
Sospende l'esecuzione per un numero di secondi.

- `seconds` (unsigned int): numero di secondi. Il tipo `unsigned int` viene utilizzato per specificare un valore numerico.

**Restituisce**: unsigned.

Esempio (08condVar/rw.c:90):
```c
sleep(1);
```


#### int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
Imposta un gestore per il segnale specificato.

- `signum` (int): parametro signum. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `act` (const struct sigaction *): nuova azione per il segnale. Il tipo `const struct sigaction *` viene utilizzato per gestire un puntatore.
- `oldact` (struct sigaction *): azione precedente. Il tipo `struct sigaction *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (10segnali/segnali.c:41):
```c
sigaction(SIGUSR1,&sa,NULL);  // handler per USR1
```


#### int sigaddset(sigset_t *set, int signum)
Aggiunge un segnale all'insieme.

- `set` (sigset_t *): insieme di segnali. Il tipo `sigset_t *` viene utilizzato per gestire un puntatore.
- `signum` (int): parametro signum. Il tipo `int` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (08condVar/heap.c:81):
```c
sigaddset(&set, SIGINT);
```


#### int sigdelset(sigset_t *set, int signum)
Rimuove un segnale dall'insieme.

- `set` (sigset_t *): insieme di segnali. Il tipo `sigset_t *` viene utilizzato per gestire un puntatore.
- `signum` (int): parametro signum. Il tipo `int` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (10segnali/segnali.c:40):
```c
// sigdelset(&sa.sa_mask,SIGUSR1);   // ... tranne SIGUSR1
```


#### int sigemptyset(sigset_t *set)
Inizializza l'insieme di segnali a vuoto.

- `set` (sigset_t *): insieme di segnali. Il tipo `sigset_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/heap.c:80):
```c
sigemptyset(&set);
```


#### int sigfillset(sigset_t *set)
Imposta tutti i segnali nell'insieme.

- `set` (sigset_t *): insieme di segnali. Il tipo `sigset_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (10segnali/segnali.c:39):
```c
sigfillset(&sa.sa_mask);          // tutti i segnali nella maschera ...
```


#### int sigqueue(pid_t pid, int sig, const union sigval value)
Invia un segnale con valore associato ad un processo.

- `pid` (pid_t): identificatore di processo. Il tipo `pid_t` viene utilizzato per specificare un valore numerico.
- `sig` (int): numero del segnale. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `value` (const union sigval): valore. Il tipo `const union sigval` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (10segnali/alice.c:57):
```c
sigqueue(bob_pid, SIGRTMIN, v);
```


#### int sigwait(const sigset_t *set, int *sig)
Attende in modo sincrono uno dei segnali indicati.

- `set` (const sigset_t *): insieme di segnali. Il tipo `const sigset_t *` viene utilizzato per gestire un puntatore.
- `sig` (int *): numero del segnale. Il tipo `int *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/heap.c:86):
```c
int e = sigwait(&set, &s);
```


#### int sigwaitinfo(const sigset_t *set, siginfo_t *info)
Come sigwait ma restituisce informazioni aggiuntive.

- `set` (const sigset_t *): insieme di segnali. Il tipo `const sigset_t *` viene utilizzato per gestire un puntatore.
- `info` (siginfo_t *): parametro info. Il tipo `siginfo_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (10segnali/alice.c:51):
```c
int signo = sigwaitinfo(&mask, &info);
```


#### int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset)
Modifica o legge la maschera dei segnali del thread corrente.

- `how` (int): operazione richiesta. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `set` (const sigset_t *restrict): insieme di segnali. Il tipo `const sigset_t *restrict` viene utilizzato per gestire un puntatore.
- `oldset` (sigset_t *restrict): vecchio insieme di segnali. Il tipo `sigset_t *restrict` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/heap.c:82):
```c
pthread_sigmask(SIG_BLOCK, &set, NULL);
```


## Funzioni di sincronizzazione

### Semafori

#### int sem_close(sem_t *sem)
Chiude il descrittore di un semaforo aperto con sem_open.

- `sem` (sem_t *): semaforo da utilizzare. Il tipo `sem_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:197):
```c
int e = sem_close(s);
```


#### int sem_destroy(sem_t *sem)
Distrugge un semaforo inizializzato staticamente.

- `sem` (sem_t *): semaforo da utilizzare. Il tipo `sem_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:229):
```c
int e = sem_destroy(sem);
```


#### int sem_init(sem_t *sem, int pshared, unsigned int value)
Inizializza un semaforo anonimo.

- `sem` (sem_t *): semaforo da utilizzare. Il tipo `sem_t *` viene utilizzato per gestire un puntatore.
- `pshared` (int): visibilità tra processi. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `value` (unsigned int): valore. Il tipo `unsigned int` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:219):
```c
int e = sem_init(sem,pshared,value);
```


#### sem_t *sem_open(const char *name, int oflag, ...)
Apre o crea un semaforo nominato.

- `name` (const char *): nome dell'oggetto. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `oflag` (int): parametro oflag. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `...`: argomenti variadic.

**Restituisce**: sem_t.

Esempio (08condVar/xerrori.c:186):
```c
sem_t *s = sem_open(name,oflag,mode,value);
```


#### int sem_post(sem_t *sem)
Incrementa il valore del semaforo (sblocco).

- `sem` (sem_t *): semaforo da utilizzare. Il tipo `sem_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:240):
```c
int e = sem_post(sem);
```


#### int sem_unlink(const char *name)
Rimuove un semaforo nominato dal filesystem.

- `name` (const char *): nome dell'oggetto. Il tipo `const char *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:208):
```c
int e = sem_unlink(name);
```


#### int sem_wait(sem_t *sem)
Decrementa il semaforo bloccando se il valore è zero.

- `sem` (sem_t *): semaforo da utilizzare. Il tipo `sem_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:250):
```c
int e = sem_wait(sem);
```


### Lock (mutex)

#### int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr)
Inizializza un mutex.

- `mutex` (pthread_mutex_t *restrict): mutex associato. Il tipo `pthread_mutex_t *restrict` viene utilizzato per gestire un puntatore.
- `attr` (const pthread_mutexattr_t *restrict): attributi opzionali. Il tipo `const pthread_mutexattr_t *restrict` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:100):
```c
int e = pthread_mutex_init(mutex, attr);
```


#### int pthread_mutex_lock(pthread_mutex_t *mutex)
Acquisisce un mutex bloccandosi se necessario.

- `mutex` (pthread_mutex_t *): mutex associato. Il tipo `pthread_mutex_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:120):
```c
int e = pthread_mutex_lock(mutex);
```


#### int pthread_mutex_unlock(pthread_mutex_t *mutex)
Rilascia un mutex precedentemente acquisito.

- `mutex` (pthread_mutex_t *): mutex associato. Il tipo `pthread_mutex_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:130):
```c
int e = pthread_mutex_unlock(mutex);
```


#### int pthread_mutex_destroy(pthread_mutex_t *mutex)
Distrugge un mutex.

- `mutex` (pthread_mutex_t *): mutex associato. Il tipo `pthread_mutex_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:110):
```c
int e = pthread_mutex_destroy(mutex);
```


### Variabili di condizione

#### int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr)
Inizializza una variabile di condizione.

- `cond` (pthread_cond_t *restrict): variabile di condizione. Il tipo `pthread_cond_t *restrict` viene utilizzato per gestire un puntatore.
- `attr` (const pthread_condattr_t *restrict): attributi opzionali. Il tipo `const pthread_condattr_t *restrict` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:262):
```c
int e = pthread_cond_init(cond,attr);
```


#### int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex)
Attende su una variabile di condizione sbloccando il mutex associato.

- `cond` (pthread_cond_t *restrict): variabile di condizione. Il tipo `pthread_cond_t *restrict` viene utilizzato per gestire un puntatore.
- `mutex` (pthread_mutex_t *restrict): mutex associato. Il tipo `pthread_mutex_t *restrict` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:282):
```c
int e = pthread_cond_wait(cond,mutex);
```


#### int pthread_cond_signal(pthread_cond_t *cond)
Risveglia un thread in attesa sulla variabile di condizione.

- `cond` (pthread_cond_t *): variabile di condizione. Il tipo `pthread_cond_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:292):
```c
int e = pthread_cond_signal(cond);
```


#### int pthread_cond_broadcast(pthread_cond_t *cond)
Risveglia tutti i thread in attesa sulla variabile di condizione.

- `cond` (pthread_cond_t *): variabile di condizione. Il tipo `pthread_cond_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:302):
```c
int e = pthread_cond_broadcast(cond);
```


#### int pthread_cond_destroy(pthread_cond_t *cond)
Distrugge la variabile di condizione.

- `cond` (pthread_cond_t *): variabile di condizione. Il tipo `pthread_cond_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:272):
```c
int e = pthread_cond_destroy(cond);
```


### Barriere

#### int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned int count)
Inizializza una barriera di sincronizzazione.

- `barrier` (pthread_barrier_t *restrict): barriera di sincronizzazione. Il tipo `pthread_barrier_t *restrict` viene utilizzato per gestire un puntatore.
- `attr` (const pthread_barrierattr_t *restrict): attributi opzionali. Il tipo `const pthread_barrierattr_t *restrict` viene utilizzato per gestire un puntatore.
- `count` (unsigned int): numero di byte da elaborare. Il tipo `unsigned int` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:142):
```c
int e = pthread_barrier_init(barrier, attr, count);
```


#### int pthread_barrier_wait(pthread_barrier_t *barrier)
Attende che tutti i thread raggiungano la barriera.

- `barrier` (pthread_barrier_t *): barriera di sincronizzazione. Il tipo `pthread_barrier_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:162):
```c
int e = pthread_barrier_wait(barrier);
```


#### int pthread_barrier_destroy(pthread_barrier_t *barrier)
Distrugge una barriera di sincronizzazione.

- `barrier` (pthread_barrier_t *): barriera di sincronizzazione. Il tipo `pthread_barrier_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:152):
```c
int e = pthread_barrier_destroy(barrier);
```


### Thread

#### int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
Crea un nuovo thread eseguendo 'start_routine'.

- `thread` (pthread_t *): identificatore del thread. Il tipo `pthread_t *` viene utilizzato per gestire un puntatore.
- `attr` (const pthread_attr_t *): attributi opzionali. Il tipo `const pthread_attr_t *` viene utilizzato per gestire un puntatore.
- `start_routine` (void *(*) (void *)): funzione eseguita dal thread.
- `arg` (void *): argomento passato alla funzione. Il tipo `void *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:76):
```c
int e = pthread_create(thread, attr, start_routine, arg);
```


#### int pthread_join(pthread_t thread, void **retval)
Attende la terminazione del thread specificato.

- `thread` (pthread_t): identificatore del thread. Il tipo `pthread_t` viene utilizzato per specificare un valore numerico.
- `retval` (void **): valore di ritorno del thread. Il tipo `void **` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:86):
```c
int e = pthread_join(thread, retval);
```


#### void pthread_exit(void *retval)
Termina il thread corrente restituendo un valore.

- `retval` (void *): valore di ritorno del thread. Il tipo `void *` viene utilizzato per gestire un puntatore.

**Restituisce**: void.

Esempio (08condVar/xerrori.c:80):
```c
pthread_exit(NULL);
```


#### int pthread_detach(pthread_t thread)
Segnala che il thread può liberare autonomamente le proprie risorse alla terminazione.

- `thread` (pthread_t): identificatore del thread. Il tipo `pthread_t` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (08condVar/heap.c:91):
```c
pthread_detach(th);
```


#### int sched_yield(void)
Cede volontariamente la CPU ad altri thread.



**Restituisce**: int.

Esempio (07threads/quicksort.c:85):
```c
sched_yield(); //rilascio la CPU
```


## Funzioni di lettura/scrittura su file

### POSIX

#### int open(const char *pathname, int flags, ...)
Apre un file e restituisce un file descriptor.

- `pathname` (const char *): percorso del file. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `flags` (int): flag di apertura. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `...`: argomenti variadic.

**Restituisce**: int.

Esempio (04fileBinari/scrivi_primi_sc.c:56):
```c
int fd = open(nome_file,O_WRONLY|O_CREAT,0666);
```


#### int close(int fd)
Chiude il file descriptor 'fd'.

- `fd` (int): file descriptor su cui operare. Il tipo `int` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:42):
```c
int e = close(fd);
```


#### ssize_t read(int fd, void *buf, size_t count)
Legge dati da un file descriptor.

- `fd` (int): file descriptor su cui operare. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `buf` (void *): buffer di memoria. Il tipo `void *` viene utilizzato per gestire un puntatore.
- `count` (size_t): numero di byte da elaborare. Il tipo `size_t` viene utilizzato per specificare un valore numerico.

**Restituisce**: ssize_t.

Esempio (09processi/contaprimi.c:67):
```c
ssize_t e = read(up[0],&x,sizeof(int));
```


#### ssize_t write(int fd, const void *buf, size_t count)
Scrive dati su un file descriptor.

- `fd` (int): file descriptor su cui operare. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `buf` (const void *): buffer di memoria. Il tipo `const void *` viene utilizzato per gestire un puntatore.
- `count` (size_t): numero di byte da elaborare. Il tipo `size_t` viene utilizzato per specificare un valore numerico.

**Restituisce**: ssize_t.

Esempio (04fileBinari/scrivi_primi_sc.c:62):
```c
// scrittura dell'intero i in formato binario con write(2)
```


#### int pipe(int pipefd[2])
Crea una pipe anonima e restituisce due file descriptor.

- `pipefd` (int [2]): array con i due descrittori della pipe. Il tipo `int [2]` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (10segnali/xerrori.c:337):
```c
int e = pipe(pipefd);
```


#### int mkfifo(const char *pathname, mode_t mode)
Crea una FIFO con il nome indicato.

- `pathname` (const char *): percorso del file. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `mode` (mode_t): modalità di apertura o permessi. Il tipo `mode_t` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (09processi/scrittore.c:17):
```c
int e = mkfifo(argv[1],0660);
```


#### int ftruncate(int fd, off_t length)
Tronca o estende il file aperto al nuovo 'length'.

- `fd` (int): file descriptor su cui operare. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `length` (off_t): parametro length. Il tipo `off_t` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (10segnali/xerrori.c:371):
```c
int e = ftruncate(fd,length);
```


### Standard C

#### FILE *fopen(const char *path, const char *mode)
Apre il file indicato e restituisce uno stream.

- `path` (const char *): percorso del file. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `mode` (const char *): modalità di apertura o permessi. Il tipo `const char *` viene utilizzato per gestire un puntatore.

**Restituisce**: FILE.

Esempio (08condVar/xerrori.c:31):
```c
FILE *f = fopen(path,mode);
```


#### int fclose(FILE *stream)
Chiude lo stream di file indicato.

- `stream` (FILE *): puntatore a FILE. Il tipo `FILE *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/somma_primi/somma_primi_files.c:110):
```c
fclose(f);
```


#### size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
Legge dati dallo stream in memoria.

- `ptr` (void *): puntatore a memoria. Il tipo `void *` viene utilizzato per gestire un puntatore.
- `size` (size_t): dimensione in byte. Il tipo `size_t` viene utilizzato per specificare un valore numerico.
- `nmemb` (size_t): numero di elementi. Il tipo `size_t` viene utilizzato per specificare un valore numerico.
- `stream` (FILE *): puntatore a FILE. Il tipo `FILE *` viene utilizzato per gestire un puntatore.

**Restituisce**: size_t.

Esempio (04fileBinari/leggi_bin.c:48):
```c
size_t m = fread(a,sizeof(int),n,f);
```


#### size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
Scrive dati in un file dallo stream.

- `ptr` (const void *): puntatore a memoria. Il tipo `const void *` viene utilizzato per gestire un puntatore.
- `size` (size_t): dimensione in byte. Il tipo `size_t` viene utilizzato per specificare un valore numerico.
- `nmemb` (size_t): numero di elementi. Il tipo `size_t` viene utilizzato per specificare un valore numerico.
- `stream` (FILE *): puntatore a FILE. Il tipo `FILE *` viene utilizzato per gestire un puntatore.

**Restituisce**: size_t.

Esempio (04fileBinari/scrivi_primi_bin.c:55):
```c
int e = fwrite(&i,sizeof(i),1,f);
```


#### int fprintf(FILE *stream, const char *format, ...)
Scrive dati formattati nello stream.

- `stream` (FILE *): puntatore a FILE. Il tipo `FILE *` viene utilizzato per gestire un puntatore.
- `format` (const char *): stringa di formato. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `...`: argomenti variadic.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:11):
```c
if(errno==0)  fprintf(stderr,"== %d == %s\n",getpid(), messaggio);
```


#### int fscanf(FILE *stream, const char *format, ...)
Legge dati formattati dallo stream.

- `stream` (FILE *): puntatore a FILE. Il tipo `FILE *` viene utilizzato per gestire un puntatore.
- `format` (const char *): stringa di formato. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `...`: argomenti variadic.

**Restituisce**: int.

Esempio (08condVar/somma_primi/somma_primi_files.c:96):
```c
e = fscanf(f,"%d",&n);
```


#### int printf(const char *format, ...)
Stampa dati formattati su stdout.

- `format` (const char *): stringa di formato. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `...`: argomenti variadic.

**Restituisce**: int.

Esempio (08condVar/pctest.c:141):
```c
printf("Uso\n\t%s interi #prod #cons\n", argv[0]);
```


#### int scanf(const char *format, ...)
Legge input formattato da stdin.

- `format` (const char *): stringa di formato. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `...`: argomenti variadic.

**Restituisce**: int.

Esempio (01introC/somma.c:28):
```c
scanf("%d",&n); // il motivo della & lo vedremo più avanti
```


#### int fflush(FILE *stream)
Svuota il buffer dello stream.

- `stream` (FILE *): puntatore a FILE. Il tipo `FILE *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (10segnali/alice.c:22):
```c
fflush(stdout);
```


#### int fseek(FILE *stream, long offset, int whence)
Imposta la posizione corrente nello stream.

- `stream` (FILE *): puntatore a FILE. Il tipo `FILE *` viene utilizzato per gestire un puntatore.
- `offset` (long): spiazzamento. Il tipo `long` viene utilizzato per specificare un valore numerico.
- `whence` (int): punto di riferimento. Il tipo `int` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (04fileBinari/leggi_bin.c:34):
```c
int e = fseek(f, 0, SEEK_END);
```


#### long ftell(FILE *stream)
Restituisce la posizione corrente nello stream.

- `stream` (FILE *): puntatore a FILE. Il tipo `FILE *` viene utilizzato per gestire un puntatore.

**Restituisce**: long.

Esempio (04fileBinari/leggi_bin.c:37):
```c
long lungfile = ftell(f);
```


#### void rewind(FILE *stream)
Riporta la posizione dello stream all'inizio del file.

- `stream` (FILE *): puntatore a FILE. Il tipo `FILE *` viene utilizzato per gestire un puntatore.

**Restituisce**: void.

Esempio (04fileBinari/leggi_bin.c:46):
```c
rewind(f); // "riavvolgo" il file
```


#### ssize_t getline(char **lineptr, size_t *n, FILE *stream)
Legge una riga dallo stream allocando buffer se necessario.

- `lineptr` (char **): puntatore al buffer della linea. Il tipo `char **` viene utilizzato per gestire un puntatore.
- `n` (size_t *): dimensione del buffer. Il tipo `size_t *` viene utilizzato per gestire un puntatore.
- `stream` (FILE *): puntatore a FILE. Il tipo `FILE *` viene utilizzato per gestire un puntatore.

**Restituisce**: ssize_t.

Esempio (02struct/frequenze.c:25):
```c
char *buffer=NULL;    // usata da getline()
```


#### int puts(const char *s)
Stampa una stringa seguita da newline su stdout.

- `s` (const char *): parametro s. Il tipo `const char *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (04fileBinari/matrice.c:38:puts("Matrice allocata staticamente):
```c
");
```


#### int asprintf(char **strp, const char *fmt, ...)
Scrive l'output formattato in una stringa allocata dinamicamente.

- `strp` (char **): puntatore alla stringa allocata. Il tipo `char **` viene utilizzato per gestire un puntatore.
- `fmt` (const char *): stringa di formato. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `...`: argomenti variadic.

**Restituisce**: int.

Esempio (01introC/creafiles.c:31):
```c
int e = asprintf(&nome,"%s.%d.txt",z,i);
```


## Gestione memoria e IPC

### Allocazione memoria

#### void *malloc(size_t size)
Alloca 'size' byte di memoria.

- `size` (size_t): dimensione in byte. Il tipo `size_t` viene utilizzato per specificare un valore numerico.

**Restituisce**: void.

Esempio (04fileBinari/matrice.c:92):
```c
b = malloc(r*sizeof(*b));
```


#### void free(void *ptr)
Libera la memoria allocata con malloc/realloc.

- `ptr` (void *): puntatore a memoria. Il tipo `void *` viene utilizzato per gestire un puntatore.

**Restituisce**: void.

Esempio (04fileBinari/matrice.c:54):
```c
free(b[i]);
```


#### void *realloc(void *ptr, size_t size)
Ridimensiona un blocco di memoria allocato.

- `ptr` (void *): puntatore a memoria. Il tipo `void *` viene utilizzato per gestire un puntatore.
- `size` (size_t): dimensione in byte. Il tipo `size_t` viene utilizzato per specificare un valore numerico.

**Restituisce**: void.

Esempio (03assembler/array_primi.c:87):
```c
a = realloc(a,messi*sizeof(int));
```


#### void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
Mappa un file o dispositivo in memoria.

- `addr` (void *): parametro addr. Il tipo `void *` viene utilizzato per gestire un puntatore.
- `length` (size_t): parametro length. Il tipo `size_t` viene utilizzato per specificare un valore numerico.
- `prot` (int): protezione della mappatura. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `flags` (int): flag di apertura. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `fd` (int): file descriptor su cui operare. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `offset` (off_t): spiazzamento. Il tipo `off_t` viene utilizzato per specificare un valore numerico.

**Restituisce**: void.

Esempio (10segnali/xerrori.c:382):
```c
void *a =  mmap(NULL, length ,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
```


#### int munmap(void *addr, size_t length)
Annulla una precedente mappatura di memoria.

- `addr` (void *): parametro addr. Il tipo `void *` viene utilizzato per gestire un puntatore.
- `length` (size_t): parametro length. Il tipo `size_t` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (10segnali/xerrori.c:393):
```c
int e = munmap(addr, length);
```


### Memoria condivisa

#### int shm_open(const char *name, int oflag, mode_t mode)
Apre o crea un oggetto di memoria condivisa POSIX.

- `name` (const char *): nome dell'oggetto. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `oflag` (int): parametro oflag. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `mode` (mode_t): modalità di apertura o permessi. Il tipo `mode_t` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (10segnali/xerrori.c:349):
```c
int e = shm_open(name, oflag, mode);
```


#### int shm_unlink(const char *name)
Rimuove un oggetto di memoria condivisa.

- `name` (const char *): nome dell'oggetto. Il tipo `const char *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (10segnali/xerrori.c:360):
```c
int e = shm_unlink(name);
```


## Controllo dei processi

#### pid_t fork(void)
Crea un nuovo processo duplicando quello corrente.



**Restituisce**: pid_t.

Esempio (10segnali/xerrori.c:315):
```c
pid_t p = fork();
```


#### int execl(const char *path, const char *arg, ...)
Sostituisce il processo corrente eseguendo il programma indicato in 'path'.

- `path` (const char *): percorso del file. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `arg` (const char *): argomento passato alla funzione. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `...`: argomenti variadic.

**Restituisce**: int.

Esempio (10segnali/alice.c:30):
```c
if(execl("./bob.out", "bob.out", (char *) NULL)==-1){
```


#### pid_t wait(int *wstatus)
Attende la terminazione di un processo figlio.

- `wstatus` (int *): stato di uscita. Il tipo `int *` viene utilizzato per gestire un puntatore.

**Restituisce**: pid_t.

Esempio (10segnali/xerrori.c:326):
```c
pid_t p = wait(status);
```


#### void exit(int status)
Termina il processo restituendo 'status'.

- `status` (int): parametro status. Il tipo `int` viene utilizzato per specificare un valore numerico.

**Restituisce**: void.

Esempio (08condVar/xerrori.c:14):
```c
exit(1);
```


#### pid_t getpid(void)
Restituisce l'identificatore del processo corrente.



**Restituisce**: pid_t.

Esempio (08condVar/xerrori.c:11):
```c
if(errno==0)  fprintf(stderr,"== %d == %s\n",getpid(), messaggio);
```


#### pid_t getppid(void)
Restituisce l'identificatore del processo padre.



**Restituisce**: pid_t.

Esempio (10segnali/bob.c:18):
```c
sigqueue(getppid(), SIGRTMIN, ready);
```


#### pid_t gettid(void)
Restituisce l'identificatore del thread corrente (Linux).



**Restituisce**: pid_t.

Esempio (08condVar/xerrori.c:180):
```c
// Si potrebbe distinguere thread da processi con gettid(2)
```


## Stringhe e caratteri

#### int atoi(const char *nptr)
Converte la stringa 'nptr' in un intero.

- `nptr` (const char *): parametro nptr. Il tipo `const char *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (08condVar/pctest.c:145):
```c
int num = atoi(argv[1]);
```


#### int strcmp(const char *s1, const char *s2)
Confronta due stringhe.

- `s1` (const char *): parametro s1. Il tipo `const char *` viene utilizzato per gestire un puntatore.
- `s2` (const char *): parametro s2. Il tipo `const char *` viene utilizzato per gestire un puntatore.

**Restituisce**: int.

Esempio (03assembler/strcmp.c:26):
```c
ris = strcmp(argv[i],argv[i+1]);
```


#### size_t strlen(const char *s)
Calcola la lunghezza della stringa.

- `s` (const char *): parametro s. Il tipo `const char *` viene utilizzato per gestire un puntatore.

**Restituisce**: size_t.

Esempio (02struct/frequenze.c:36):
```c
if(strlen(s)>0) {
```


#### char *strdup(const char *s)
Duplica la stringa indicata allocando memoria.

- `s` (const char *): parametro s. Il tipo `const char *` viene utilizzato per gestire un puntatore.

**Restituisce**: char.

Esempio (02struct/array_capitali_funz.c:34):
```c
a->nome = strdup(s);
```


#### char *strtok(char *restrict s, const char *restrict delim)
Estrae token da una stringa in base ai delimitatori.

- `s` (char *restrict): parametro s. Il tipo `char *restrict` viene utilizzato per gestire un puntatore.
- `delim` (const char *restrict): parametro delim. Il tipo `const char *restrict` viene utilizzato per gestire un puntatore.

**Restituisce**: char.

Esempio (02struct/frequenze.c:34):
```c
char *s = strtok(buffer,Delimitatori);
```


#### char *strerror(int errnum)
Restituisce una stringa descrittiva dell'errore.

- `errnum` (int): parametro errnum. Il tipo `int` viene utilizzato per specificare un valore numerico.

**Restituisce**: char.

Esempio (08condVar/xerrori.c:13):
```c
strerror(errno));
```


#### int strerror_r(int errnum, char *buf, size_t buflen)
Scrive in 'buf' una descrizione dell'errore 'errnum'.

- `errnum` (int): parametro errnum. Il tipo `int` viene utilizzato per specificare un valore numerico.
- `buf` (char *): buffer di memoria. Il tipo `char *` viene utilizzato per gestire un puntatore.
- `buflen` (size_t): parametro buflen. Il tipo `size_t` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (08condVar/xerrori.c:64):
```c
char *errmsg = strerror_r(en, buf, Buflen);
```


## Matematica e numeri casuali

#### int abs(int x)
Restituisce il valore assoluto di 'x'.

- `x` (int): parametro x. Il tipo `int` viene utilizzato per specificare un valore numerico.

**Restituisce**: int.

Esempio (04fileBinari/matrice.c:6):
```c
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit()
```


#### double sqrt(double x)
Calcola la radice quadrata di 'x'.

- `x` (double): parametro x. Il tipo `double` viene utilizzato per specificare un valore numerico.

**Restituisce**: double.

Esempio (01introC/scrivi_primi.c:32):
```c
// allora esiste un divisore <= sqrt(k) che è dispari
```


#### int rand(void)
Restituisce un numero pseudo-casuale.



**Restituisce**: int.

Esempio (04fileBinari/matrice.c:6):
```c
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit()
```


#### long int random(void)
Restituisce un numero pseudo-casuale (interfaccia BSD).



**Restituisce**: long.

Esempio (07threads/pmergesort.c:199):
```c
a[i] = (int) random() % 1000000;
```


#### void srand(unsigned int seed)
Imposta il seed per la sequenza generata da rand.

- `seed` (unsigned int): parametro seed. Il tipo `unsigned int` viene utilizzato per specificare un valore numerico.

**Restituisce**: void.

Esempio (10segnali/alice.c:59):
```c
srand(time(NULL)); // inizializza il generatore (una sola volta!)
```


#### void srandom(unsigned int seed)
Imposta il seed per random.

- `seed` (unsigned int): parametro seed. Il tipo `unsigned int` viene utilizzato per specificare un valore numerico.

**Restituisce**: void.

Esempio (07threads/pmergesort.c:195):
```c
srandom(seed);
```


## Utilità varie

#### void perror(const char *s)
Stampa il messaggio di errore relativo all'ultima chiamata fallita.

- `s` (const char *): parametro s. Il tipo `const char *` viene utilizzato per gestire un puntatore.

**Restituisce**: void.

Esempio (08condVar/xerrori.c:33):
```c
perror("Errore apertura file");
```


#### void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
Ordina un array usando l'algoritmo quicksort.

- `base` (void *): array da ordinare. Il tipo `void *` viene utilizzato per gestire un puntatore.
- `nmemb` (size_t): numero di elementi. Il tipo `size_t` viene utilizzato per specificare un valore numerico.
- `size` (size_t): dimensione in byte. Il tipo `size_t` viene utilizzato per specificare un valore numerico.
- `compar` (int (*)(const void *, const void *)): funzione di confronto.

**Restituisce**: void.

Esempio (02struct/frequenze.c:95):
```c
qsort(a,n,sizeof(*a), (__compar_fn_t) &confronta_freq);
```


#### time_t time(time_t *tloc)
Restituisce l'ora corrente.

- `tloc` (time_t *): parametro tloc. Il tipo `time_t *` viene utilizzato per gestire un puntatore.

**Restituisce**: time_t.

Esempio (04fileBinari/write_speed.c:39):
```c
time_t start = time(NULL); // numero di secondi da 1/1/1970
```
## Confronto funzioni simili

### pause vs sleep
| Funzione | Blocco dell'esecuzione | Ripresa |
| --- | --- | --- |
| `pause()` | attende indefinitamente un segnale | ritorna quando un segnale viene gestito |
| `sleep(seconds)` | attende un numero prefissato di secondi | ritorna allo scadere del tempo o se interrotta da segnale |

### fread vs read
| Funzione | Interfaccia | Buffer / stream | Uso tipico |
| --- | --- | --- | --- |
| `fread(ptr,size,nmemb,stream)` | libreria C (stdio) | opera su `FILE*` e gestisce buffering | I/O ad alto livello su file o pipe |
| `read(fd,buf,count)` | POSIX | opera su descrittore di file | I/O a basso livello, usato anche per socket e device |

### fopen vs open
| Funzione | Interfaccia | Cosa restituisce | Uso |
| --- | --- | --- | --- |
| `fopen(path,mode)` | libreria C | puntatore `FILE*` con buffering | apertura file con funzioni stdio |
| `open(path,flags,...)` | POSIX | descrittore di file intero | apertura a basso livello, configurabile |
## Appendice
### Funzioni sui segnali
| Funzione | Descrizione |
| --- | --- |
| `int kill(pid_t pid, int sig)` | Invia il segnale 'sig' al processo indicato. |
| `int pause(void)` | Sospende il processo fino alla ricezione di un segnale. |
| `unsigned int sleep(unsigned int seconds)` | Sospende l'esecuzione per un numero di secondi. |
| `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)` | Imposta un gestore per il segnale specificato. |
| `int sigaddset(sigset_t *set, int signum)` | Aggiunge un segnale all'insieme. |
| `int sigdelset(sigset_t *set, int signum)` | Rimuove un segnale dall'insieme. |
| `int sigemptyset(sigset_t *set)` | Inizializza l'insieme di segnali a vuoto. |
| `int sigfillset(sigset_t *set)` | Imposta tutti i segnali nell'insieme. |
| `int sigqueue(pid_t pid, int sig, const union sigval value)` | Invia un segnale con valore associato ad un processo. |
| `int sigwait(const sigset_t *set, int *sig)` | Attende in modo sincrono uno dei segnali indicati. |
| `int sigwaitinfo(const sigset_t *set, siginfo_t *info)` | Come sigwait ma restituisce informazioni aggiuntive. |
| `int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset)` | Modifica o legge la maschera dei segnali del thread corrente. |

#### Funzioni di sincronizzazione - Semafori
| Funzione | Descrizione |
| --- | --- |
| `int sem_close(sem_t *sem)` | Chiude il descrittore di un semaforo aperto con sem_open. |
| `int sem_destroy(sem_t *sem)` | Distrugge un semaforo inizializzato staticamente. |
| `int sem_init(sem_t *sem, int pshared, unsigned int value)` | Inizializza un semaforo anonimo. |
| `sem_t *sem_open(const char *name, int oflag, ...)` | Apre o crea un semaforo nominato. |
| `int sem_post(sem_t *sem)` | Incrementa il valore del semaforo (sblocco). |
| `int sem_unlink(const char *name)` | Rimuove un semaforo nominato dal filesystem. |
| `int sem_wait(sem_t *sem)` | Decrementa il semaforo bloccando se il valore è zero. |

#### Funzioni di sincronizzazione - Lock (mutex)
| Funzione | Descrizione |
| --- | --- |
| `int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr)` | Inizializza un mutex. |
| `int pthread_mutex_lock(pthread_mutex_t *mutex)` | Acquisisce un mutex bloccandosi se necessario. |
| `int pthread_mutex_unlock(pthread_mutex_t *mutex)` | Rilascia un mutex precedentemente acquisito. |
| `int pthread_mutex_destroy(pthread_mutex_t *mutex)` | Distrugge un mutex. |

#### Funzioni di sincronizzazione - Variabili di condizione
| Funzione | Descrizione |
| --- | --- |
| `int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr)` | Inizializza una variabile di condizione. |
| `int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex)` | Attende su una variabile di condizione sbloccando il mutex associato. |
| `int pthread_cond_signal(pthread_cond_t *cond)` | Risveglia un thread in attesa sulla variabile di condizione. |
| `int pthread_cond_broadcast(pthread_cond_t *cond)` | Risveglia tutti i thread in attesa sulla variabile di condizione. |
| `int pthread_cond_destroy(pthread_cond_t *cond)` | Distrugge la variabile di condizione. |

#### Funzioni di sincronizzazione - Barriere
| Funzione | Descrizione |
| --- | --- |
| `int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned int count)` | Inizializza una barriera di sincronizzazione. |
| `int pthread_barrier_wait(pthread_barrier_t *barrier)` | Attende che tutti i thread raggiungano la barriera. |
| `int pthread_barrier_destroy(pthread_barrier_t *barrier)` | Distrugge una barriera di sincronizzazione. |

#### Funzioni di sincronizzazione - Thread
| Funzione | Descrizione |
| --- | --- |
| `int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)` | Crea un nuovo thread eseguendo 'start_routine'. |
| `int pthread_join(pthread_t thread, void **retval)` | Attende la terminazione del thread specificato. |
| `void pthread_exit(void *retval)` | Termina il thread corrente restituendo un valore. |
| `int pthread_detach(pthread_t thread)` | Segnala che il thread può liberare autonomamente le proprie risorse alla terminazione. |
| `int sched_yield(void)` | Cede volontariamente la CPU ad altri thread. |

#### Funzioni di lettura/scrittura su file - POSIX
| Funzione | Descrizione |
| --- | --- |
| `int open(const char *pathname, int flags, ...)` | Apre un file e restituisce un file descriptor. |
| `int close(int fd)` | Chiude il file descriptor 'fd'. |
| `ssize_t read(int fd, void *buf, size_t count)` | Legge dati da un file descriptor. |
| `ssize_t write(int fd, const void *buf, size_t count)` | Scrive dati su un file descriptor. |
| `int pipe(int pipefd[2])` | Crea una pipe anonima e restituisce due file descriptor. |
| `int mkfifo(const char *pathname, mode_t mode)` | Crea una FIFO con il nome indicato. |
| `int ftruncate(int fd, off_t length)` | Tronca o estende il file aperto al nuovo 'length'. |

#### Funzioni di lettura/scrittura su file - Standard C
| Funzione | Descrizione |
| --- | --- |
| `FILE *fopen(const char *path, const char *mode)` | Apre il file indicato e restituisce uno stream. |
| `int fclose(FILE *stream)` | Chiude lo stream di file indicato. |
| `size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)` | Legge dati dallo stream in memoria. |
| `size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)` | Scrive dati in un file dallo stream. |
| `int fprintf(FILE *stream, const char *format, ...)` | Scrive dati formattati nello stream. |
| `int fscanf(FILE *stream, const char *format, ...)` | Legge dati formattati dallo stream. |
| `int printf(const char *format, ...)` | Stampa dati formattati su stdout. |
| `int scanf(const char *format, ...)` | Legge input formattato da stdin. |
| `int fflush(FILE *stream)` | Svuota il buffer dello stream. |
| `int fseek(FILE *stream, long offset, int whence)` | Imposta la posizione corrente nello stream. |
| `long ftell(FILE *stream)` | Restituisce la posizione corrente nello stream. |
| `void rewind(FILE *stream)` | Riporta la posizione dello stream all'inizio del file. |
| `ssize_t getline(char **lineptr, size_t *n, FILE *stream)` | Legge una riga dallo stream allocando buffer se necessario. |
| `int puts(const char *s)` | Stampa una stringa seguita da newline su stdout. |
| `int asprintf(char **strp, const char *fmt, ...)` | Scrive l'output formattato in una stringa allocata dinamicamente. |

#### Gestione memoria e IPC - Allocazione memoria
| Funzione | Descrizione |
| --- | --- |
| `void *malloc(size_t size)` | Alloca 'size' byte di memoria. |
| `void free(void *ptr)` | Libera la memoria allocata con malloc/realloc. |
| `void *realloc(void *ptr, size_t size)` | Ridimensiona un blocco di memoria allocato. |
| `void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)` | Mappa un file o dispositivo in memoria. |
| `int munmap(void *addr, size_t length)` | Annulla una precedente mappatura di memoria. |

#### Gestione memoria e IPC - Memoria condivisa
| Funzione | Descrizione |
| --- | --- |
| `int shm_open(const char *name, int oflag, mode_t mode)` | Apre o crea un oggetto di memoria condivisa POSIX. |
| `int shm_unlink(const char *name)` | Rimuove un oggetto di memoria condivisa. |

### Controllo dei processi
| Funzione | Descrizione |
| --- | --- |
| `pid_t fork(void)` | Crea un nuovo processo duplicando quello corrente. |
| `int execl(const char *path, const char *arg, ...)` | Sostituisce il processo corrente eseguendo il programma indicato in 'path'. |
| `pid_t wait(int *wstatus)` | Attende la terminazione di un processo figlio. |
| `void exit(int status)` | Termina il processo restituendo 'status'. |
| `pid_t getpid(void)` | Restituisce l'identificatore del processo corrente. |
| `pid_t getppid(void)` | Restituisce l'identificatore del processo padre. |
| `pid_t gettid(void)` | Restituisce l'identificatore del thread corrente (Linux). |

### Stringhe e caratteri
| Funzione | Descrizione |
| --- | --- |
| `int atoi(const char *nptr)` | Converte la stringa 'nptr' in un intero. |
| `int strcmp(const char *s1, const char *s2)` | Confronta due stringhe. |
| `size_t strlen(const char *s)` | Calcola la lunghezza della stringa. |
| `char *strdup(const char *s)` | Duplica la stringa indicata allocando memoria. |
| `char *strtok(char *restrict s, const char *restrict delim)` | Estrae token da una stringa in base ai delimitatori. |
| `char *strerror(int errnum)` | Restituisce una stringa descrittiva dell'errore. |
| `int strerror_r(int errnum, char *buf, size_t buflen)` | Scrive in 'buf' una descrizione dell'errore 'errnum'. |

### Matematica e numeri casuali
| Funzione | Descrizione |
| --- | --- |
| `int abs(int x)` | Restituisce il valore assoluto di 'x'. |
| `double sqrt(double x)` | Calcola la radice quadrata di 'x'. |
| `int rand(void)` | Restituisce un numero pseudo-casuale. |
| `long int random(void)` | Restituisce un numero pseudo-casuale (interfaccia BSD). |
| `void srand(unsigned int seed)` | Imposta il seed per la sequenza generata da rand. |
| `void srandom(unsigned int seed)` | Imposta il seed per random. |

### Utilità varie
| Funzione | Descrizione |
| --- | --- |
| `void perror(const char *s)` | Stampa il messaggio di errore relativo all'ultima chiamata fallita. |
| `void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))` | Ordina un array usando l'algoritmo quicksort. |
| `time_t time(time_t *tloc)` | Restituisce l'ora corrente. |

