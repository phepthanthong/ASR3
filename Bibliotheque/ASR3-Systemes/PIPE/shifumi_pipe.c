/* shifumi.c */
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

//int p[nb][2];

int main(int argc, char *argv[])
{
  int i;      // compteur
  int retour; // retour fork
  pid_t pid;  // pid
  int status; // valeur de retour fils termine

  int nb = atoi(argv[1]);  
  int p[nb][2];
  int alea = aleatoire();
  int ppc[3] = {1,2,3};

  for (i=0; i<nb; i++){
    if (pipe(p[i]) != 0) {
      fprintf(stderr,"pb ouverture pipe \n");
      _exit(1);
    }
  }

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
	  
	  close(p[i][0]);
	  
	  if (aleatoire() == 0)
	    {
	      fprintf(stdout, "Processus numero %d joue PIERRE \n",getpid());
	      write(p[i][1],&ppc[0],1);
	      //exit(0);
	    }
	  if (aleatoire() == 1)
	    {
	      fprintf(stdout, "Processus numero %d joue CISEAUX \n",getpid());
	      write(p[i][1],&ppc[1],1);
	      //exit(1);
	    }
	  
	  if (aleatoire() == 2)
	    {	    
	      fprintf(stdout, "Processus numero %d joue PAPIER \n",getpid());
	      write(p[i][1],&ppc[2],1);
	      //exit(2);
	    }
	  close(p[i][1]);
	  exit(i);
	}
      /*if (retour == 0)
	{
	int x;
	close(p[i][1]);
	read(p[i][0],&x,sizeof(int));
	close(p[i][0]);
	  }*/
    }
  
  // dans le pere
  sleep(2);
  
  int a;
  int d1=0, d2=0, d3=0; // les points
  int arr[nb];  // contient les pid des processus
  int arr2[nb]; // contient les points des processus
  
  for (i=0;i<nb;i++){
    pid = wait(&status);
    arr[i] = pid;
    close(p[status/256][1]);
    read((int)p[status/256][0],&a,1);
    arr2[i]=a;

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

