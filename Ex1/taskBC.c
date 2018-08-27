#include <x86intrin.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sched.h>
#include <sys/times.h>



int main()
{

    
    unsigned int i, t1, t2;
    /*
    for(i = 0; i < 10*1000*1000; i++){
        __rdtsc();
    } // 8.7 nanosec
    */
    
    /*
    struct timespec now; 
    for(i = 0; i < 10*1000*1000; i++){
        clock_gettime(CLOCK_MONOTONIC, &now);
    } // 21.9 nanosec
    */
    
    /*
    struct tms en_cpu;
    for(i = 0; i < 10*1000*1000; i++){
        times(&en_cpu);
    } // 258.3 nanosec
    */
    

    
    int ns_max = 500;
    int histogram[ns_max];
    memset(histogram, 0, sizeof(int)*ns_max);
    
    struct timespec now1;
    struct timespec now2;
    struct tms cpu1;
    struct tms cpu2;

    for(int i = 0; i < 10*1000*1000; i++){
        
        /*
        t1 = __rdtsc();
        t2 = __rdtsc();
        int ns = (t2 - t1) * (1./2.66);
        */
        
        
        clock_gettime(CLOCK_MONOTONIC, &now1);
        sched_yield();
        clock_gettime(CLOCK_MONOTONIC, &now2);
        int ns = (now2.tv_nsec - now1.tv_nsec);
        
        
        /*
        times(&cpu1);
        times(&cpu2);
        int ns = (cpu2.tms_stime - cpu1.tms_stime) / 10000000;
        */
        
        
        if(ns >= 0 && ns < ns_max){
            histogram[ns]++;
        }
    }

    for(int i = 0; i < ns_max; i++){
        printf("%d\n", histogram[i]);
    }

}

