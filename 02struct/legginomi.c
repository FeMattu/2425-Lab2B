#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione ass
#include <string.h>   // funzioni per stringhe
#include <errno.h>    // richiesto per usare errno


// Scopo del programma:
// mostrare il funzionamento di getline() e strtok() 
// Eseguire passando come argomento persone.txt


// prototipo funzione dopo il main
void termina(const char *messaggio);


// "elimina" gli spazi in testa a una stringa
// restituisce un puntatore alla prima posizione
// che non è uno spazio
char *elimina_spazi_testa(char s[])
{
  int i=0;
  while(s[i]==' ')
    i++;
  assert(s[i]!=' ');
  return &s[i];
}


// main che legge le linee e le spezza al ;
// elimina eventuali spazi iniziali 
// e stampa il risultato
int main(int argc, char *argv[])
{

  if(argc!=2) {
    printf("Uso: %s nomefile\n",argv[0]);
    exit(1);
  }
  FILE *f = fopen(argv[1],"r");
  if(f==NULL) termina("Errore apertura file");

  // ciclo di lettura delle linee del file
  char *buffer=NULL;    // usata da getline()
  size_t n=0;           // usata da getline()
  while(true) {
    //leggi linea dal file
    ssize_t e = getline(&buffer,&n,f);
    if(e<0) {        // se e<0 assumiamo sia finito il file
      free(buffer);  // dealloco il buffer usato per le linee 
      break;
    }
    // esegue la tokenizzazione di buffer: legge primo token 
    char *s = strtok(buffer,";\n");
    while(s!=NULL) {
      s = elimina_spazi_testa(s); // elimina spai in testa
      if(strlen(s)>0) printf("Letto: <%s>\n",s);
      // legge il prossimo token
      s = strtok(NULL,";\n");
    }
  } // end while del getline
  fclose(f);
  return 0;
}




// stampa su stderr il  messaggio che gli passo
// se errno!=0 stampa anche il messaggio d'errore associato 
// a errno. dopo queste stampe termina il programma
void termina(const char *messaggio)
{
  if(errno==0) 
     fprintf(stderr,"%s\n",messaggio);
  else 
    perror(messaggio);
  exit(1);
}



