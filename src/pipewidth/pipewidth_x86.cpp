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
#define ONE \
    "add %%rdx, %%r8  \n\t" \
    "add %%rdx, %%r9  \n\t" \
    "add %%rdx, %%r10 \n\t" \
    "add %%rdx, %%r11 \n\t" \
    "add %%rdx, %%r12 \n\t" \
    "add %%rdx, %%r13 \n\t" \
    "add %%rdx, %%r14 \n\t" \
    "add %%rdx, %%r15 \n\t" 

    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r8", "r9", "r10","r11","r12","r13","r14","r15");
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
    double f = (__LOOP_COUNT * __INNER_COUNT * 8) / 1.0e9 / (end - begin) / freq;
    printf("ALU width: %f\n", f);
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
#define ONE "nop \r\n"
    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r8", "r9", "memory");
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
    printf("Nop width: %f\n", f);
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
#define ONE "vandpd %%xmm0, %%xmm1, %%xmm2\r\n" \
            "vandpd %%xmm0, %%xmm1, %%xmm3\r\n" \
            "vandpd %%xmm0, %%xmm1, %%xmm4\r\n" \
            "vandpd %%xmm0, %%xmm1, %%xmm5\r\n" \
            "vandpd %%xmm0, %%xmm1, %%xmm6\r\n" \
            "vandpd %%xmm0, %%xmm1, %%xmm7\r\n" \
            "vandpd %%xmm0, %%xmm1, %%xmm8\r\n" \
            "vandpd %%xmm0, %%xmm1, %%xmm9\r\n"
    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r9","xmm0","xmm1","xmm2","xmm3","xmm4","xmm5","xmm6","xmm7","xmm8","xmm9","xmm10");
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
    double f = (__LOOP_COUNT * __INNER_COUNT * 8) / 1.0e9 / (end - begin) / freq;
    printf("FPU width: %f\n", f);
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
#define ONE "vandpd %%xmm0, %%xmm1, %%xmm2\r\n" \
            "add %%rax, %%r9 \r\n" \
            "add %%rax, %%r10\r\n" \
            "vandpd %%xmm0, %%xmm1, %%xmm3\r\n" \
            "add %%rax, %%r11\r\n" \
            "add %%rax, %%r12\r\n" \
            "vandpd %%xmm0, %%xmm1, %%xmm4\r\n" \
            "add %%rax, %%r13\r\n" \
            "add %%rax, %%r14\r\n" \

    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        TEN ONE
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r9","r10","r11","r12","r13","r14","xmm2","xmm3","xmm4");
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
    printf("Rename width: %f\n", f);
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
    printf("BRU width: %f\n", f);
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
#define ONE "mov   (%1), %%r9\r\n" \
            "mov  8(%1), %%r9\r\n" \
            "mov 16(%1), %%r9\r\n" \
            "mov 24(%1), %%r9\r\n" 
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        TEN TEN FIVE
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt), "r"(loadbase)
        :"r9", "r10","memory");
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
    printf("Load width: %f\n", f);
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
#define ONE "mov %%r9,   (%1)\r\n" \
            "mov %%r9,  8(%1)\r\n" \
            "mov %%r9, 16(%1)\r\n" \
            "mov %%r9, 24(%1)\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        TEN TEN FIVE
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt), "r"(storebase)
        :"r9", "r10","memory");
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
    printf("Store width: %f\n", f);
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
#define ONE "mov %%r9, (%1)\r\n" \
            "mov (%2), %%r10\r\n" \
            "mov %%r9, (%1)\r\n" \
            "mov (%2), %%r10\r\n" \
            "mov %%r9, (%1)\r\n" \
            "mov (%2), %%r10\r\n" \
            "mov %%r9, (%1)\r\n" \
            "mov (%2), %%r10\r\n" 
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        TEN TEN FIVE
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt), "r"(storebase), "r"(loadbase)
        :"r9", "r10","memory");
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
    printf("AGU width: %f\n", f);
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
