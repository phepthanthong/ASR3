#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 10 // taille du tableau
#define NB_P 2 // Nb producteur
#define NB_C 2 // Nb consommateur
#define IT 20 // iteration producteur ou consommateur

int nb = 0, buffer[MAX], in = 0, out = 0; // ressource commune

//declaration des semaphores

sem_t mutexin; // mutex pour l'ecriture
sem_t mutexout; // mutex pour la lecture
sem_t nonplein; // Nb places libres
sem_t nonvide; // Nb places occupees

void *prod(void* me)
{
  int i;
  for (i=0; i<IT; i++)
    {
      sem_wait(&nonplein);
      sem_wait(&mutexin);
      printf("Je suis le producteur %d et je modifie la ressource \n", (int) me);
      nb++; // modification de la ressource
      printf("Je suis le producteur %d et je mets la ressource %d dans le buffer %d \n", (int) me, nb, in);
      buffer[in] = nb;
      in = (in + 1)%MAX;
      sem_post(&mutexin);
      sem_post(&nonvide);
    }
  return NULL;
}

void *cons(void* me)
{
  int i, tmp;
  for (i=0; i<IT; i++)
    {
      sem_wait(&nonvide);
      sem_wait(&mutexout);
      tmp = buffer[out];
      printf("Je suis le consommateur %d, je prends la ressource dans le buffer %d et j'affiche le nombre qui est: %d \n", (int) me, out, tmp);
      out = (out + 1)%MAX;
      sem_post(&mutexout);
      sem_post(&nonplein);
    }
  return NULL;
}

int main(void)
{
  pthread_t produ[NB_P], conso[NB_C];
  int r, t;
  // init semaphore
  sem_init(&mutexin, 0, 1);
  sem_init(&mutexout, 0, 1);
  sem_init(&nonvide, 0, 0);
  sem_init(&nonplein, 0, MAX);
 
  for (t=0; t<MAX; t++)
    buffer[t] = 0;

  for (t=0; t<NB_P; t++)
    {
      r = pthread_create(&(produ[t]), NULL, prod, (void*)t);
      if (r)
	printf("ERROR: return code from pthread_join is %d \n", r);
    }

  for (t=0; t<NB_C; t++)
    {
      r = pthread_create(&(conso[t]), NULL, cons, (void*)t);
      if (r)
	printf("ERROR: return code from pthread_join is %d \n", r);
    }

  for (t=0; t<NB_P; t++)
    pthread_join(produ[t],0);
  for (t=0; t<NB_C; t++)
    pthread_join(conso[t],0);

  sem_destroy(&mutexin);
  sem_destroy(&mutexout);
  sem_destroy(&nonvide);
  sem_destroy(&nonplein);
  return 0;
}
