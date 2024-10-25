// #define _GNU_SOURCE 
// #include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>

#include "test.h"

#define REPEAT 1000000LL

struct timeval tv_begin, tv_end;

int main(int argc, char* argv[])
{
	// char target[] = {"/log/ras.res"};
	// printf("%s",strcat(argv[1],target));
	char source[100];
    double freq = strtod(argv[2],NULL);
    // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
	// strcpy(source,argv[1]);
	// FILE *target_file;
	// target_file = fopen(strcat(argv[1],target),"w");

    // cpu_set_t set;
    // // CPU_ZERO(&set);
    // CPU_SET(0, &set);
    // sched_setaffinity(getpid(), sizeof(set), &set);

    // #pragma optimize level = 0
    gettimeofday(&tv_begin, NULL);
    for (int j=0; j< REPEAT; j++){
        a += foo_func(a);
    }
    gettimeofday(&tv_end, NULL);

    long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
    printf("%f\n",(timeSpan*1000.0)/(REPEAT));

    // fclose(target_file);

    return a;
}
