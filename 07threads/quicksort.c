// template per quicksort con partizionamento parallelo
//
#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include "xerrori.h"

#define QUI __LINE__,__FILE__
#define SOGLIA_PARALLELO 100

// prototipi delle funzioni che appaiono dopo il main()
int *random_array(int n, int seed);
void quicksort(int b[], int n);


// ordina gli interi passati sulla linea di comando
int main(int argc, char *argv[])
{
  if(argc!=3) {
    fprintf(stderr, "Uso:\n\t   %s num_interi seed\n", argv[0]);
    exit(1);
  }
  int n = atoi(argv[1]);
  assert(n>0);
  // genera array random di n elementi
  int *a = random_array(n,atoi(argv[2]));
  // calcola somma prima dell'ordinamento
  long somma=0;
  for(int i=0;i<n;i++) somma += a[i];
  
  // esegue l'ordinamento
  quicksort(a,n);
  
  // controlla ordinamento
  long somma2 = a[0];
  for(int i=1;i<n;i++) {
    somma2 += a[i];
    if(a[i-1]>a[i]) {
      printf("Array non ordinato alla posizione %d (%d>%d)\n",i,a[i-1],a[i]);
      exit(1);
    }
  }
  if(somma!=somma2) {
    printf("Somma degli elementi non corrisponde: %ld vs %ld\n",somma,somma2);
    exit(1);
  }
  else 
    puts("Array ordinato e somma mantenuta, sorting probabilmente OK");

  // dealloco l'array e termino
  free(a);   
  return 0;
}

typedef struct{
  int *a;
  int *i;
  int *j;
  int pivot;
  bool *done;
  pthread_mutex_t *mu;
  pthread_cond_t *found_element_less_then_pivot;
}partition_data;

void *tbody(void *arg){
  partition_data *d = (partition_data *)arg;

  while(true){
    xpthread_mutex_lock(d->mu, QUI);
    if((*d->done)) {  //se il thread principale ha finito si esce
      xpthread_mutex_unlock(d->mu, QUI);
      break;
    }   
    while(--(*d->j) >= 0){
      if(d->a[*d->j]<=d->pivot){ // esce se a[j]<=pivot
        fprintf(stdout, "[DEBUG] [THREAD] Decremento di j:%d i:%i\n",(*d->j), (*d->i));
        xpthread_cond_signal(d->found_element_less_then_pivot,QUI); //segnalo al thread principale
        break;
      }
    } 
    xpthread_mutex_unlock(d->mu, QUI);
    sched_yield(); //rilascio la CPU
  }

  return NULL;
}


// procedura di partizionamento di un array a[0..n-1]
// partiziona l'array in due parti in modo che gli elementi
// della prima parte sono <= degli elementi della seconda parte
// restituisce il numero di elementi nelal prima parte
int partition(int a[], int n)
{
  assert(n>1);
  // scelgo pivot in posizione random 
  int k = random() % n;      // genero posizione random del pivot
  int pivot = a[k];          // elemento pivot
  a[k]=a[0];a[0]=pivot;      // scambia a[k]<->a[0] per mettere il pivot in a[0]

  // procedura di partizionamento
  // l'elemento pivot svolge anche la funzione di sentinella  
  int i= -1;      // puntatore oltre estremo sinistro
  int j = n;      //puntatore oltre estremo destro

  // Se la dimensione è sotto la soglia effettuo partizionamento sequenziale
  if(n < SOGLIA_PARALLELO){
    while(1) {
      while(a[--j]>pivot) ; // esce se a[j]<=pivot
      while(a[++i]<pivot) ; // esce se a[i]>=pivot
      if(i<j) {
        // scambia a[i] <-> a[j]
        int t=a[i]; a[i]=a[j]; a[j]=t;
      }
      else break; 
    }
  // altrimenti effetto partizionamento parallelo
  }else{
    //dati per la sincronizzazione
    bool done=false;
    pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t found_element_less_then_pivot = PTHREAD_COND_INITIALIZER;
    
    partition_data datas;
    datas.a = a;
    datas.i = &i;
    datas.j = &j;
    datas.pivot = pivot;
    datas.done = &done;
    datas.mu = &mu;
    datas.found_element_less_then_pivot = &found_element_less_then_pivot;

    //creo thread per la gestione dell'indice decrescente (j)
    pthread_t t;
    xpthread_create(&t, NULL, &tbody, &datas, QUI);

    while(true) {
      while(a[++i]<pivot){
        fprintf(stdout, "[DEBUG] Incremento di i:%d j:%i\n",i, j);
      }; // esce se a[i]>=pivot

      xpthread_mutex_lock(&mu, QUI);
      xpthread_cond_wait(&found_element_less_then_pivot, &mu, QUI);
      if(i<j) {
        // scambia a[i] <-> a[j]
        int t=a[i]; a[i]=a[j]; a[j]=t;
      }
      else {
        done = true;
        xpthread_mutex_unlock(&mu, QUI);
        break;
      }; 
      xpthread_mutex_unlock(&mu, QUI);
    }

    xpthread_join(t, NULL, QUI);
    xpthread_mutex_destroy(&mu, QUI);
    xpthread_cond_destroy(&found_element_less_then_pivot, QUI);
  }

  // la prima meta' e' a[0] .. a[j] quindi ha j+1 elementi   
  assert(j+1 >0);
  assert(j+1 < n);
  return j+1; 
}


// Quicksort: ordina array a[0]...a[n-1]
// Notate che tutto il lavoro viene fatto da partition!
void quicksort(int b[], int n) {
  if(n>1) {
    int q = partition(b,n);
    assert(q>0 && q<n);   // verifica che entrambe le partizioni non siano vuote
    quicksort(b,q);       // chiamata ricorsiva prima parte 
    quicksort(b+q,n-q);   // chiamata ricorsiva seconda parte
  }
}


// genera array di n elementi con interi random tra 0 e 999999 
int *random_array(int n, int seed)
{
  assert(n>0);
  srandom(seed);
  int *a = malloc(n* sizeof(int));
  assert(a!=NULL);
  for(int i=0;i<n;i++)
    a[i] = (int) random() % 1000000;
  return a;
}

// funzione di confronto tra interi passata a qsort
int intcmp(const void *a, const void *b)
{
  return *((int *) a) - *((int *) b);
}


