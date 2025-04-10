#include "xerrori.h"
// abbreviamo la chiamata alle funzioni x...
#define QUI __LINE__,__FILE__

volatile sig_atomic_t finito = 0;

// gestione di heap mediante condition variable
// per fare si che le stampe riflettano l'effettivo ordine
// delle operazioni queste sono effettuate quando il 
// mutex è sempre bloccato 

// struct che tiene traccia della memoria disponibile e 
// contiene le variabili cond/mutex per regolarne l'utilizzo
typedef struct {
  pthread_cond_t  *cv; // condition variable
  pthread_mutex_t *mu; // mutex
  int MB;       // memoria attualmente disponibile
} heap;

// simula allocazione con spazio limitato
void richiedi(heap *h, int n) {
  xpthread_mutex_lock(h->mu,QUI);
  fprintf(stderr,"%2d Richiesti: %3d\n", gettid()%100, n);
  while(n>h->MB) {
    fprintf(stderr,"%2d Negati: %3d\n", gettid()%100, n);
    xpthread_cond_wait(h->cv,h->mu,QUI);
  }
  h->MB -= n;
  fprintf(stderr,"%2d Assegnati: %3d. Rimanenti: %4d\n\n", gettid()%100,
          n,h->MB);
  xpthread_mutex_unlock(h->mu,QUI);
}

// deallocazione
void libera(heap *h, int n) {
  xpthread_mutex_lock(h->mu,QUI);
  h->MB += n;
  xpthread_cond_broadcast(h->cv,QUI);
  fprintf(stderr,"%2d Restituiti: %3d. Rimanenti: %4d\n\n", gettid()%100,
          n,h->MB);
  xpthread_mutex_unlock(h->mu,QUI); 
}


// codice thread tipo 1, chiede 10,20,...,50
void *tipo1(void *v) {
  heap *h = (heap *) v;
  for(int i=1;i<=5;i++) {
    int m = 10*i;
    richiedi(h,m);
    sleep(1);
    libera(h,m);
  }
  return NULL;
}

// codice thread tipo 2, chiede 15,25,...,55
void *tipo2(void *v) {
  heap *h = (heap *) v;
  for(int i=1;i<=5;i++) {
    int m = 10*i+5;
    richiedi(h,m);
    sleep(1);
    libera(h,m);
  }
  return NULL;
}

void *alloca_da_segnale(void *arg) {
  heap *h = (heap *)arg;
  richiedi(h, 7);
  sleep(5);
  libera(h, 7);
  return NULL;
}

void *signal_handler(void *a){
  heap *h = (heap *)a;
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  pthread_sigmask(SIG_BLOCK, &set, NULL);

  while (1) {
    int s;
    int e = sigwait(&set, &s);
    if (e < 0) xtermina("Errore sigwait\n", QUI);

    pthread_t th;
    xpthread_create(&th, NULL, alloca_da_segnale, h, QUI);
    pthread_detach(th);
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  // controlla numero argomenti
  if(argc!=3) {
      printf("Uso: %s mem numT\n",argv[0]);
      return 1;
  }
  int mem = atoi(argv[1]);
  int nt = atoi(argv[2]);
  assert(nt>1);

  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  pthread_sigmask(SIG_BLOCK, &set, NULL);  // blocca SIGINT per tutti i thread


  // inizializza heap 
  pthread_cond_t c = PTHREAD_COND_INITIALIZER;
  pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
  heap h;
  h.cv = &c; h.mu = &m;
  h.MB = mem;

  // Avvio thread gestore dei segnali Ctrl+C
  pthread_t handler;
  xpthread_create(&handler, NULL, &signal_handler, &h, QUI);
  
  // esegue i thread
  pthread_t t[nt];
  // esegue un thread tipo1
  xpthread_create(&t[0],NULL,&tipo1,&h,QUI);
  for(int i=1;i<nt;i++)
    // esegue nt-1 thread di tipo 2
    xpthread_create(&t[i],NULL,&tipo2,&h,QUI);

  // attende terminazione thread e termina
  for(int i=0;i<nt;i++)
    xpthread_join(t[i],NULL,QUI);

  xpthread_join(handler,NULL, QUI);
  xpthread_cond_destroy(&c,QUI);
  xpthread_mutex_destroy(&m,QUI);
  
  fprintf(stderr,"Terminato con memoria: %d\n",h.MB);
  return 0;
}
