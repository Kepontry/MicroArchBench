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
    "mov $0, %%r8  \n\t" \
    "mov $0, %%r9  \n\t" \
    "mov $0, %%r10 \n\t" \
    "mov $0, %%r11 \n\t" \
    "mov $0, %%r12 \n\t" \
    "mov $0, %%r13 \n\t" \
    "mov $0, %%r14 \n\t" \
    "mov $0, %%r15 \n\t" 

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
    double f = (__LOOP_COUNT * __INNER_COUNT * 8) / 1.0e9 / (end - begin) / freq;
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
    "mov $1, %%r8  \n\t" \
    "mov $1, %%r9  \n\t" \
    "mov $1, %%r10 \n\t" \
    "mov $1, %%r11 \n\t" \
    "mov $1, %%r12 \n\t" \
    "mov $1, %%r13 \n\t" \
    "mov $1, %%r14 \n\t" \
    "mov $1, %%r15 \n\t" 

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
    double f = (__LOOP_COUNT * __INNER_COUNT * 8) / 1.0e9 / (end - begin) / freq;
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
    "mov %%r15, %%r8  \n\t" \
    "mov %%r8 , %%r9  \n\t" \
    "mov %%r9 , %%r10 \n\t" \
    "mov %%r10, %%r11 \n\t" \
    "mov %%r11, %%r12 \n\t" \
    "mov %%r12, %%r13 \n\t" \
    "mov %%r13, %%r14 \n\t" \
    "mov %%r14, %%r15 \n\t" 

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
    double f = (__LOOP_COUNT * __INNER_COUNT * 8) / 1.0e9 / (end - begin) / freq;
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
    "mov %%rdx, %%r8  \n\t" \
    "mov %%rdx, %%r9  \n\t" \
    "mov %%rdx, %%r10 \n\t" \
    "mov %%rdx, %%r11 \n\t" \
    "mov %%rdx, %%r12 \n\t" \
    "mov %%rdx, %%r13 \n\t" \
    "mov %%rdx, %%r14 \n\t" \
    "mov %%rdx, %%r15 \n\t" 

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
    double f = (__LOOP_COUNT * __INNER_COUNT * 8) / 1.0e9 / (end - begin) / freq;
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
    "mov %%r8, %%r8  \n\t" \
    "mov %%r9, %%r9  \n\t" \
    "mov %%r10, %%r10 \n\t" \
    "mov %%r11, %%r11 \n\t" \
    "mov %%r12, %%r12 \n\t" \
    "mov %%r13, %%r13 \n\t" \
    "mov %%r14, %%r14 \n\t" \
    "mov %%r15, %%r15 \n\t" 

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
    double f = (__LOOP_COUNT * __INNER_COUNT * 8) / 1.0e9 / (end - begin) / freq;
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
    "mov %%r8, %%r8  \n\t" 
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
    "mov %%r8, %%r9  \n\t" \
    "mov %%r9, %%r8  \n\t" 

    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r8", "r9");
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
    "sub %%r8, %%r8  \n\t"

    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r8");
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
#define ONE \
    "xor %%r8, %%r8  \n\t"

    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r8");
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

void __attribute__ ((noinline)) fmov_single(uint64_t cnt){
#undef ONE
#define ONE \
    "movapd %%xmm0, %%xmm1 \n\t" \
    "movapd %%xmm0, %%xmm2 \n\t" \
    "movapd %%xmm0, %%xmm3 \n\t" \
    "movapd %%xmm0, %%xmm4 \n\t" \
    "movapd %%xmm0, %%xmm5 \n\t" \
    "movapd %%xmm0, %%xmm6 \n\t" \
    "movapd %%xmm0, %%xmm7 \n\t" \
    "movapd %%xmm0, %%xmm8 \n\t" 

    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"xmm1", "xmm2", "xmm3","xmm4","xmm5","xmm6","xmm7","xmm8");
}

void fmov_single_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/movelimination.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    fmov_single(10000);
    double begin = second();
    fmov_single(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT * 8) / 1.0e9 / (end - begin) / freq;
    printf("Fmov single: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Fmov single: "<<f<<"\n"<< endl;
        output_file.close();
    }
}


int main(int argc, char* argv[]) {
    mov_imm_zero_test(argv[1],atof(argv[2]));
    mov_imm_one_test(argv[1],atof(argv[2]));
    mov_chain_test(argv[1],atof(argv[2]));
    mov_single_test(argv[1],atof(argv[2]));
    fmov_single_test(argv[1],atof(argv[2]));
    mov_self_test(argv[1],atof(argv[2]));
    mov_self_mul_test(argv[1],atof(argv[2]));
    mov_bounce_test(argv[1],atof(argv[2]));
    sub_test(argv[1],atof(argv[2]));
    xor_eli_test(argv[1],atof(argv[2]));
    return 0;
}
