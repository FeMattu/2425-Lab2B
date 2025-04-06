// Nuovo esempio di sorting parallelo 
// si procede partizionando l'array a metà e ordinando 
// le due metà in parallelo in maniera ricorsiva.
// la ricorsione termina quando la dimensione
// dell'array è inferiore ad una certa soglia passata da linea di comando
#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include "xerrori.h"

#define QUI __LINE__,__FILE__


// prototipi delle funzioni che appaiono dopo il main()
void merge(int a[], int na, int c[], int nc, int b[]);
int *random_array(int n, int seed);
int intcmp(const void *a, const void *b);
void pmergesort(int *a, int m, int soglia);


// struct contenente la descrizione di un array
// e una soglia per la ricorsione
typedef struct {
  int *a;     // indirizzo array
  int m;      // dimensione array 
  int soglia; 
} array;

// funzione eseguita dai thread ausiliari
// ordina con qsort oppure divide array 
// e ordina in parallelo con un thread ausiliario 
void *tbody(void *arg)
{  
  array *origarg = (array *)arg;    // Casting degli argomenti per il thread
  array d = *origarg;               // Copia locale degli argomenti

  // Se l'array ha meno elementi di soglia ordino con qsort
  if (d.m <= d.soglia) {
    qsort(d.a, d.m, sizeof(int), &intcmp);
  } else {
    // divido il problema in due
    assert(d.m > 1);
    int n1 = origarg->m / 2;  //Dimensione prima metà
    int n2 = origarg->m - n1; //Dimesnione seconda metà

    // Ordino seconda metà
    // Crea una struct dinamica per il thread
    array *right = malloc(sizeof(array));
    if (right == NULL) {
      perror("malloc failed");
      exit(EXIT_FAILURE);
    }
    right->a = &d.a[n1];
    right->m = n2;
    right->soglia = d.soglia;

    pthread_t t;
    fprintf(stderr, "Creo thread che esegue sorting su %d elementi\n", n2);
    xpthread_create(&t, NULL, &tbody, right, QUI);

    // Ordina la prima metà nel thread corrente
    array left = {.a = d.a, .m = n1, .soglia = d.soglia};
    fprintf(stderr, "Eseguo sorting della prima metà su %d elementi\n", n1);
    tbody(&left);

    // Attendi il completamento del thread e libera la memoria
    xpthread_join(t, NULL, QUI);
    free(right);

    // Unisci le due metà ordinate
    int *tmp = malloc(origarg->m * sizeof(int));
    if (tmp == NULL) {
      perror("malloc tmp failed");
      exit(EXIT_FAILURE);
    }
    merge(d.a, n1, d.a + n1, n2, tmp);
    // Copia l'array unito nell'array originale
    for (int i = 0; i < origarg->m; i++) {
      d.a[i] = tmp[i];
    }
    free(tmp);
  }
  return NULL;
} 

// entry point dell'algoritmo di mergesort parallelo
// gli array di lunghezza <= soglia sono ordinati con qsort()
// gli altri sono divisi a metà e ordinati in parallelo
// usando un thread ausiliario
void pmergesort(int *a, int m, int soglia)
{  
  if(m<=soglia){
    qsort(a,m,sizeof(int),&intcmp);
    return;
  }

  //creeo nuovo thread per effettuare il sort
  array d = {a,m,soglia};
  pthread_t t;
  xpthread_create(&t,NULL,&tbody,&d,QUI);
  xpthread_join(t,NULL,QUI);
} 

 
// ordina un array di argv[1] interi random generati con 
// seed argv[2] termimando la ricorsione quando la dimensione
// degli array raggiunge argv[3]
int main(int argc, char *argv[])
{
  if(argc!=4) {
    fprintf(stderr, "Uso:\n\t   %s num_interi seed soglia\n", argv[0]);
    exit(1);
  }
  int n = atoi(argv[1]);
  assert(n>0);
  int soglia = atoi(argv[3]);
  assert(soglia>1);
  // genera array random di n elementi
  int *a = random_array(n,atoi(argv[2]));
  // calcola somma prima dell'ordinamento
  long somma=0;
  for(int i=0;i<n;i++) somma += a[i];
  
  // esegue l'ordinamento
  pmergesort(a,n,soglia);
  
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


// funzione per il merge di due array in un terzo array già allocato
// merge di a[0...n1-1] e c[0... n2-1] dentro b[]
void merge(int a[], int na, int c[], int nc, int b[])
{
  assert(a!=NULL && c!=NULL && b!=NULL);
  assert(na>0 && nc>0);
  
  int i=0; // indice per a[]
  int j=0; // indice per c[]
  int k=0; // indice per b[]
  
  // scorro a[] e c[] e copio il minore in b[]
  while(i<na && j<nc) {
    if(a[i]<c[j]) {
      b[k] = a[i];
      i++;
    } else {
      b[k] = c[j];
      j++;
    }
    k++;
  }
  
  // copio il resto di a[] in b[]
  while(i<na) {
    b[k] = a[i];
    i++; k++;
  }
  
  // copio il resto di c[] in b[]
  while(j<nc) {
    b[k] = c[j];
    j++; k++;
  }
  assert(i==na);
  assert(j==nc);
  assert(k==na+nc); 
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


