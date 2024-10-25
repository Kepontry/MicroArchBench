// #define _GNU_SOURCE 
// #include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>

#define REPEAT 1000000LL

struct timeval tv_begin, tv_end;

void call(int num){
    if(num > 0){
        call(num -1);
    }
}

int main(int argc, char* argv[])
{
    printf("\n>>>>> Running RAS Test\n");

	char target[] = {"/log/ras.res"};
	// printf("%s",strcat(argv[1],target));
	char source[100];
    double freq = strtod(argv[2],NULL);
	strcpy(source,argv[1]);
	FILE *target_file;
	target_file = fopen(strcat(argv[1],target),"w");

    // cpu_set_t set;
    // // CPU_ZERO(&set);
    // CPU_SET(0, &set);
    // sched_setaffinity(getpid(), sizeof(set), &set);

    // #pragma optimize level = 0
    for(int i=0; i<200; i++){
        gettimeofday(&tv_begin, NULL);
        for (int j=0; j< REPEAT; j++){
            call(i);
        }
        gettimeofday(&tv_end, NULL);

        long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        fprintf(target_file,"%f\n",(timeSpan*1000.0)/(REPEAT)/(i+1)*freq);
        // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    }

    fclose(target_file);

    return 0;
}
