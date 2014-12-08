#include <stdio.h>
#include <unistd.h>

int p[2];
main()
{
int i,s;

if (pipe(p) != 0) {
     fprintf(stderr,"pb ouverture pipe \n");
     _exit(1);
     }
if (fork()==0) {
         fils1();
               }
if (fork()==0) {
         fils2();
               }
close(p[0]);
close(p[1]);
fprintf(stderr,"debut attente \n");
i=wait(&s);
i=wait(&s);
printf("fin du programme\n");
}
fils1()
{
char c;
int i;

close(p[0]);
fprintf(stderr,"debut fils1 ( taper 0 pour fin ... )\n");
while ((read(0,&c,1) > 0 ) && ( c != '0' )  )
       if ( (( c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'))) {
             if ((c >= 'a') && ( c <= 'z')) {
                        i= c;
                        i-=32;
                        c=i;
                      }
            
             write(p[1],&c,1);
             printf("fils1 %c\n",c);
                 }
close(p[1]);
fprintf(stderr,"fin fils1 \n");
_exit(0);
}
fils2()
{
char c;

close (p[1]);
fprintf(stderr,"debut fils2 \n");
while (read(p[0],&c,1) > 0) 
        printf("fils2 :%c\n",c);
close(p[0]);      
fprintf(stderr,"fin fils2\n");
_exit(0);
       
}

