#include "xerrori.h"
#define QUI __LINE__,__FILE__

volatile sig_atomic_t tot_segnali = 0;
volatile sig_atomic_t finito = 0;
int N = 0;
pid_t pong_pid = 0;
pid_t ping_pid = 0;

void handler_ping(int s){
  tot_segnali++;
  printf("[%d] [PING] Ricevuto un PONG [%d]\n", getpid(), tot_segnali);
  kill(pong_pid, SIGUSR1);
  if (tot_segnali==N/2) finito=1;
}

void handler_pong(int s){
  tot_segnali++;
  printf("[%d] [PONG] Ricevuto un PING [%d]\n", getpid(), tot_segnali);
  kill(ping_pid, SIGUSR1); //il padre di PONG è PING
  if (tot_segnali==N/2) finito=1;
}

void imposta_handler(void (*handler)(int)){
  // definisce signal handler 
  struct sigaction sa;
  sa.sa_handler = handler;
  // setta sa.sa_mask che è la maschera di segnali da bloccare
  // durante l'esecuzione di handler().
  sigfillset(&sa.sa_mask);      // tutti i segnali nella maschera ...
  sigaction(SIGUSR1,&sa,NULL);  // handler per USR1
}

void handler_ready(int s) { ; }

int main(int argc, char *argv[]){
    if(argc!=2) {
        fprintf(stderr,"Uso\n\t%s numero_scambi\n", argv[0]);
        exit(1);
      }
      // conversione input
      N = atoi(argv[1]);
      if(N<=0 || N%2!=0){
        fprintf(stderr, "Il numero degli scambi deve essere un numero positivo e pari: %d\n", N);
        exit(1);
      }

      ping_pid=getpid();

      printf("[%d] PING correttamente avviato\n", ping_pid);

      pong_pid=xfork(QUI); // Creo il processo figlio (PONG)


      if(pong_pid==0){// codice processo figlio creato -> PONG
        printf("[%d] PONG correttamente avviato\n", getpid());
        imposta_handler(&handler_pong); // Imposto handler di PONG
        kill(ping_pid, SIGUSR2);       // Notifico a PING che sono pronto
        while(!finito){pause();}        // Attendo di ricevere un PING
        printf("[PONG] Terminato\n");
        return 0;
      }

      imposta_handler(&handler_ping); // Imposto handelr di PING

      //handshake con PONG per attendere che sia pronto
      struct sigaction sa_ready;
      sa_ready.sa_handler = &handler_ready;
      sigfillset(&sa_ready.sa_mask);
      sigaction(SIGUSR2,&sa_ready,NULL);
      pause();

      kill(pong_pid, SIGUSR1);        // Avvio gli scambi
      fprintf(stdout,"[PING] Inviato Segnale di avvio a PONG\n");
      while(!finito){pause();}   // Attendo di ricevere un PONG
      fprintf(stdout, "[PING] Terminato\n");

      printf("Abbiamo finito di fare scambi a ping-pong\n");
      return 0;
}

