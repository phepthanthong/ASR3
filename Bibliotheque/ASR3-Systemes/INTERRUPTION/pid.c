#include<stdio.h>

#include<unistd.h>

#include<stdlib.h>

int main() {
	
	printf("Je suis le processus numero : %d \n", getpid());
	
	printf("Le pid de mon pere est  : %d \n", getppid());
	
	system("ps -l");
	
	exit(0);
	
}
