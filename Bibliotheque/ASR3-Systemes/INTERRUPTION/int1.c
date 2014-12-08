/*----------------------------------------------------------------
 annee II
                  Cours systeme d'exploitation

Illustration des interruptions
------------------------------
Questions:
      a)  Que fait ce programme?
      b)  Compiler et executer le programme.
      
-----------------------------------------------------------------*/
#include <unistd.h> 
#include <signal.h>
#include <stdio.h>
void interruption (), arret ();

int cmpt = 1;

int main ()
{

  	signal(SIGINT, interruption);  /*  recuperation de ^C  */
  	signal(SIGQUIT, arret);        /*  recuperation de ^\  */
  	signal(SIGTSTP, SIG_IGN);      /*  on ignore ^z        */

	for (;;) {
		printf("%d", cmpt); fflush(stdout);
		sleep(1);
	}
}

void arret () {

	write (1,"\n",1);
        write (1,"Au revoir\n",10);
	signal(SIGQUIT, SIG_DFL);
        _exit(0);
}

void interruption () {

	signal(SIGINT, interruption);	
	cmpt++;
}
