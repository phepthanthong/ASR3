/*----------------------------------------------------------------
 annee II
                  Cours systeme d'exploitation

Illustration des interruptions    (exemple 2)
------------------------------
Questions:
      a)  Que fait ce programme?
      b)  Compiler et executer le programme.
      
-----------------------------------------------------------------*/
#include <unistd.h> 
#include <signal.h>
#include <stdio.h>
#define DELAI 1

void initialise(), calcule(), sauve(), onalrm();

unsigned long i;

int main ()
{

        initialise();
	signal(SIGALRM, onalrm); 
        alarm(DELAI); 
        calcule();
        fprintf(stdout,"calcul termine\n");
        _exit(0); 

}

void onalrm () 
{
        sauve(); 
        signal(SIGALRM,onalrm);
        alarm(DELAI);
}

void initialise () 
{
        i=0;
}
void sauve()
{
        fprintf(stderr,"sauvegarde de i :%lu\n",i);
}
void calcule()
{
          while (i+= 4);
}
