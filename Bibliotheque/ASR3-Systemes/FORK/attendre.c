/* attendre.c */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  int m, n;

  if(fork()==0)
    {  /* processus fils */
      printf("processus fils de numero : %d \n", getpid());
      exit(3);
    }
  else
    {
      m=wait(&n);
      printf("fin du processus fils %d avec valeur de retour %d \n", m, n); 
    }
exit(EXIT_SUCCESS);
}
