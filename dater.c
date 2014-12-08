#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void main()
{
  printf("La date est :");
  //fflush(stdout);
  system("/bin/date");
}
