// esempio produttore/consumatore tra processi
// utilizzando memoria condivisa e named semaphores
#include "xerrori.h"
// #include <time.h>

#define QUI __LINE__,__FILE__
#define Buf_size 10 
#define Shm        "/my_shm"
#define Sem_items  "/my_items"
#define Sem_slots  "/my_slots"
#define Mutex_cons "/cons_mutex"
#define CIndex "/cindex"
#define CONSUMATORI 3



int main(int argc,char *argv[])
{
  if(argc!=2) {
    fprintf(stderr,"Uso\n\t%s num_items\n", argv[0]);
    exit(1);
  }
  // conversione input
  int n= atoi(argv[1]);

  // ---- creazione buffer prod-cons in memoria condivisa
  int shm_size = Buf_size*sizeof(int);
  int fd = xshm_open(Shm,O_RDWR | O_CREAT, 0666,QUI);
  xftruncate(fd, shm_size, QUI);
  int *b = simple_mmap(shm_size,fd, QUI);
  close(fd); // dopo mmap e' possibile chiudere il file descriptor  
    // ---- creazione semafori named
  sem_t *free_slots = xsem_open(Sem_slots,O_CREAT|O_EXCL,0666,Buf_size,QUI);
  sem_t *data_items = xsem_open(Sem_items,O_CREAT|O_EXCL,0666,0,QUI);
  // non devo usare unlink qui altrimenti il consumatore non
  // non vede memoria condivisa e semafori

  // creazione del blocco di memoria per cindex
  int shm_cindex_size = 1*sizeof(int);
  int fd_cindex = xshm_open(CIndex,O_RDWR | O_CREAT, 0666, QUI);
  xftruncate(fd_cindex,shm_cindex_size,QUI);
  int *cindex = simple_mmap(shm_cindex_size,fd_cindex,QUI);
  close(fd_cindex);
  *cindex=0;
  //creazionde del semaforo per gestire cindex
  sem_t *mutex = xsem_open(Mutex_cons,O_CREAT|O_EXCL,0666,1,QUI); //inizializzato ad 1 per renderlo binario
    
  for(int i=0; i<CONSUMATORI;i++){
    pid_t p = xfork(QUI);
    sleep(1); //serve per evitare che venga schedulato un solo figlio e il produttore termini prima dell'esecuzione degli altri figli
    // non assicura, ma aumenta la possibilità che vengano eseguiti anche gli altri figli prima della terminazione del produttore
    // così da evitare che i filedescriptor e i semafori siano ancora aperti e non si abbia errore
    if(p==0) {// figlio
      printf("[%d] Figlio %d-esimo di %d\n",getpid(),i,getppid());
      if(execl("./shm_cons.out", "", (char *) NULL)==-1){
        xtermina("Exec fallita",QUI);
      }    
    }  
  }

  // loop produttore 
  int pindex = 0;
  for(int j=1;j<=n;j++) {
    xsem_wait(free_slots,QUI);
    b[pindex%Buf_size] = j;
    pindex++;
    xsem_post(data_items,QUI);
    printf("Item %d written\n",j); 
  }
  // valore di terminazione
  xsem_wait(free_slots,QUI);
  b[pindex%Buf_size] = -1;
  pindex++;
  xsem_post(data_items,QUI);
  printf("Item %d written\n",-1);
  
  // prenota cancellazione di shm e sem
  xsem_unlink(Sem_items,QUI); 
  xsem_unlink(Sem_slots,QUI); 
  xsem_unlink(Mutex_cons,QUI);
  xshm_unlink(Shm,QUI);     
  xshm_unlink(CIndex,QUI);

  // unmap memoria condivisa e chiude i semafori
  xmunmap(b,shm_size,QUI);
  xmunmap(cindex,shm_cindex_size,QUI);
  xsem_close(data_items,QUI);
  xsem_close(free_slots,QUI);
  xsem_close(mutex,QUI);
  return 0;
}
