#include "xerrori.h"

#define QUI __LINE__,__FILE__

int main(int argc, char *argv[]){
    if(argc!=2){
        fprintf(stderr,"Uso: %s numero_iniziale\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]); //converto input in intero

    if(n<0){
        fprintf(stderr, "N deve essere un valore positivo\n");
        exit(1);
    }

    if(n==0) return 0;  // Se N è 0 allora non si termina direttamente senza nemmeno
    //far partire BOB

    fprintf(stdout,"[%d] ALICE avviata correttamente\n", getpid());
    fflush(stdout);
    
    union sigval v = {.sival_int = n};  //Union per inviare 'n' a BOB
    pid_t bob_pid = xfork(QUI);         //Creo processo figlio per avviare BOB
    if(bob_pid == -1) xtermina("fork fallita\n", QUI);
    
    if(bob_pid==0){//figlio
        fprintf(stdout, "Cambio codice a processo figlio -> BOB\n");
        if(execl("./bob.out", "bob.out", (char *) NULL)==-1){
            xtermina("Execl fallita\n", QUI);
        }
    }else {
        fprintf(stdout, "Bob Pid: %d\n", bob_pid);
    }

    // Setto la maschera per attendere ils egnale SIGRTMIN
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGRTMIN);

    int e = pthread_sigmask(SIG_BLOCK, &mask, NULL);
    if(e!=0) xtermina("Errore pthread_sigmask\n", QUI);

    //variabile per il valore ricevuto
    siginfo_t info;

    //Fase di handshake con bob
    fprintf(stdout, "Attendo che BOB sia pronto\n");
    do{
        int signo = sigwaitinfo(&mask, &info);
        if(signo<0) xtermina("Errore sigwaitinfo\n", QUI);
    }while(info.si_value.sival_int != 1);

    fprintf(stdout,"Invio %d a BOB\n", n);
    //Se la exec non è fallita allora invio il segnale con il numero a BOB
    sigqueue(bob_pid, SIGRTMIN, v);

    srand(time(NULL)); // inizializza il generatore (una sola volta!)

    while(n!=0){
        int signo = sigwaitinfo(&mask, &info);
        if (signo <0) xtermina("Errore sigwaitinfo\n", QUI);
        n = info.si_value.sival_int; //prendo il valore aggiornato

        if(n==0){
            fprintf(stdout,"Ha vinto BOB\n");
            return 0;
        }

        if(n%2==0) {
            if(rand() % 2 == 0) n-=1;
            else n/=2;
        }else n-=1;

        fprintf(stdout, "[ALICE] %d\n", n);

        v.sival_int=n;

        sigqueue(bob_pid, SIGRTMIN, v);     //invio il segnale a BOB con il valore
    }

    return 0;
}