#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 256
char tube[MAX];

void* producteur(void* arg) 
{
	printf("producteur\n");
	int i=0;
	char c='a';
	for(i=0;i<MAX;i++) 
	{
		tube[i]=c;
		c++;
		if(c>'z')
			c='a';
		sleep(1);
	}
	return NULL;
}

void* consommateur(void* arg)
{
	printf("consommateur\n");
	char c;
	int i;
	for(i=0;i<MAX; i++)
	{
		while(tube[i] == 0);
		printf("conso : lu : %c\n", tube[i]);
		tube[i]=0;
	}

	return NULL;
}

int main(int argc, char** argv) 
{
	pthread_t prod, cons;
	memset(tube, 0, MAX);
	

	pthread_create(&prod, NULL, producteur, NULL);

	pthread_create(&cons, NULL, consommateur, NULL);
	pthread_join(prod, NULL);
	pthread_join(cons, NULL);

	return 0;
}
