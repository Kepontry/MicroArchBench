#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string>
#include <fstream>

using namespace std;

static inline double second(){
    struct timespec _t;
    clock_gettime(CLOCK_REALTIME, &_t);
    return _t.tv_sec + _t.tv_nsec/1.0e9;
}

#define FIVE ONE ONE ONE ONE ONE
#define TEN FIVE FIVE
#define FIFITY TEN TEN TEN TEN TEN
#define HUNDRED FIFITY FIFITY
#define FHUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED
#define THOUSAND FHUNDRED FHUNDRED

#define FTHOUSAND THOUSAND THOUSAND THOUSAND THOUSAND THOUSAND
#define TENTHOUSAND FTHOUSAND FTHOUSAND

#ifndef __INNER_COUNT
#define __INNER_COUNT 30ULL
#endif

#ifndef __LOOP_COUNT
#define __LOOP_COUNT 500000000ULL
#endif

void __attribute__ ((noinline)) freq(uint64_t cnt){
#define ONE "add x10, x10, #1\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        TEN TEN TEN
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "v0", "x4", "x5", "memory");
}


void freq_test(string res_dir) {
    bool has_output_dir = false;
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    freq(10000);
    double begin = second();
    freq(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1000000000.0 / (end - begin);
    printf("Frequency: %f GHz, Cycle time: %f ns\n", f, 1/f);
    if(has_output_dir){
        string output_dir = res_dir + "/log/freq.res";
        ofstream output_file;
        output_file.open(output_dir);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir);
        output_file << "Frequency: "<<f<<" GHz, Cycle time: "<<1/f<<" ns\n"<< endl;
        output_file.close();
    }
}

int main(int argc, char* argv[]) {
    freq_test(argv[1]);
    return 0;
}
