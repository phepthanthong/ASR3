/* cons.c */

/*
   Ce programme affiche le contenu de la mémoire partagée
   Arrêt par Contrôle-C
*/

/* 
   fonctionne seulement si prod et cons sont lancés 
   dans le même répertoire (voir ftok(".",'A')).
*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

struct donnees {
  int nb;
  int total;
};

int encore;

void arret(int signal)
{
  encore=0;
}

int main(void) 
{
  key_t cle;
  int id;
  struct donnees *commun;
  struct sigaction a;

  cle = ftok(".",'A');
  if (cle==-1) {perror("ftok"); exit(EXIT_FAILURE);};
  id = shmget(cle,sizeof(struct donnees),0);

  if (id == -1) {  
    switch(errno) {
    case ENOENT:
      printf("pas de segment\n");
      exit(EXIT_SUCCESS);
    default:
      perror("shmget"); 
      exit(EXIT_FAILURE);
    };
  };
  commun = (struct donnees *)shmat (id,NULL,SHM_R);
  if (commun == NULL) {perror("shmat"); exit(EXIT_FAILURE);};

  encore = 1;

  a.sa_handler = arret;
  sigemptyset(&a.sa_mask); 
  a.sa_flags = 0;
  sigaction(SIGINT,&a,NULL);

  while(encore)
    {
      sleep(2);
      printf("sous-total %d= %d\n",commun->nb,commun->total);
    };

  printf("---\n");
  if ( shmdt((char *)commun) == -1)
    {perror("shmdt"); exit(EXIT_FAILURE);};
  exit(EXIT_SUCCESS);
}
