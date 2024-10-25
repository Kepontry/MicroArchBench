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
#define __LOOP_COUNT 200000000ULL
#endif

void __attribute__ ((noinline)) aluwidth(uint64_t cnt){
#define ONE "add x9, x10, #1\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "v0", "x4", "x5", "memory");
}


void aluwidth_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    aluwidth(10000);
    double begin = second();
    aluwidth(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("ALU width: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "ALU width: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) nopwidth(uint64_t cnt){
#undef ONE
#define ONE "nop\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "v0", "x4", "x5", "memory");
}

void nopwidth_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    nopwidth(10000);
    double begin = second();
    nopwidth(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("Nop width: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Nop width: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) fpuwidth(uint64_t cnt){
#undef ONE
#define ONE "fabs d0, d1\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "v0", "x4", "x5", "memory");
}

void fpuwidth_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    fpuwidth(10000);
    double begin = second();
    fpuwidth(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("FPU width: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "FPU width: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) renamewidth(uint64_t cnt){
#undef ONE
#define ONE "fabs d0, d1\r\n" \
            "add x9, x10, #1\r\n" \
            "add x9, x10, #1\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        TEN TEN TEN ONE ONE ONE
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "d0", "d1", "memory");
}

void renamewidth_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    renamewidth(10000);
    double begin = second();
    renamewidth(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("Rename width: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Rename width: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) brwidth(uint64_t cnt){
#undef ONE
#define ONE "b.ne 1b\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        "mov x9 , #1\r\n"
        "mov x10, #1\r\n"
        "cmp x10,x9\r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "d0", "d1", "memory");
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


void __attribute__ ((noinline)) loadwidth(uint64_t cnt,uint64_t* loadbase){
#undef ONE
#define ONE "ldr x9, [%1, #0 ]\r\n" \
            "ldr x9, [%1, #8 ]\r\n" \
            "ldr x9, [%1, #16]\r\n" \
            "ldr x9, [%1, #24]\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        TEN TEN FIVE
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt), "r"(loadbase)
        :"x9", "x10", "d0", "d1", "memory");
}

void loadwidth_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    uint64_t foo[10];

    loadwidth(10000,foo);
    double begin = second();
    loadwidth(__LOOP_COUNT,foo);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("Load width: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Load width: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) storewidth(uint64_t cnt,uint64_t* storebase){
#undef ONE
#define ONE "str x9, [%1, #0 ]\r\n" \
            "str x9, [%1, #8 ]\r\n" \
            "str x9, [%1, #16]\r\n" \
            "str x9, [%1, #24]\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        TEN TEN FIVE
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt), "r"(storebase)
        :"x9", "x10", "d0", "d1", "memory");
}

void storewidth_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    uint64_t foo[10];

    storewidth(10000,foo);
    double begin = second();
    storewidth(__LOOP_COUNT,foo);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("Store width: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Store width: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) aguwidth(uint64_t cnt,uint64_t* storebase,uint64_t* loadbase){
#undef ONE
#define ONE "ldr x10, [%2, #0]\r\n" \
            "str x9,  [%1, #0]\r\n" \
            "ldr x10, [%2, #8]\r\n" \
            "str x9,  [%1, #8]\r\n" \
            "ldr x10, [%2, #16]\r\n" \
            "str x9,  [%1, #16]\r\n" \
            "ldr x10, [%2, #24]\r\n" \
            "str x9,  [%1, #24]\r\n" 
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        TEN TEN FIVE
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt), "r"(storebase), "r"(loadbase)
        :"x9", "x10", "d0", "d1", "memory");
}

void aguwidth_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    uint64_t foo0[10];
    uint64_t foo1[10];

    aguwidth(10000,foo0,foo1);
    double begin = second();
    aguwidth(__LOOP_COUNT,foo0,foo1);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT * 2) / 1.0e9 / (end - begin) / freq;
    printf("AGU width: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "AGU width: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

int main(int argc, char* argv[]) {
    aluwidth_test(argv[1],atof(argv[2]));
    nopwidth_test(argv[1],atof(argv[2]));
    brwidth_test(argv[1],atof(argv[2]));
    fpuwidth_test(argv[1],atof(argv[2]));
    renamewidth_test(argv[1],atof(argv[2]));
    loadwidth_test(argv[1],atof(argv[2]));
    storewidth_test(argv[1],atof(argv[2]));
    aguwidth_test(argv[1],atof(argv[2]));
    return 0;
}
