#include <stdio.h>
#include <unistd.h>

/* exemple de programme qui realise :
      ll | wc -l
en utilisant : pipe
               fork
               dup
               execl
---------------------------*/

main()
{
int fd[2];

/* ouverture pipe */
if (pipe(fd) != 0) {
       fprintf(stderr, "Pb ouverture pipe");
       _exit(1);
                   }

/* creation de deux processus */

if (fork()) {
     /* processus pere : il est charge d'executer ll */

           close (1);
          dup(fd[1]);
          close(fd[1]);
          close(fd[0]);
          execl( "/bin/ls","ll","-l",0);
          fprintf(stderr,"pb execl ll\n");
          _exit (2);
           }
else       {
    /* processus fils charge d'executer wc */
          close(0);
          dup(fd[0]);
          close(fd[1]);
          close(fd[0]);
          execl( "/usr/bin/wc","wc","-l",0);
          fprintf(stderr,"pb execl wc\n");
          _exit (3);
           }
}     

