#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>

#include "Buffer.h"

using namespace std;

void * producer(void * b)
{
	Buffer * pB = (Buffer *)b;
	int i = 0;
	while (true)
	{
		sleep(rand()%1+1);
		if (pB->produce(i) == i)
		{	
			printf("Produced %d\n",i);
			i++;
		}
	}
}

void * consumer(void * b)
{
	Buffer * pB = (Buffer *)b;
	while (true)
	{
		sleep(rand()%1+1);
		int c = pB->consume();
		if (c > -1)
			printf("Consumed %d\n",c);
	}
}

int main()
{
	srand(time(NULL));

	pthread_t tid;
	pthread_attr_t attr;
    pthread_attr_init(&attr);
    Buffer buffer;

    pthread_create(&tid, &attr, producer, &buffer); 
    pthread_create(&tid, &attr, producer, &buffer);
    pthread_create(&tid, &attr, producer, &buffer);
    pthread_create(&tid, &attr, producer, &buffer);
    pthread_create(&tid, &attr, consumer, &buffer); 
    pthread_create(&tid, &attr, consumer, &buffer); 

	while (true)
	{}
}



