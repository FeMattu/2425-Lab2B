#include "xerrori.h"

// collezione di chiamate a funzioni di sistema con controllo output
// i prototipi sono in xerrori.h


// termina un processo con eventuale messaggio d'errore
// si noti che la variabile errno è "thread local"
// quindi ne esiste una diversa per ogni thread  
void termina(const char *messaggio) {
  if(errno==0)  fprintf(stderr,"== %d == %s\n",getpid(), messaggio);
  else fprintf(stderr,"== %d == %s: %s\n",getpid(), messaggio,
              strerror(errno));
  exit(1);
}

// termina un processo con eventuale messaggio d'errore + linea e file
// si noti che la variabile errno è "thread local"
// quindi ne esiste una diversa per ogni thread  
void xtermina(const char *messaggio, int linea, char *file) {
  if(errno==0)  fprintf(stderr,"== %d == %s\n",getpid(), messaggio);
  else fprintf(stderr,"== %d == %s: %s\n",getpid(), messaggio,
               strerror(errno));
  fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);

  exit(1);
}

// ---------- operazioni su FILE *
FILE *xfopen(const char *path, const char *mode, int linea, char *file) {
  FILE *f = fopen(path,mode);
  if(f==NULL) {
    perror("Errore apertura file");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return f;
}

// ----------- operazioni su file descriptors
void xclose(int fd, int linea, char *file) {
  int e = close(fd);
  if(e!=0) {
    perror("Errore chiusura file descriptor");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return;
}


// ----- funzioni per thread: in caso di errore non scrivono 
// il codice d'errore in errno ma lo restituiscono
// come return value. Un return value==0 indica nessun errore
// errno viene evitato perché in certe implementazioni 
// non è thread-safe (nei linux recenti lo è)

// stampa il messaggio d'errore associato al codice en 
// in maniera simile a perror
#define Buflen 100
void xperror(int en, char *msg) {
  char buf[Buflen];
  
  char *errmsg = strerror_r(en, buf, Buflen);
  if(msg!=NULL)
    fprintf(stderr,"%s: %s\n",msg, errmsg);
  else
    fprintf(stderr,"%s\n",errmsg);
}


// threads: creazione e join

int xpthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg, int linea, char *file) {
  int e = pthread_create(thread, attr, start_routine, arg);
  if (e!=0) {
    xperror(e, "Errore pthread_create");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }
  return e;                       
}
                          
int xpthread_join(pthread_t thread, void **retval, int linea, char *file) {
  int e = pthread_join(thread, retval);
  if (e!=0) {
    xperror(e, "Errore pthread_join");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }
  return e;
}




// ----- mutex 
int xpthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr, int linea, char *file) {
  int e = pthread_mutex_init(mutex, attr);
  if (e!=0) {
    xperror(e, "Errore pthread_mutex_init");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }  
  return e;
}

int xpthread_mutex_destroy(pthread_mutex_t *mutex, int linea, char *file) {
  int e = pthread_mutex_destroy(mutex);
  if (e!=0) {
    xperror(e, "Errore pthread_mutex_destroy");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }
  return e;
}

int xpthread_mutex_lock(pthread_mutex_t *mutex, int linea, char *file) {
  int e = pthread_mutex_lock(mutex);
  if (e!=0) {
    xperror(e, "Errore pthread_mutex_lock");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }
  return e;
}

int xpthread_mutex_unlock(pthread_mutex_t *mutex, int linea, char *file) {
  int e = pthread_mutex_unlock(mutex);
  if (e!=0) {
    xperror(e, "Errore pthread_mutex_unlock");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }
  return e;
}

// ---- barriere
int xpthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, 
                          unsigned int count, int linea, char *file) {
  int e = pthread_barrier_init(barrier, attr, count);
  if (e!=0) {
    xperror(e, "Errore pthread_barrier_init");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }  
  return e;
}

int xpthread_barrier_destroy(pthread_barrier_t *barrier, int linea, char *file) {
  int e = pthread_barrier_destroy(barrier);
  if (e!=0) {
    xperror(e, "Errore pthread_barrier_destroy");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }
  return e;
}

int xpthread_barrier_wait(pthread_barrier_t *barrier, int linea, char *file) {
  int e = pthread_barrier_wait(barrier);
  if (e!=0 && e!=PTHREAD_BARRIER_SERIAL_THREAD) {
    xperror(e, "Errore pthread_barrier_wait");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }
  return e;
}


// ---- semafori POSIX

// IMPORTANTE: i semafori posix sono usati sia da processi che da threads
// Nel caso dei threads, non è opportuno eseguire in caso di errore exit(1)
// in quanto questo fa terminare tutti i thread del processo: bisognerebbe
// chiamare pthread_exit() che fa terminare solo il thread corrente
// (usare pthread_exit per i processi ugualmente non è accettabile 
// perché poi invoca exit(0)). 
// Si potrebbe distinguere thread da processi con gettid(2)


// semafori NAMED
sem_t *xsem_open(const char *name, int oflag, mode_t mode, 
              unsigned int value,  int linea, char *file) {
  sem_t *s = sem_open(name,oflag,mode,value);
  if (s==SEM_FAILED) {
    perror("Errore sem_open");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file); 
    exit(1);
  }
  return s;
}

int xsem_close(sem_t *s, int linea, char *file)
{
  int e = sem_close(s);
  if(e!=0) {
    perror("Errore sem_close"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;  
}

int xsem_unlink(const char *name, int linea, char *file)
{
  int e = sem_unlink(name);
  if(e!=0) {
    perror("Errore sem_unlink"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;  
}

// semafori UNNAMED
int xsem_init(sem_t *sem, int pshared, unsigned int value, int linea, char *file) {
  int e = sem_init(sem,pshared,value);
  if(e !=0) {
    perror("Errore sem_init"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;
}

int xsem_destroy(sem_t *sem, int linea, char *file) {
  int e = sem_destroy(sem);
  if(e !=0) {
    perror("Errore sem_destroy"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;
}

// comuni NAMED e UNNAMED
int xsem_post(sem_t *sem, int linea, char *file) {
  int e = sem_post(sem);
  if(e !=0) {
    perror("Errore sem_post"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;
}

int xsem_wait(sem_t *sem, int linea, char *file) {
  int e = sem_wait(sem);
  if(e !=0) {
    perror("Errore sem_wait"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;
}


// condition variables
int xpthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr, int linea, char *file) {
  int e = pthread_cond_init(cond,attr);
  if (e!=0) {
    xperror(e, "Errore pthread_cond_init");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }
  return e;
}

int xpthread_cond_destroy(pthread_cond_t *cond, int linea, char *file) {
  int e = pthread_cond_destroy(cond);
  if (e!=0) {
    xperror(e, "Errore pthread_cond_destroy");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }
  return e;
}

int xpthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, int linea, char *file) {
  int e = pthread_cond_wait(cond,mutex);
  if (e!=0) {
    xperror(e, "Errore pthread_cond_wait");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }
  return e;
}

int xpthread_cond_signal(pthread_cond_t *cond, int linea, char *file) {
  int e = pthread_cond_signal(cond);
  if (e!=0) {
    xperror(e, "Errore pthread_cond_signal");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }
  return e;
}

int xpthread_cond_broadcast(pthread_cond_t *cond, int linea, char *file) {
  int e = pthread_cond_broadcast(cond);
  if (e!=0) {
    xperror(e, "Errore pthread_cond_broadcast");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    pthread_exit(NULL);
  }
  return e;
}
