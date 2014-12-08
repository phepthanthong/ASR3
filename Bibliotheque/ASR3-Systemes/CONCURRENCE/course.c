#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

#define NB_THREADS 10
#define MAX 20000

 int cpt;

void *f_thread(void *arg)
{
  int id=(int)arg;
  int i;
  for(i=0;i<MAX;i++) {
	  cpt++;
  }

  return (void*)id;
}

int main(int argc, char**argv)
{
  pthread_t tid[NB_THREADS];
  cpt=0;
  int i;
  for(i=0;i<NB_THREADS;i++) 
  {
    int ret = pthread_create(&tid[i], NULL, f_thread, (void*)i);
    if(ret) {
      fprintf(stderr, "Impossible de créer le thread %d\n", i);
      return 1;
    }
  }
  
  void *ret_val;
  for(i=0;i<NB_THREADS;i++) 
  {
    int ret = pthread_join(tid[i], &ret_val);
    if(ret) {
      fprintf(stderr, "Erreur lors de l'attente du thread %d\n", i);
      return 1;
    }
  }
  printf("cpt vaut %d\n", cpt);
  return 0;
}
