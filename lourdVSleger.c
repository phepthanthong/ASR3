#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h> // pour le random

#define nbLourds 100
//#define nbThread 100

int main()
{
  int retour;
  pid_t pid;
  int status;

  printf("3... 2... 1... GOOOO ! \n");
  signal(SIGUSR1, compet);
}

void compet()
{
  signal(SIGUSR1, compet);

  int i;
  for (i=0; i<nbLourds; i++)
    {
      if ((retour = fork()) < 0)
	{
	  // traitement erreur fork()
	  fprintf(stderr,"Erreur fatale : fork()\n");
	  exit(EXIT_FAILURE);
	}
      if (retour == 0)
	{
	  execl("lourds", "lourds", NULL);
	  execl("legers", "legers", NULL);
	}
    }
  
}

int aleatoire()
{
  srand(time(NULL)+getpid());
  float max = 10;
  int alea = (max * rand() / RAND_MAX);
  return (alea);
}
