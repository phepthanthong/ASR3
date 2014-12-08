/*----------------------------------------------------------------
 annee II
                  Cours systeme d'exploitation

   Gestion des processus
------------------------------
Questions:
      a)  Que fait ce programme?
      b)  Compiler et executer.

attention : ce programme utilise le fichier executable de nom : fils
que vous devez avoir dans votre repertoire courant.
Cet executable est obtenu par compilation du texte fils.c
      
-----------------------------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int a,i;
  
  fprintf(stdout,"debut du processus de numero %d \n",getpid());
  
  /* creation d'un second processus */
  
  a = fork();
  if (!a) {
    /* cette partie de programme 
       ne s'execute que pour le processus cree (processus fils)*/
    
    execl( "fils","fils",0);
    fprintf(stderr,"pb execl ");
    exit (3);
  }
  fprintf(stdout,"je suis papa de %d\n",a);
  
  /* pour passer le temps, les enfants grandissent */
  for (i=0;i < 10; i++)
    {
      fprintf(stdout,"le process de numero %d continue\n",getpid());
      sleep(1);
    }
  /* le reste */
  
  sleep(2);
  fprintf(stdout,"fin du processus de numero : %d \n",getpid());
  
  exit (0);
}     

