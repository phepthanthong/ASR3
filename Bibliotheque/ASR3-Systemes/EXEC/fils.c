/*-----------------------------------------------------------------
   Gestion des processus
------------------------------
texte de fils.c
      code C de l'executable fils  
-----------------------------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int i;
  
  fprintf(stdout,"debut du processus de numero %d \n",getpid());
  for (i=1;i<6;i++)
    {
      sleep(1);
      fprintf(stdout,"le process de numero %d s'execute\n",getpid());
    }
  fprintf(stdout,"fin du processus de numero : %d \n",getpid());
  
  exit (0);
}     

