#include "xerrori.h"
#define QUI __LINE__,__FILE__

volatile sig_atomic_t tot_segnali = 0;
volatile int N = 0;
volatile pid_t pong = 0;

void handler_ping(int s){
  tot_segnali++;
  printf("[%d] PING", getpid());
  kill(pong, SIGUSR1);
  if (tot_segnali==N/2) exit(tot_segnali);
}

void handler_pong(int s){
  tot_segnali++;
  printf("[%d] PONG", getpid());
  kill(getppid(), SIGUSR1);
  if (tot_segnali==N/2) exit(tot_segnali);
}

int main(int argc, char *argv[]){
    if(argc!=2) {
        fprintf(stderr,"Uso\n\t%s numero_scambi\n", argv[0]);
        exit(1);
      }
      // conversione input
      int n= atoi(argv[1]);
      pritnf("[%d] PING correttamente avviato", getpid());

      // definisce signal handler 
      struct sigaction sa;
      sa.sa_handler = &handler_pong;
      // setta sa.sa_mask che è la maschera di segnali da bloccare
      // durante l'esecuzione di handler().
      sigfillset(&sa.sa_mask);          // tutti i segnali nella maschera ...
      // sigdelset(&sa.sa_mask,SIGUSR1);   // ... tranne SIGUSR1
      sigaction(SIGUSR1,&sa,NULL);  // handler per USR1
      sigaction(SIGUSR2,&sa,NULL);  // stesso handler per USR2
      // definisco variabile dove salvo il settaggio attuale per SIGINT
      struct sigaction oldsa;
      sigaction(SIGINT,&sa,&oldsa);

      pong=xfork(QUI); 

      if(pong==0){//allora sono processo filgio creato -> PONG
        printf("[%d] PONG correttamente avviato", getpid());
        
      }

      // loop ping

}

