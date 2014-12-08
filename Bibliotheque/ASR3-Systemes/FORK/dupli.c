/* dupli.c */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int n;
  if((n=fork())==0)
    { /* processus fils */
      printf("pid processus fils %d \n", getpid());
      exit(EXIT_SUCCESS);
    }
  else
    { /* processus pere */
      /* system("ps -l"); */
      sleep(5);
      printf("pid processus pere %d \n", getpid());      
      printf("mon fils porte le numero %d \n", n);      
    }
exit(EXIT_SUCCESS);
}
