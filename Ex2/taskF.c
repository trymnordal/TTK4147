#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t forks[5];
pthread_mutex_t waiter;
pthread_t phils[5];

int phil[5] = {0,1,2,3,4};

void* eat(void* args){

	int *args_int = args;

	printf("%d\n", *args_int);

	while(1)
	{

		pthread_mutex_lock(&waiter);

		pthread_mutex_lock(&forks[*args_int]);
		if (*args_int<4)
			pthread_mutex_lock(&forks[*args_int+1]);
		else
			pthread_mutex_lock(&forks[0]);

		printf("%d: Eat\n", *args_int);
		usleep(1000);

		

		pthread_mutex_unlock(&forks[*args_int]);
		if (*args_int<4)
			pthread_mutex_unlock(&forks[*args_int+1]);
		else
			pthread_mutex_unlock(&forks[0]);

		pthread_mutex_unlock(&waiter);

		printf("%d: Think\n", *args_int);
		usleep(1000);
	}

    return NULL;
}


int main(){

    int numPhils = sizeof(phils)/sizeof(*phils);
    int numForks = sizeof(forks)/sizeof(*forks);

    pthread_mutex_init(&waiter,NULL);

    for( int i=0; i<numForks; ++i)
    {
    	pthread_mutex_init(&forks[i], NULL);
    }

    for( int i=0; i<numPhils; i++)
    {
    	pthread_create(&phils[i], NULL, eat, &phil[i]);
    }

    for( int i=0; i<numPhils; ++i)
    {
    	pthread_join(phils[i], NULL);
    }

    for( int i=0; i<numForks; ++i)
    {
    	pthread_mutex_destroy(&forks[i]);
    }

    return 0;


/*
    // 2nd arg is a pthread_mutexattr_t
    pthread_mutex_init(&mtx, NULL);



    pthread_mutex_lock(&mtx);
    // Critical section
    pthread_mutex_unlock(&mtx);

    pthread_mutex_destroy(&mtx);*/
}