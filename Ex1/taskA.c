#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

// real: wall clock time
// user: amount of cpu time spent in user mode within the process
// sys: amount of cpu time spent in the kernel within the process

struct timespec timespec_normalized(time_t sec, long nsec){ 
    while(nsec >= 1000000000){ 
        nsec -= 1000000000; 
        ++sec; 
    } 
    while(nsec < 0){ 
        nsec += 1000000000; 
        --sec; 
    } 
    return (struct timespec){sec, nsec}; 
}

struct timespec timespec_sub(struct timespec lhs, struct timespec rhs){ 
    return timespec_normalized(lhs.tv_sec - rhs.tv_sec, lhs.tv_nsec - rhs.tv_nsec); 
} 

struct timespec timespec_add(struct timespec lhs, struct timespec rhs){ 
    return timespec_normalized(lhs.tv_sec + rhs.tv_sec, lhs.tv_nsec + rhs.tv_nsec); 
}
 
int timespec_cmp(struct timespec lhs, struct timespec rhs){ 
    if (lhs.tv_sec < rhs.tv_sec) 
        return -1; 
    if (lhs.tv_sec > rhs.tv_sec) 
        return 1; 
    return lhs.tv_nsec - rhs.tv_nsec; 
}

void busy_wait(struct timespec t){ 
    struct timespec now; 
    clock_gettime(CLOCK_MONOTONIC, &now); 
    
    struct timespec then = timespec_add(now, t); 
    while(timespec_cmp(now, then) < 0){ 
        //for(int i = 0; i < 10000; i++){} 
        clock_gettime(CLOCK_MONOTONIC, &now); 
    } 
} 

static struct tms en_cpu;

void times_wait()
{
    times(&en_cpu);
    
    while(en_cpu.tms_utime+en_cpu.tms_stime < 100)
    {
        times(&en_cpu);
    }

}

int main()
{
    // DEL EN
    sleep(1);
    
    // DEL TO
    struct timespec t;
    
    t.tv_sec = 1;
    t.tv_nsec = 0;
    
    busy_wait(t);
    
    
    // DEL TRE
    times_wait();
    
    
    return 0;
}





