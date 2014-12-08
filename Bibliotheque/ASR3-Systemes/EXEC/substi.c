#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

main(){

  close(STDOUT_FILENO);
  open("toto",O_RDWR|O_CREAT|O_APPEND);
  execl("/bin/ls", ".", "-l", 0);
  printf("test execl, ça fonctionne !");
  fprintf(STDERR_FILENO,"ERREUR EXEC \n");

}
