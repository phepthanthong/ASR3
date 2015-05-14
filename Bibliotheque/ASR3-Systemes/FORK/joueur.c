/* joueur.c */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h> // pour le random


int aleatoire()
{
  srand(time(NULL)+getpid());
  float max = 3;
  int alea = (max * rand() / RAND_MAX);
  return (alea);
}

int main()
{
  int k=aleatoire();
  if (aleatoire() == 0)
    {
      fprintf(stdout, "Processus numero %d joue PIERRE \n",getpid());
      write(p[i][1],&k,1);
      exit(0);
    }
  if (aleatoire() == 1)
    {
      fprintf(stdout, "Processus numero %d joue CISEAUX \n",getpid());
      write(p[i][1],&k,1);
      exit(1);
    }
  
  if (aleatoire() == 2)
    {	    
      fprintf(stdout, "Processus numero %d joue PAPIER \n",getpid());
      write(p[i][1],&k,1);
      exit(2);
    }
}
