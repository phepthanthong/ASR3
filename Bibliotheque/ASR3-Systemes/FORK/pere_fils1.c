/*----------------------------------------------------------------
 annee II
                  Cours systeme d'exploitation

Exemple de synthese :  pere_fils1.c
-------------------
Questions:
      a)  Que fait ce programme?
      b)  Compiler et executer le programme.
      c)  Expliquer son fonctionnement.

-----------------------------------------------------------------*/
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int nb_recu;

void hand (int sig) 
{
  if (sig == SIGUSR1){
    signal(SIGUSR1, hand); 
    nb_recu++;
    printf("."); fflush(stdout);
  }
  else {
    printf("Nombre d'exemplaires recus : %d\n", nb_recu);
    exit(EXIT_SUCCESS);
  }
}

void initialise () 
{
  nb_recu=0;
}

int main ()
{
  signal(SIGUSR1, hand); 
  signal(SIGINT, hand); 
  initialise();
  printf("Patientez 10 secondes svp ...\n");
  if (fork() == 0) {
    int i;
    for (i=0; i<10 ; i++) { 
      kill(getppid(), SIGUSR1);
      sleep(1); 
    }
    printf("\nFin du fils \nVous pouvez taper Ctrl-C ...\n");
    exit(EXIT_SUCCESS);
  }
  while(1) pause();
}
