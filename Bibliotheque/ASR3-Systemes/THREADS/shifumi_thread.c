/* shifumi.c */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h> // pour le random
#include <pthread.h>

void * joueur(void * int)
{

}

int aleatoire()
{
  srand(time(NULL)+getpid());
  float max = 3;
  int alea = (max * rand() / RAND_MAX);
  return (alea);
}


int main(int argc, char *argv[])
{
  int i;      // compteur
  int retour; // retour fork
  pid_t pid;  // pid
  int status; // valeur de retour fils termine

  int nb = atoi(argv[1]);

  for (i=0; i<nb; i++)
    {
      if ((retour = fork()) < 0)
	{
	  // traitement erreur fork()
	  fprintf(stderr,"Erreur fatale : fork()\n");
	  exit(EXIT_FAILURE);
	}
      if (retour == 0)
	{	  
	  /*if (aleatoire() == 0)
	    {
	      fprintf(stdout, "Processus numero %d joue PIERRE \n",getpid());
	      exit(0);
	    }
	  if (aleatoire() == 1)
	    {
	      fprintf(stdout, "Processus numero %d joue CISEAUX \n",getpid());
	      exit(1);
	    }
	  
	  if (aleatoire() == 2)
	    {	    
	      fprintf(stdout, "Processus numero %d joue PAPIER \n",getpid());
	      exit(2);
	      }*/
	  execl("joueur", "joueur", NULL);
	}
    }
  
  // dans le pere
  sleep(2);
  
  int d1=0, d2=0, d3=0; // les points
  int arr[nb];  // contient les pid des processus
  int arr2[nb]; // contient les points des processus

  for (i=0;i<nb;i++){
     pid = wait(&status);
     arr[i] = pid;
     if ( WEXITSTATUS(status) == 0 )
       {
	 d3++;
	 arr2[i] = WEXITSTATUS(status);
       }
     if ( WEXITSTATUS(status) == 1 )
       {
	 d1++;
	 arr2[i] = WEXITSTATUS(status);
       }
     if ( WEXITSTATUS(status) == 2 )
       {
	 d2++;
	 arr2[i] = WEXITSTATUS(status);
       }
  }
  printf("Point Pierre %d \n", d1);
  printf("Point Cisaux %d \n", d2);
  printf("Point Papier %d \n", d3);
  
  for (i=0;i<nb;i++)
    {
      if ( arr2[i] == 0 )
	fprintf(stdout, "Processus : %d Point : %d \n", arr[i], d1);
      if ( arr2[i] == 1 )
	fprintf(stdout, "Processus : %d Point : %d \n", arr[i], d2);
      if ( arr2[i] == 2 )
	fprintf(stdout, "Processus : %d Point : %d \n", arr[i], d3);
    }
  
  exit(EXIT_SUCCESS);
}

