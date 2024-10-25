#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>


#include "test.h"

#define N 100000LL
#define MAXHIS 65536

struct timeval tv_begin, tv_end;

int mycopy(unsigned int*src,unsigned int*dst,int pattern){
    for(int i=0; i<MAXHIS*2; i++){
        dst[i] = src[i%pattern];
    }
    return 0;
}

int main()
{
    // unsigned int *a = (unsigned int *) malloc(MAXHIS*4*2);
    unsigned int a[MAXHIS*2];
    unsigned int c[MAXHIS*2];
    for(int i=0;i<MAXHIS*2;i++){
        a[i] = rand()%2;
    }
    if(a == NULL){
        printf("fail!\n");
    }

    unsigned long long repeat = N;

    #pragma optimize level = 0
    int pattern[] = {1,2,4,8,12,16,24,32,48,64,96,128,192,256,512,600,768,1024,1536,2048,3072,4096,5120,6144,8192,10240,12288,16384,24567,32768,65536};
    for(int cur_len=1;cur_len<31;cur_len++){
        mycopy(a,c,pattern[cur_len]);
        repeat = N;
        gettimeofday(&tv_begin, NULL);
        ONE
        gettimeofday(&tv_end, NULL);

        long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f\t",(timeSpan*1000.0)/(N*(1L+1L)));
        // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    }
    printf("\n");

    for(int cur_len=1;cur_len<31;cur_len++){
        mycopy(a,c,pattern[cur_len]);
        repeat = N;
        gettimeofday(&tv_begin, NULL);
        TWO
        gettimeofday(&tv_end, NULL);

        long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f\t",(timeSpan*1000.0)/(N*(2L+1L)));
        // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    }
    printf("\n");

    for(int cur_len=1;cur_len<31;cur_len++){
        mycopy(a,c,pattern[cur_len]);
        repeat = N;
        gettimeofday(&tv_begin, NULL);
        FOUR
        gettimeofday(&tv_end, NULL);

        long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f\t",(timeSpan*1000.0)/(N*(4L+1L)));
        // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    }
    printf("\n");

    for(int cur_len=1;cur_len<31;cur_len++){
        mycopy(a,c,pattern[cur_len]);
        repeat = N;
        gettimeofday(&tv_begin, NULL);
        EIGHT
        gettimeofday(&tv_end, NULL);

        long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f\t",(timeSpan*1000.0)/(N*(8L+1L)));
        // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    }
    printf("\n");

    for(int cur_len=1;cur_len<31;cur_len++){
        mycopy(a,c,pattern[cur_len]);
        repeat = N;
        gettimeofday(&tv_begin, NULL);
        SIXTEEN
        gettimeofday(&tv_end, NULL);

        long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f\t",(timeSpan*1000.0)/(N*(16L+1L)));
        // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    }
    printf("\n");

    for(int cur_len=1;cur_len<31;cur_len++){
        mycopy(a,c,pattern[cur_len]);
        repeat = N;
        gettimeofday(&tv_begin, NULL);
        THIRTYTWO
        gettimeofday(&tv_end, NULL);

        long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f\t",(timeSpan*1000.0)/(N*(32L+1L)));
        // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    }
    printf("\n");

    for(int cur_len=1;cur_len<31;cur_len++){
        mycopy(a,c,pattern[cur_len]);
        repeat = N;
        gettimeofday(&tv_begin, NULL);
        SIXTYFOUR
        gettimeofday(&tv_end, NULL);

        long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f\t",(timeSpan*1000.0)/(N*(64L+1L)));
        // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    }
    printf("\n");

    for(int cur_len=1;cur_len<31;cur_len++){
        mycopy(a,c,pattern[cur_len]);
        repeat = N;
        gettimeofday(&tv_begin, NULL);
        HUNDRED
        gettimeofday(&tv_end, NULL);

        long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f\t",(timeSpan*1000.0)/(N*(128L+1L)));
        // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    }
    printf("\n");

    for(int cur_len=1;cur_len<31;cur_len++){
        mycopy(a,c,pattern[cur_len]);
        repeat = N;
        gettimeofday(&tv_begin, NULL);
        TWOHUNDRED
        gettimeofday(&tv_end, NULL);

        long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f\t",(timeSpan*1000.0)/(N*(256L+1L)));
        // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    }
    printf("\n");

    for(int cur_len=1;cur_len<31;cur_len++){
        mycopy(a,c,pattern[cur_len]);
        repeat = N;
        gettimeofday(&tv_begin, NULL);
        FIVEHUNDRED
        gettimeofday(&tv_end, NULL);

        long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f\t",(timeSpan*1000.0)/(N*(512L+1L)));
        // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    }
    printf("\n");

    for(int cur_len=1;cur_len<31;cur_len++){
        mycopy(a,c,pattern[cur_len]);
        repeat = N;
        gettimeofday(&tv_begin, NULL);
        TENHUNDRED
        gettimeofday(&tv_end, NULL);

        long long timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f\t",(timeSpan*1000.0)/(N*(1024L+1L)));
        // printf("pattern len: %d \t latency: %fns\n",pattern[cur_len],(timeSpan*1000.0)/(N*512L));
    }
    printf("\n");

    return 0;
}
