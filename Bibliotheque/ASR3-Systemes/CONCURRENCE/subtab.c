#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

#include "temps.h"

#define NB_THREADS 2
#define MAX 8*1024*1024

int tab[MAX];
int sum;

void *f_thread(void *arg)
{
  int id=(int)arg;
  int i;
  /* nombre d'elements a traiter par ce thread */
  int tranche=MAX/NB_THREADS;
  /* indice de depart */
  int borne_min=tranche*id;
  /* indice de fin */
  int borne_max=tranche*(id+1);

  printf("thread %d : de %d à %d\n", id, borne_min, borne_max);

  for(i=borne_min;i<borne_max;i++) {
	  sum+=tab[i];
  }
  return (void*)id;
}

/* remplit le tableau avec n'importe quoi*/
void remplir_tab()
{
  int i;
  for(i=0;i<MAX;i++)
    tab[i]=(i*i)%10;
}

int main(int argc, char**argv)
{
  pthread_t tid[NB_THREADS];
  int i;
  void *ret_val;
  struct timeval tv1,tv2;

  sum=0;
  remplir_tab();

  gettimeofday(&tv1,NULL);

  for(i=0;i<NB_THREADS;i++) 
  {
    int ret = pthread_create(&tid[i], NULL, f_thread, (void*)i);
    if(ret) {
      fprintf(stderr, "Impossible de créer le thread %d\n", i);
      return 1;
    }
  }
  
  for(i=0;i<NB_THREADS;i++) 
  {
    int ret = pthread_join(tid[i], &ret_val);
    if(ret) {
      fprintf(stderr, "Erreur lors de l'attente du thread %d\n", i);
      return 1;
    }
  }

  gettimeofday(&tv2,NULL);

  printf("sum vaut %d\n", sum);
  printf("duree du calcul : %f ms\n", ((float)TIME_DIFF(tv1,tv2)/1000));

  return 0;
}
