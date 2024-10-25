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
#define __LOOP_COUNT 10000000ULL
#endif

void __attribute__ ((noinline)) ptchase(uint64_t cnt,uint64_t* loadbase){
#undef ONE
#define ONE "ldr %1, [%1]\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt), "r"(loadbase)
        :"x9", "x10", "d0", "d1", "memory");
}

void ptchase_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/ptchase.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    uint64_t foo[10];
    foo[0] = (uint64_t)foo;

    ptchase(10000,foo);
    double begin = second();
    ptchase(__LOOP_COUNT,foo);
    double end = second();
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT);
    printf("Pointer chasing: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Pointer chasing: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) noptchase(uint64_t cnt,uint64_t* storebase){
#undef ONE
#define ONE "ldr x9, [%1]\r\n" \
            "add %1, x9 , %1\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        FIFTY
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt), "r"(storebase)
        :"x9", "x10", "d0", "d1", "memory");
}

void noptchase_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/ptchase.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    uint64_t foo[10];
    foo[0] = 0;

    noptchase(10000,foo);
    double begin = second();
    noptchase(__LOOP_COUNT,foo);
    double end = second();
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT /2);
    printf("No pointer chasing: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "No pointer chasing: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

int main(int argc, char* argv[]) {
    ptchase_test(argv[1],atof(argv[2]));
    noptchase_test(argv[1],atof(argv[2]));
    return 0;
}
