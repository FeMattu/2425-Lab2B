#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include "xerrori.h"
#include "limits.h"

#define BLOCK_SIZE 20
#define BUFFER_SIZE 8 //32 bit
#define QUI __LINE__ , __FILE__
#define SENTINELLA NULL

typedef struct{
    sem_t *sem_free_slots;
    sem_t *sem_data_items;
    int **buffer;
    int *pindex;
    int *filerim;
    pthread_mutex_t *mutex;
    pthread_mutex_t *mufilerim;
    const char* filename;
}dati;

void* tbody(void* a){
    dati *d = (dati *)a;
    FILE *f = fopen(d->filename, "rb");
    if(f==NULL) {
        fprintf(stderr,"[P] Errore apertura file: %s", d->filename); 
        pthread_exit(NULL);
    }

    //Lettura a blocchi di BLOCK_SIZE dati dai file
    while(true) {
        int *blocco = malloc(BLOCK_SIZE * sizeof(int));
        size_t letti = fread(blocco, sizeof(int), BLOCK_SIZE, f);
        fprintf(stdout, "[P] Letti %zu interi da %s\n", letti, d->filename);

        //se sono stati letti meno di BLOCK_SIZE dati allora faccio padding con il primo valore
        if (letti > 0 && letti < BLOCK_SIZE) {
            for (size_t i = letti; i < BLOCK_SIZE; i++) {
                blocco[i] = blocco[0];  //un qualsiasi valore che sia presente nel blocco non influenza
                                        //il calcolo del valore min max
            }
        }

        // se non vengono più letti dati abbiamo finito
        if(letti <= 0) {
            free(blocco);
            break;
        }

        //altrimenti inserisco blocco nel buffer
        xsem_wait(d->sem_free_slots,QUI);               //controllo se c'è ancora posto nel buffer
        xpthread_mutex_lock(d->mutex, QUI);             //faccio la lock per pindex
        d->buffer[(*d->pindex)++ % BUFFER_SIZE]=blocco;
        xpthread_mutex_unlock(d->mutex, QUI);
        xsem_post(d->sem_data_items,QUI);               // seganlo che è stato aggiunto un blocco nel buffer
        fprintf(stdout, "[P] Blocco dati da %zu interi in %s caricato nel buffer\n", letti, d->filename);
    }
    fclose(f);
    xpthread_mutex_lock(d->mufilerim, QUI);
    (*d->filerim)--;
    xpthread_mutex_unlock(d->mufilerim, QUI);
    //dato sentinella per seganlare al consumatore che sono finiti i dati da leggere
    xsem_wait(d->sem_free_slots, QUI);
    xpthread_mutex_lock(d->mutex,QUI);
    d->buffer[(*d->pindex)++%BUFFER_SIZE]=SENTINELLA;
    xpthread_mutex_unlock(d->mutex, QUI);
    xsem_post(d->sem_data_items, QUI);

    fprintf(stdout, "[P] Dati del file %s scritti nel buffer\n", d->filename);
    return NULL;
}

/**
 * Funzione che resituisce dato un blocco contenente interi a 32 bit 
 * il massimo e il minimo presente.
 */
void minmax(int *blocco, const size_t num_dati, int *min, int *max){
    for (size_t i = 0; i < num_dati; i++) {
        if (blocco[i] < *min) *min = blocco[i];
        if (blocco[i] > *max) *max = blocco[i];
    }
}

//il main è l'unico consumatore
int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stdout, "Uso:\n\t   %s [...Input files]\n", argv[0]);
        exit(1); 
    }

    //setup
    int nproduttori = argc-1;  // numero thread ausiliari (produttori)
    int filerim = nproduttori; // file rimasti da leggere
    assert(nproduttori>0);   

    //buffer circolare
    int *buffer[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = NULL;
    }

    // inizializzazione dei thread e dei loro argomenti
    int pindex=0;                                           //indice di scrittura dei produttori
    pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;         //mutex per la gestione di pindex
    pthread_mutex_t mufilerim = PTHREAD_MUTEX_INITIALIZER;  //mutex per la gestione dei file ancora da leggere
    pthread_t t[nproduttori];
    dati a[nproduttori];

    //Semafori per la gestione dell'accesso al buffer e questi non sono condivisi con altri processi
    sem_t sem_free_slots, sem_data_items;
    xsem_init(&sem_free_slots,0,BUFFER_SIZE, QUI);  //buffer inizialmente è totalmete libero
    xsem_init(&sem_data_items,0,0,QUI);             //buffer dati inizialmente è vuoto

    //creazione dei thread produttori
    for(int i = 0; i < nproduttori; i++){
        a[i].buffer = buffer;
        a[i].filename = argv[i+1];
        a[i].mutex = &mu;
        a[i].sem_data_items = &sem_data_items;
        a[i].sem_free_slots = &sem_free_slots;
        a[i].filerim = &filerim;
        a[i].mufilerim = &mufilerim;
        a[i].pindex = &pindex;
        xpthread_create(&t[i],NULL,&tbody,&a[i],__LINE__,__FILE__);
    }

    fprintf(stdout, "[C] %d thread ausiliari creati\n",nproduttori);

    //indice per la gestione della lettura da parte dell'unico consumatore (Main)
    int cindex=0;

    // setup per calcolo min-max
    int min = INT_MAX;
    int max = INT_MIN;

    //leggo dati dal buffer
    while(true){
        int *blocco;    //blocco dati da leggere
        xsem_wait(&sem_data_items, QUI);
        blocco = buffer[cindex%BUFFER_SIZE];
        xpthread_mutex_lock(&mu,QUI);       
        buffer[cindex%BUFFER_SIZE] = NULL;  // rimuovo il blocco poichè se non viene tolto va in deadlock
        xpthread_mutex_unlock(&mu,QUI);
        xsem_post(&sem_free_slots, QUI);
        if(blocco != SENTINELLA){
            fprintf(stdout, "[C] Blocco valido ricevuto: elaboro...\n");
            minmax(blocco,BLOCK_SIZE,&min,&max);
            free(blocco);   //libero il blocco quando sono sicuro che questo non è una SENTINELLA
        }
        cindex+=1;
        //controllo se sono ancora presenti dati nel buffer quando sono stati letti tutti i file
        xpthread_mutex_lock(&mufilerim, QUI);
        if(filerim==0 && blocco==SENTINELLA){
            int dati = false;
            for(int i=0; i<BUFFER_SIZE; i++)
                if((buffer[i]!=SENTINELLA || buffer[i]!=NULL) && !dati){
                    dati=true;
                    break;
                }
            if(!dati) {
                xpthread_mutex_unlock(&mufilerim, QUI);
                break;
            }
        }
        xpthread_mutex_unlock(&mufilerim, QUI);
    }
    fprintf(stdout,"[C] Fine lettura, non ci sono più dati nel buffer\n");
    fprintf(stdout, "[C] Minimo calcolato: %d\tMassimo calcolato: %d\n", min,max);

    //join dei thread e uscita
    for(int i = 0; i < nproduttori; i++){
        xpthread_join(t[i],NULL,QUI);
    }

    //distruggo tutti i mutex e semafori creati
    pthread_mutex_destroy(&mu);
    pthread_mutex_destroy(&mufilerim);
    xsem_destroy(&sem_data_items,QUI);
    xsem_destroy(&sem_free_slots,QUI);
    return 0;
}