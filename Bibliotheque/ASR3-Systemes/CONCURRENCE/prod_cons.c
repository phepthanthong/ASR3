#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 5
#define nbProd 2
#define nbCons 3
#define read 1
#define write 0
char tube[MAX];

pthread_mutex_t m;
int rw;
void* producteur(void* arg) 
{
  printf("producteur\n");
  int i=0;
  char c='a';
  
  while(i<MAX) 
    {
      pthread_mutex_lock(&m);
      if (rw == write)
	{
	  i++;
	  tube[i]=c;
	  c++;
	  if(c>'z')
	    c='a';
	  rw = read;
	}
      pthread_mutex_unlock(&m);
      sleep(1);
    }
  return NULL;  
}

void* consommateur(void* arg)
{
  printf("consommateur\n");
  char c;
  int i;
 
  while(i<MAX)
    {
      pthread_mutex_lock(&m);
      if (rw == read)
	{
	  if(tube[i] != 0)
	    {
	      printf("conso : lu : %c\n", tube[i]);
	      tube[i]=0;

	    }
	  rw = write;  
	}
      pthread_mutex_unlock(&m);  
    }
  return NULL;
}
int main(int argc, char** argv) 
{
  pthread_t prod, prod1, cons, cons1;
  memset(tube, 0, MAX);
  //int i = 0;
  rw = write;
  pthread_mutex_init(&m, NULL);
  pthread_create(&prod, NULL, producteur, (void*)1);
  pthread_create(&prod1, NULL, producteur, (void*)2 );
  pthread_create(&cons, NULL, consommateur, (void*)1);
  pthread_create(&cons1, NULL, consommateur, (void*)2);
  pthread_join(prod, NULL);
  pthread_join(prod1, NULL);
  pthread_join(cons, NULL);
  pthread_join(cons1, NULL);
  pthread_mutex_destroy(&m);
  return 0;
}
