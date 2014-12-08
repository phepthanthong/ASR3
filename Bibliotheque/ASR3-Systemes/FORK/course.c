/* course.c
Course entre cinq processus fils :
Ce programme lance cinq processus fils pendant une dur�e donn�e et
affiche l'ordre de d�part, d'arriv�e et le num�ro
du processus concern�.                     */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define NB      5        // nombre de concurrents
#define ARRIVEE 10000000   // distance a parcourir

int main()
{
  int i;                 // compteur concurrents
  int r;                 // retour fork
  pid_t pid;             // pid
  int status;            // valeur de retour fils termine

  for(i=1; i<=NB; i++)
    {
      if ((r = fork()) < 0)
	{
	  // traitement erreur fork()
	  fprintf(stderr,"Erreur fatale : fork()\n");
	  exit(EXIT_FAILURE);
	}
      if (r == 0)
	{
	  // un fils : il court....
	  int j;
	  for (j=0; j<ARRIVEE; j++);
	  exit(i);
	}
      // dans le p�re
      // poursuite de la boucle for
    }
  
  // p�re
  for (i=1; i<=NB; i++)
    {
      pid = wait(&status);
      fprintf (stdout, "le processus %d parti numero %d est arrive numero %d\n",
	       pid, WEXITSTATUS(status), i);
      // status/256 --> WEXITSTATUS(status)
    }
  exit(EXIT_SUCCESS);
}

