#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

long q = 0;

sem_t mutex;

// Note the argument and return types: void*
void* fn(void* args){

	long ql = 0;

	
	for (int i=0; i<50*1000*1000; ++i)
	{
		//sem_wait(&mutex);
		q++;
		//sem_post(&mutex);
		ql++;
	}

	//sem_wait(&mutex);
	printf("Global: \t%ld\nLocal: \t\t%ld\n", q, ql);
	//sem_post(&mutex);

    return NULL;
}

int main(){

    pthread_t t1, t2;
    //sem_init(&mutex,0,1);

    pthread_create(&t1, NULL, fn, NULL);    
    pthread_create(&t2, NULL, fn, NULL);  

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    //sem_destroy(&mutex);

}