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

void __attribute__ ((noinline)) mullat(uint64_t cnt){
#define ONE \
    "imul %%r8, %%r8  \n\t"

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


void mullat_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    mullat(10000);
    double begin = second();
    mullat(__LOOP_COUNT);
    double end = second();
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT);
    printf("Mul latency: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Mul latency: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) mulbw(uint64_t cnt){
#define ONE "imul %%rdx, %%r8   \n\t" \
            "imul %%rax, %%r9   \n\t" \
            "imul %%rcx, %%r10  \n\t" \
            "imul %%rbx, %%r11  \n\t" \
            "imul %%rdx, %%r12  \n\t" \
            "imul %%rax, %%r13  \n\t" \
            "imul %%rcx, %%r14  \n\t" \
            "imul %%rbx, %%r15  \n\t"

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

void mulbw_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    mulbw(10000);
    double begin = second();
    mulbw(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) * 8 / 1.0e9 / (end - begin) / freq;
    printf("Mul bandwidth: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Mul bandwidth: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) udivlat(uint64_t cnt){
#define ONE "mov %%r9, %%rax \n\t" \
            "mov $0, %%rdx \n\t" \
            "div %%r8   \n\t" \
            "add %%rax, %%r8  \n\t" \
            "sub %%rax, %%r8  \n\t" 

    asm volatile(
        ".align 256 \r\n"
        "mov $3, %%r8 \r\n"
        "mov $0, %%r9 \n\t" \
        "sub $1, %%r9 \n\t" 
        "1: \r\n"
        ONE
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r8", "r9", "rax", "rdx");
}


void udivlat_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    udivlat(10000);
    double begin = second();
    udivlat(__LOOP_COUNT);
    double end = second();
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT/ 100) - 2;
    printf("Div(unsigned) latency: %f (plz compute)\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Div(unsigned) latency: "<<f<<" (plz compute)\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) sdivlat(uint64_t cnt){
#define ONE "mov %%r9, %%rax \n\t" \
            "cqo \n\t" \
            "idiv %%r8   \n\t" \
            "add %%rax, %%r8  \n\t" \
            "sub %%rax, %%r8  \n\t" 

    asm volatile(
        ".align 256 \r\n"
        "mov $3, %%r8 \r\n"
        "mov $0, %%r9 \n\t" \
        "sub $1, %%r9 \n\t" 
        "1: \r\n"
        ONE
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r8", "r9", "rax", "rdx");
}


void sdivlat_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    sdivlat(10000);
    double begin = second();
    sdivlat(__LOOP_COUNT);
    double end = second();
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT/ 100) - 2;
    printf("Div(signed) latency: %f (plz compute)\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Div(signed) latency: "<<f<<" (plz compute)\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) udivbw(uint64_t cnt){
#define ONE "mov %%r9, %%rax \n\t" \
            "mov $0, %%rdx \n\t" \
            "div %%r8 \n\t"

    asm volatile(
        ".align 256 \r\n"
        "mov $3, %%r8 \r\n"
        "mov $0, %%r9 \n\t" \
        "sub $1, %%r9 \n\t" 
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r8", "r9", "rax", "rdx");
}

void udivbw_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    udivbw(10000);
    double begin = second();
    udivbw(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("Div(unsigned) bandwidth: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Div(unsigned) bandwidth: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) faddlat(uint64_t cnt){
#undef ONE
#define ONE "vaddss %%xmm0, %%xmm0, %%xmm0\r\n"
    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"xmm0");
}
void faddlat_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    faddlat(10000);
    double begin = second();
    faddlat(__LOOP_COUNT);
    double end = second();
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT);
    printf("Fadd latency: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Fadd latency: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) faddbw(uint64_t cnt){
#undef ONE
#define ONE "vaddss %%xmm0, %%xmm1, %%xmm2\r\n"
    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"xmm2");
}

void faddbw_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    faddbw(10000);
    double begin = second();
    faddbw(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("Fadd bandwidth: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Fadd bandwidth: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) fmalat(uint64_t cnt){
#undef ONE
#define ONE "vfmadd132pd %%xmm2, %%xmm1, %%xmm0\r\n"
    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"xmm0","xmm1","xmm2");
}

void fmalat_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    fmalat(10000);
    double begin = second();
    fmalat(__LOOP_COUNT);
    double end = second();
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT);
    printf("Fma latency: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Fma latency: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) fmabw(uint64_t cnt){
#undef ONE
#define ONE "vfmadd132pd %%xmm0, %%xmm0, %%xmm1\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm2\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm3\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm4\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm5\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm6\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm7\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm8\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm9\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm10\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm11\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm12\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm13\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm14\r\n" \
            "vfmadd132pd %%xmm0, %%xmm0, %%xmm15\r\n" 
    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        ONE ONE ONE ONE
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"xmm0","xmm1","xmm2","xmm3","xmm4","xmm5","xmm6","xmm7",
        "xmm8","xmm9","xmm10","xmm11","xmm12","xmm13","xmm14","xmm15");
}

void fmabw_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    fmabw(10000);
    double begin = second();
    fmabw(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT * 6 / 10) / 1.0e9 / (end - begin) / freq;
    printf("Fma bandwidth: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Fma bandwidth: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) fmullat(uint64_t cnt){
#undef ONE
#define ONE "mulss %%xmm0, %%xmm0\r\n" 
    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"xmm0","xmm1","xmm2","xmm3","xmm4","xmm5","xmm6","xmm7");
}

void fmullat_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    fmullat(10000);
    double begin = second();
    fmullat(__LOOP_COUNT);
    double end = second();
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT);
    printf("Fmul latency: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Fmul latency: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) fmulbw(uint64_t cnt){
#undef ONE
#define ONE "mulss %%xmm0, %%xmm1\r\n" \
            "mulss %%xmm0, %%xmm2\r\n" \
            "mulss %%xmm0, %%xmm3\r\n" \
            "mulss %%xmm0, %%xmm4\r\n" \
            "mulss %%xmm0, %%xmm5\r\n" \
            "mulss %%xmm0, %%xmm6\r\n" \
            "mulss %%xmm0, %%xmm7\r\n" \
            "mulss %%xmm0, %%xmm8\r\n" 

    asm volatile(
        ".align 256 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"xmm0","xmm1","xmm2","xmm3","xmm4","xmm5","xmm6","xmm7","xmm8");
}

void fmulbw_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    fmulbw(10000);
    double begin = second();
    fmulbw(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT * 8) / 1.0e9 / (end - begin) / freq;
    printf("Fmul bandwidth: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Fmul bandwidth: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) fdivlat(uint64_t cnt){
#define ONE "vdivss %%xmm0, %%xmm1, %%xmm2\r\n" \
            "vaddss %%xmm2, %%xmm1, %%xmm1\r\n" \
            "vsubss %%xmm2, %%xmm1, %%xmm1\r\n"

    asm volatile(
        ".align 256 \r\n"
        "mov $0, %%r9 \r\n"
        "sub $1, %%r9 \r\n" 
        "cvtsi2sd %%r9, %%xmm0 \r\n" // TOFIX signed convert
        "mov $3, %%r9 \r\n"
        "cvtsi2sd %%r9, %%xmm1 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r9","xmm0","xmm1","xmm2","xmm3","xmm4","xmm5","xmm6","xmm7","xmm8");
}

void fdivlat_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    fdivlat(10000);
    double begin = second();
    fdivlat(__LOOP_COUNT);
    double end = second();
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT); //TOFIX
    printf("Fdiv latency: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Fdiv latency: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) fdivbw(uint64_t cnt){
#define ONE "vdivss %%xmm0, %%xmm1, %%xmm2\r\n" 

    asm volatile(
        ".align 256 \r\n"
        "mov $0, %%r9 \r\n"
        "sub $1, %%r9 \r\n" 
        "cvtsi2sd %%r9, %%xmm0 \r\n" // TOFIX signed convert
        "mov $3, %%r9 \r\n"
        "cvtsi2sd %%r9, %%xmm1 \r\n"
        "1: \r\n"
        HUNDRED
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :"r9","xmm0","xmm1","xmm2","xmm3","xmm4","xmm5","xmm6","xmm7","xmm8");
}

void fdivbw_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    fdivbw(10000);
    double begin = second();
    fdivbw(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
    printf("Fdiv bandwidth: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Fdiv bandwidth: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) fsqrtlat(uint64_t cnt){
#define ONE "fsqrt \r\n"
    asm volatile(
        "fldpi \n\t"
        ".align 8 \r\n"
        "1: \r\n"
        TEN
        "dec %0 \r\n"
        "jne 1b \r\n"
        :
        :"r"(cnt)
        :);
}

void fsqrtlat_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/instlatency.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    fsqrtlat(10000);
    double begin = second();
    fsqrtlat(__LOOP_COUNT);
    double end = second();
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT / 10);
    printf("Fsqrt latency: %f\n", f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Fsqrt latency: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

int main(int argc, char* argv[]) {
    mullat_test(argv[1],atof(argv[2]));
    mulbw_test(argv[1],atof(argv[2]));
    udivlat_test(argv[1],atof(argv[2]));
    sdivlat_test(argv[1],atof(argv[2]));
    udivbw_test(argv[1],atof(argv[2]));
    faddlat_test(argv[1],atof(argv[2]));
    faddbw_test(argv[1],atof(argv[2]));
    fmalat_test(argv[1],atof(argv[2]));
    fmabw_test(argv[1],atof(argv[2]));
    fmullat_test(argv[1],atof(argv[2]));
    fmulbw_test(argv[1],atof(argv[2]));
    fdivlat_test(argv[1],atof(argv[2]));
    fdivbw_test(argv[1],atof(argv[2]));
    fsqrtlat_test(argv[1],atof(argv[2]));
    return 0;
}
