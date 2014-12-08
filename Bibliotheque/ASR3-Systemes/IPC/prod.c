const/* prod.c */

/*
   ce programme lit une suite de nombres,
   et effectue le cumul dans une variable en
   mémoire partagée.uu
*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

struct donnees {
  int nb;
  int total;
};

int main(void) 
{
  key_t cle;
  int id;
  struct donnees *commun;
  int reponse;

  cle = ftok(".",'A'); 
  if (cle==-1) {perror("ftok"); exit(EXIT_FAILURE);};
  id = shmget(cle,sizeof(struct donnees),
	      IPC_CREAT | IPC_EXCL | 0666);
  if (id == -1) {
    switch(errno) {
    case EEXIST :
      fprintf(stderr,"Le segment existe deja\n");
      break;
    default:
      perror("shmget"); 
      break;
    }
    exit(EXIT_FAILURE);
  };
  commun = (struct donnees *)shmat (id,NULL,SHM_R | SHM_W);
  if (commun == NULL) {perror("shmat"); exit(EXIT_FAILURE);};

  commun->nb    = 0;
  commun->total = 0;

  while(1)
    {
      printf("+ ");
      if (scanf("%d",&reponse)!=1) break;
      commun->nb++;
      commun->total += reponse;
      printf("sous-total %d= %d\n",commun->nb,commun->total);
    };
  printf("---\n");
  /* detachement */
  if (shmdt((char *)commun) == -1) {
    perror("shmdt"); 
    exit(EXIT_FAILURE);
  };
  /* suppression segment */
  if (shmctl(id,IPC_RMID,NULL) == -1) {
    perror("shmctl(remove)");
    exit(EXIT_FAILURE);
  };
  exit(EXIT_SUCCESS);
}
