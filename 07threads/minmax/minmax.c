#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include "xerrori.h"

#define BLOCK_SIZE 20
#define BUFFER_SIZE 8 //32 bit

typedef struct{

}dati;

void* tbody(void* a){
    dati *d = (dati *)a;
}

//il main è l'unico consumatore

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "Uso:\n\t   %s [...Input files]", argv[0]);
        exit(1);
    }

    int nproduttori = argc-1;  // numero thread ausiliari (consumatori)
    assert(nproduttori>=0);
    int tot_primi = 0;
    long tot_somma = 0;
    int e,n,cindex=0;    
    // inizializzazione dei thread e dei loro argomenti
    int buffer[BUFFER_SIZE];
    int pindex=0;
    pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
    pthread_t t[nproduttori];
    dati a[nproduttori];

    //creazione dei thread consumatori
    for(int i = 0; i < nproduttori; i++){
        xpthread_create(&t[i],NULL,&tbody,&a[i],__LINE__,__FILE__);
    }



    //joi dei thread e uscita
    for(int i = 0; i < nproduttori; i++){
        xpthread_join(&t[i],NULL,__LINE__,__FILE__);
    }
    pthread_mutex_destroy(&mu);
}