#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string>
#include <fstream>

#define FIVE ONE ONE ONE ONE ONE
#define TEN FIVE FIVE
#define FIFTY TEN TEN TEN TEN TEN
#define HUNDRED FIFTY FIFTY
#define FHUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED
#define THOUSAND FHUNDRED FHUNDRED

#define FTHOUSAND THOUSAND THOUSAND THOUSAND THOUSAND THOUSAND
#define TENTHOUSAND FTHOUSAND FTHOUSAND

#ifndef __INNER_COUNT
#define __INNER_COUNT 100ULL
#endif

#ifndef __LOOP_COUNT
#define __LOOP_COUNT 200000000ULL
#endif

using namespace std;

static inline double second(){
    struct timespec _t;
    clock_gettime(CLOCK_REALTIME, &_t);
    return _t.tv_sec + _t.tv_nsec/1.0e9;
}

void __attribute__ ((noinline)) brwidth(uint64_t cnt){
#undef ONE
#define ONE "jz 1b\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        "add $1, %%r9\r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r9", "memory");
}

void brwidth_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    brwidth(10000);
    double begin = second();
    brwidth(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("BRU width: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "BRU width: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

int main(int argc, char* argv[]) {
    brwidth_test(argv[1],atof(argv[2]));
    return 0;
}
