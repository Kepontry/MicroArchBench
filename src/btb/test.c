// #define _GNU_SOURCE 
// #include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>

#include "test.h"

struct timeval tv_begin, tv_end;

int main()
{
    // cpu_set_t set;
    // // CPU_ZERO(&set);
    // CPU_SET(0, &set);
    // sched_setaffinity(getpid(), sizeof(set), &set);

    // #pragma optimize level = 0
    gettimeofday(&tv_begin, NULL);
    for (unsigned long long j=0; j< REPEAT; j++){
        TEST_LOOP
    }
    // test(REPEAT);
    gettimeofday(&tv_end, NULL);

    long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
    printf("%f\t",(timeSpan*1000.0)/(REPEAT));
    // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    printf("\n");

    return 0;
}
