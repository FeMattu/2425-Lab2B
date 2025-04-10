#include "xerrori.h"

#define QUI __LINE__,__FILE__

int main(int argc, char *argv[]){
    fprintf(stdout, "[%d] BOB avviato correttamente\n", getpid());
    //Imposto la maschera dei segnali che volgio ricevere
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGRTMIN);

    // Blocco i segnali per questo thread
    int e = pthread_sigmask(SIG_BLOCK, &mask, NULL);
    if(e!=0) xtermina("Errore pthread_sigmask\n", QUI);

    //Fase di handshake, notifico ad ALICE che sono pronto a giocare
    union sigval ready = {.sival_int = 1};
    sigqueue(getppid(), SIGRTMIN, ready);

    //Attendo di ricevere il valore da Alice
    siginfo_t info;
    int n = -1;
    union sigval v = {.sival_int = n};  //Union per inviare 'n' ad ALICE
    srand(time(NULL)); // inizializza il generatore (una sola volta!)

    fprintf(stdout, "[%d] [BOB] Attendo di ricevere il valore da Alice\n", getpid());
    while(n!=0){
        int signo = sigwaitinfo(&mask, &info);
        if (signo <0) xtermina("Errore sigwaitinfo\n", QUI);
        n = info.si_value.sival_int; //prendo il valore aggiornato
        
        if(n==0){
            fprintf(stdout,"Ha vinto ALICE\n");
            return 0;
        }

        if(n%2==0) {
            if(rand() % 2 == 0) n-=1;
            else n/=2;
        }else n-=1;

        fprintf(stdout, "[BOB] %d\n", n);

        v.sival_int=n;

        sigqueue(getppid(), SIGRTMIN, v);     //invio il segnale ad ALICE (padre) con il valore
    }
    return 0;
}