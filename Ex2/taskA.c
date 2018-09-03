#include <pthread.h>
#include <stdio.h>
long q = 0;
// Note the argument and return types: void*
void* fn(void* args){

	long ql = 0;

	for (int i=0; i<50*1000*1000; ++i)
	{
		q++;
		ql++;
	}

	printf("Global: \t%ld\nLocal: \t\t%ld\n", q, ql);

    return NULL;
}

int main(){

    pthread_t t1, t2;

    pthread_create(&t1, NULL, fn, NULL);    
    pthread_create(&t2, NULL, fn, NULL);  

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

}