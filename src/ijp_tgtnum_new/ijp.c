#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include "test.h"

#define MAXHIS 4096
#define MAXTGT 512
#define MAXNUM 512
#define REPEAT 100

int mygen(unsigned int*dst,uint64_t pattern){
    for(uint64_t i=0; i<MAXHIS; i++){
        dst[i] = i%pattern;
    }
    return 0;
}


int main(){
    void (* a[MAXNUM])();
    void (* tgt[MAXTGT])();
    int b=0;
    ASSIGN

    struct timeval tv_begin, tv_end;
    unsigned int pattern[MAXHIS];
    int tgt_num[] = {2,4,8,12,16,24,32,48,64,96,128,192,256,384,512};

    for(int i=0;i<15;i++){ 
        mygen(pattern,tgt_num[i]);
        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT*4;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                a[0] = tgt[pattern[i]]; a[0]();
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*4));
    }
    printf("\n");

    for(int i=0;i<15;i++){ 
        mygen(pattern,tgt_num[i]);
        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT*4;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                TWO
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*4*2));
    }
    printf("\n");

    for(int i=0;i<15;i++){ 
        mygen(pattern,tgt_num[i]);
        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT*4;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                FOUR
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*4*4));
    }
    printf("\n");

    for(int i=0;i<15;i++){ 
        mygen(pattern,tgt_num[i]);
        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                EIGHT
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*8));
    }
    printf("\n");

    for(int i=0;i<15;i++){ 
        mygen(pattern,tgt_num[i]);
        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                SIXTEEN
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*16));
    }
    printf("\n");

    for(int i=0;i<15;i++){ 
        mygen(pattern,tgt_num[i]);
        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                THIRTYTWO
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*32));
    }
    printf("\n");

    for(int i=0;i<15;i++){ 
        mygen(pattern,tgt_num[i]);
        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                SIXTYFOUR
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*64));
    }
    printf("\n");

    for(int i=0;i<15;i++){ 
        mygen(pattern,tgt_num[i]);
        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                HUNDRED
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*128));
    }
    printf("\n");

    for(int i=0;i<15;i++){ 
        mygen(pattern,tgt_num[i]);
        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                THUNDRED
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*256));
    }
    printf("\n");

    for(int i=0;i<15;i++){ 
        mygen(pattern,tgt_num[i]);
        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                FHUNDRED
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*512));
    }
    printf("\n");

    return b;
}
