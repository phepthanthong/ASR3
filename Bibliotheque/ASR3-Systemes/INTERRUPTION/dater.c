#include <stdio.h>
#include <stdlib.h>

void main() {

  printf("La date est : "); 

  fflush(stdout); // pour vider le buffer ...

  system("/bin/date +%D");

  exit(0);
}
