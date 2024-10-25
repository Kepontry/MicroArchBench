#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

static inline double second(){
    struct timespec _t;
    clock_gettime(CLOCK_REALTIME, &_t);
    return _t.tv_sec + _t.tv_nsec/1.0e9;
}

#define FIVE ONE ONE ONE ONE ONE
#define TEN FIVE FIVE
#define FIFTY TEN TEN TEN TEN TEN
#define HUNDRED FIFTY FIFTY
#define FHUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED
#define THOUSAND FHUNDRED FHUNDRED

#define FTHOUSAND THOUSAND THOUSAND THOUSAND THOUSAND THOUSAND
#define TENTHOUSAND FTHOUSAND FTHOUSAND

#ifndef __INNER_COUNT
#define __INNER_COUNT 30ULL
#endif

#ifndef __LOOP_COUNT
#define __LOOP_COUNT 100000ULL
#endif

#define DUMMY_SIZE 16384
uint8_t dummy[DUMMY_SIZE] __attribute__ ((aligned (16384)));

void __attribute__ ((noinline)) st2ld(size_t store_addr, size_t load_addr, uint64_t cnt){
// #define ONE "str w10, [%0]\r\n" "str w10, [%0, #4]\r\n" "ldr x10, [%1]\r\n"
// #define ONE "strh w10, [%0]\r\n" "ldr w10, [%1]\r\n"
// #define ONE "str w10, [%0]\r\n" "ldrh w10, [%1]\r\n"
// #define ONE "str q0, [%0]\r\n" "ldr d0, [%1]\r\n"
#define ONE "mov %%r8, (%0)\n\t" "mov (%1), %%r8d\n\t"

    asm volatile(
        "1: \n\t"
        TEN TEN TEN
        "dec %2 \n\t"
        "jne 1b \n\t"
        :
        : "r"(store_addr), "r"(load_addr), "r"(cnt)
        :"r8", "r9", "memory");
}

void st2ld_test(string res_dir) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/ldstforward.res";
    ofstream output_file;
    if(res_dir.length() > 0){
        has_output_dir = true;
    }
    // cout << output_dir << endl;


    if(has_output_dir) output_file.open(output_dir);

    st2ld((size_t)dummy, (size_t)dummy, 10000);
    for (size_t i = 0; i < 64; i++)
    {
        for (size_t j = 0; j < 64; j++)
        {
            double begin = second();
            st2ld((size_t)dummy + i, (size_t)dummy + j, __LOOP_COUNT);
            double end = second();

            if(has_output_dir){
                output_file << (end - begin) / (__LOOP_COUNT * __INNER_COUNT) * 1000000000 << ",";
            }else{
                printf("%.3lf,", (end - begin) / (__LOOP_COUNT * __INNER_COUNT) * 1000000000);
            }
        }
        if(has_output_dir){
            output_file << "\n";
        }else{
            printf("\n");
        }
    }

    if(has_output_dir) output_file.close();

}

int main(int argc, char* argv[]) {
    printf("\n>>>>> Running Store-to-load Forward Test\n");
    if ((size_t)dummy % 4096) {
        fprintf(stderr, "dummp align error\n");
        abort();
    }

    st2ld_test(argv[1]);

    return 0;
}
