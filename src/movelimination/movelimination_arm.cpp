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
#define __LOOP_COUNT 5000000ULL
#endif

void __attribute__ ((noinline)) mov_imm_zero(uint64_t cnt){
#define ONE \
    "mov x4,  #0  \n\t" \
    "mov x5,  #0  \n\t" \
    "mov x6,  #0  \n\t" \
    "mov x7,  #0  \n\t" \
    "mov x8,  #0  \n\t" \
    "mov x9,  #0  \n\t" \
    "mov x10,  #0  \n\t" \
    "mov x11,  #0  \n\t" \
    "mov x12,  #0  \n\t" \
    "mov x13,  #0  \n\t" 
    asm volatile(
        ".align 8 \n\t"
        "1: \n\t"
        HUNDRED
        "subs %0, %0, #1 \n\t"
        "b.ne 1b \n\t"
        :
        : "r"(cnt)
        :"x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "memory");
}

void mov_imm_zero_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/movelimination.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    mov_imm_zero(10000);
    double begin = second();
    mov_imm_zero(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT * 10) / 1.0e9 / (end - begin) / freq;
    printf("Mov imm zero: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Mov imm zero: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) mov_imm_one(uint64_t cnt){
#undef ONE
#define ONE \
    "mov x4,  #1  \n\t" \
    "mov x5,  #1  \n\t" \
    "mov x6,  #1  \n\t" \
    "mov x7,  #1  \n\t" \
    "mov x8,  #1  \n\t" \
    "mov x9,  #1  \n\t" \
    "mov x10,  #1  \n\t" \
    "mov x11,  #1  \n\t" \
    "mov x12,  #1  \n\t" \
    "mov x13,  #1  \n\t" 
    asm volatile(
        ".align 8 \n\t"
        "1: \n\t"
        HUNDRED
        "subs %0, %0, #1 \n\t"
        "b.ne 1b \n\t"
        :
        : "r"(cnt)
        :"x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "memory");
}

void mov_imm_one_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/movelimination.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    mov_imm_one(10000);
    double begin = second();
    mov_imm_one(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT * 10) / 1.0e9 / (end - begin) / freq;
    printf("Mov imm one: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Mov imm one: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) mov_chain(uint64_t cnt){
#undef ONE
#define ONE \
    "mov x9,  x12  \n\t" \
    "mov x10, x9  \n\t" \
    "mov x11, x10 \n\t" \
    "mov x4, x11 \n\t" \
    "mov x13, x4 \n\t" \
    "mov x5, x13 \n\t" \
    "mov x6, x5 \n\t" \
    "mov x7, x6 \n\t" \
    "mov x8, x7 \n\t" \
    "mov x12, x8 \n\t" 
    asm volatile(
        ".align 8 \n\t"
        "1: \n\t"
        HUNDRED
        "subs %0, %0, #1 \n\t"
        "b.ne 1b \n\t"
        :
        : "r"(cnt)
        :"x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "memory");
}

void mov_chain_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/movelimination.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    mov_chain(10000);
    double begin = second();
    mov_chain(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT * 10) / 1.0e9 / (end - begin) / freq;
    printf("Mov chain: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Mov chain: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) mov_single(uint64_t cnt){
#undef ONE
#define ONE \
    "mov x4,  x13  \n\t" \
    "mov x5,  x13  \n\t" \
    "mov x6,  x13  \n\t" \
    "mov x7,  x13  \n\t" \
    "mov x8,  x13  \n\t" \
    "mov x9,  x13  \n\t" \
    "mov x10, x13  \n\t" \
    "mov x11, x13  \n\t" \
    "mov x12, x13  \n\t" 
    asm volatile(
        ".align 8 \n\t"
        "1: \n\t"
        HUNDRED
        "subs %0, %0, #1 \n\t"
        "b.ne 1b \n\t"
        :
        : "r"(cnt)
        :"x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "memory");
}

void mov_single_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/movelimination.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    mov_single(10000);
    double begin = second();
    mov_single(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT * 9) / 1.0e9 / (end - begin) / freq;
    printf("Mov single: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Mov single: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) mov_self_mul(uint64_t cnt){
#undef ONE
#define ONE \
    "mov x4,  x4  \n\t" \
    "mov x5,  x5  \n\t" \
    "mov x6,  x6  \n\t" \
    "mov x7,  x7  \n\t" \
    "mov x8,  x8  \n\t" \
    "mov x9,  x9  \n\t" \
    "mov x10, x10  \n\t" \
    "mov x11, x11  \n\t" \
    "mov x12, x12  \n\t" 
    asm volatile(
        ".align 8 \n\t"
        "1: \n\t"
        HUNDRED
        "subs %0, %0, #1 \n\t"
        "b.ne 1b \n\t"
        :
        : "r"(cnt)
        :"x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "memory");
}

void mov_self_mul_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/movelimination.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    mov_self_mul(10000);
    double begin = second();
    mov_self_mul(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT * 9) / 1.0e9 / (end - begin) / freq;
    printf("Mov self mul: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Mov self mul: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) mov_self(uint64_t cnt){
#undef ONE
#define ONE \
    "mov x4,  x4  \n\t"
    asm volatile(
        ".align 8 \n\t"
        "1: \n\t"
        HUNDRED
        "subs %0, %0, #1 \n\t"
        "b.ne 1b \n\t"
        :
        : "r"(cnt)
        :"x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "memory");
}

void mov_self_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/movelimination.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    mov_self(10000);
    double begin = second();
    mov_self(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("Mov self: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Mov self: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) mov_bounce(uint64_t cnt){
#undef ONE
#define ONE \
    "mov x4,  x5  \n\t" \
    "mov x5,  x4  \n\t"
    asm volatile(
        ".align 8 \n\t"
        "1: \n\t"
        HUNDRED
        "subs %0, %0, #1 \n\t"
        "b.ne 1b \n\t"
        :
        : "r"(cnt)
        :"x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "memory");
}

void mov_bounce_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/movelimination.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    mov_bounce(10000);
    double begin = second();
    mov_bounce(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT * 2) / 1.0e9 / (end - begin) / freq;
    printf("Mov bounce: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Mov bounce: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) sub(uint64_t cnt){
#undef ONE
#define ONE \
    "sub x5, x5, x5  \n\t"
    asm volatile(
        ".align 8 \n\t"
        "1: \n\t"
        HUNDRED
        "subs %0, %0, #1 \n\t"
        "b.ne 1b \n\t"
        :
        : "r"(cnt)
        :"x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "memory");
}

void sub_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/movelimination.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    sub(10000);
    double begin = second();
    sub(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("Sub eli: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Sub eli: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) xor_eli(uint64_t cnt){
#undef ONE
#define ONE "eor x5, x5, x5  \n\t"
    asm volatile(
        ".align 8 \n\t"
        "1: \n\t"
        HUNDRED
        "subs %0, %0, #1 \n\t"
        "b.ne 1b \n\t"
        :
        : "r"(cnt)
        :"x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "memory");
}

void xor_eli_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/movelimination.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    xor_eli(10000);
    double begin = second();
    xor_eli(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("Xor_eli: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Xor_eli: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

int main(int argc, char* argv[]) {
    mov_imm_zero_test(argv[1],atof(argv[2]));
    mov_imm_one_test(argv[1],atof(argv[2]));
    mov_chain_test(argv[1],atof(argv[2]));
    mov_single_test(argv[1],atof(argv[2]));
    mov_self_test(argv[1],atof(argv[2]));
    mov_self_mul_test(argv[1],atof(argv[2]));
    mov_bounce_test(argv[1],atof(argv[2]));
    sub_test(argv[1],atof(argv[2]));
    xor_eli_test(argv[1],atof(argv[2]));
    return 0;
}
