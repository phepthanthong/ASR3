#include <stdlib.h>
#include <stdio.h>


#include <sys/types.h>
       #include <sys/wait.h>


int main ()
{
  if (fork()==0) {
    // le fils dort 10 secondes puis termine
    printf("Le fils (pid %d) dort... ", getpid()); fflush(stdout);
    sleep(10);
    printf("et termine...\n"); fflush(stdout);
    exit(0);
  } else {
    // le pere boucle...
    wait(0);
    while (1) pause();
  }
}
