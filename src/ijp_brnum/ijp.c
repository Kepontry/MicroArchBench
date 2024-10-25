#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include "test.h"

#define MAXHIS 65536
#define MAXBP 512
#define REPEAT 100

void foo_func0(){
    ;
}

void foo_func1(){
    ;
}

int mycopy(unsigned int*src,unsigned int*dst,uint64_t pattern){
    for(uint64_t i=0; i<MAXHIS; i++){
        dst[i] = src[i%pattern];
    }
    return 0;
}


int main(){
    void (* a[MAXBP])();

    unsigned int pattern_raw[MAXHIS];
    for(int i=0;i<MAXHIS;i++){
        pattern_raw[i] = rand()%2;
    }

    struct timeval tv_begin, tv_end;
    unsigned int pattern[MAXHIS];
    int pattern_len[] = {1,2,4,8,12,16,24,32,48,64,96,128,192,256,512,600,768,1024,1536,2048,3072,4096,5120,6144,8192,10240,12288,16384,24567,32768,65536};
    int br_num[] = {1,2,4,8,16,32,64,128,256,512};

    for(uint64_t cur_len=1;cur_len<31;cur_len++){
        mycopy(pattern_raw,pattern,pattern_len[cur_len]);

        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT*4;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                if(pattern[i]) a[0] = foo_func0;
                else           a[0] = foo_func1;
                    // asm volatile(
                    // "nop \r\n"
                    // "nop \r\n"
                    // "nop \r\n"
                    // "nop \r\n"
                    // "nop \r\n"
                    // "nop \r\n"
                    // "nop \r\n"
                    // "nop \r\n"
                    // :
                    // :
                    // :);
                a[0]();
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*4));
    }
    printf("\n");

    for(uint64_t cur_len=1;cur_len<31;cur_len++){
        mycopy(pattern_raw,pattern,pattern_len[cur_len]);

        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT*4;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                TWO
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*2*4));
    }
    printf("\n");

    for(uint64_t cur_len=1;cur_len<31;cur_len++){
        mycopy(pattern_raw,pattern,pattern_len[cur_len]);

        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                FOUR
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT*4));
    }
    printf("\n");


    for(uint64_t cur_len=1;cur_len<31;cur_len++){
        mycopy(pattern_raw,pattern,pattern_len[cur_len]);

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


    for(uint64_t cur_len=1;cur_len<31;cur_len++){
        mycopy(pattern_raw,pattern,pattern_len[cur_len]);

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

    for(uint64_t cur_len=1;cur_len<31;cur_len++){
        mycopy(pattern_raw,pattern,pattern_len[cur_len]);

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

    for(uint64_t cur_len=1;cur_len<31;cur_len++){
        mycopy(pattern_raw,pattern,pattern_len[cur_len]);

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

    for(uint64_t cur_len=1;cur_len<31;cur_len++){
        mycopy(pattern_raw,pattern,pattern_len[cur_len]);

        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT/2;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                HUNDRED
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT/2*128));
    }
    printf("\n");

    for(uint64_t cur_len=1;cur_len<31;cur_len++){
        mycopy(pattern_raw,pattern,pattern_len[cur_len]);

        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT/2;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                THUNDRED
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT/2*256));
    }
    printf("\n");

    for(uint64_t cur_len=1;cur_len<31;cur_len++){
        mycopy(pattern_raw,pattern,pattern_len[cur_len]);

        gettimeofday(&tv_begin, NULL);
        for(uint64_t j=0;j<REPEAT/2;j++){
            for(uint64_t i=0; i<MAXHIS;i++){
                FHUNDRED
            }
        }
        gettimeofday(&tv_end, NULL);
        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f,",(timeSpan*1000.0)/(MAXHIS*REPEAT/2*512LL));
    }
    printf("\n");

    return 0;
}
