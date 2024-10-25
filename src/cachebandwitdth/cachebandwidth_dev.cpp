#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

using namespace std;

#define ONE tmp = foo[base];\
            tmp = foo[base + 8];\
            tmp = foo[base + 16];\
            tmp = foo[base + 32];\
            tmp = foo[base + 40];\
            tmp = foo[base + 48];\
            tmp = foo[base + 56];\
            tmp = foo[base + 64];\
            base = (base+8) % cur_num;
#define FIVE ONE ONE ONE ONE ONE
#define TEN FIVE FIVE
#define FIFTY TEN TEN TEN TEN TEN
#define HUNDRED FIFTY FIFTY

int stride_add(int cur){
    int next = 0;
    int tmp = (int)log2(cur);
    // printf("tmp: %d %d",cur,tmp);
    next = pow(2,tmp) / 4;
    // printf("nxt: %d",next);
    if(next < 2) return cur + 2;
    return cur + (int)next;
}

int main(){

    cout << "\n>>>>> Running Cache Bandwidth Test" << endl;

    uint64_t *foo;
    uint64_t repeat = 50,tmp;
    uint64_t cur_size = 4 * 1024;
    uint64_t max_size = 128 * 1024 * 1024; // 128 MB
    uint64_t cur_num = cur_size / 8 - 64; // 128 MB

    struct timeval tv_begin, tv_end;

    while(cur_size <= max_size){
        foo = (uint64_t *)malloc(cur_size);
        uint64_t traverse = repeat * cur_size / 64 / 10;
        register uint64_t base = 0;

        gettimeofday(&tv_begin, NULL);
        for (uint64_t j=0; j< traverse; j++){
            TEN
        }
        gettimeofday(&tv_end, NULL);

        double timeSpan = (tv_end.tv_sec - tv_begin.tv_sec)* 1000000 + (tv_end.tv_usec-tv_begin.tv_usec);
        printf("%f\n",8*traverse/(timeSpan*1000.0));

        free(foo);
        cur_size = stride_add(cur_size);
    }











    return tmp;
}