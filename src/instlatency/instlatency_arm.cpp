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
#define ONE "mul x9, x9, x9\r\n"
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
#define ONE "mul x8, x9, x9\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "x4", "x5", "x6", "x7","memory");
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
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
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
#define ONE "udiv x4, x9, x8\r\n" \
            "add x9, x9, x4\r\n" \
            "sub x9, x9, x4\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        "mov x9, #0 \r\n"
        "sub x9, x9, #1 \r\n"
        "mov x8, #3 \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "x4", "x5", "memory");
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
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT) - 2;
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
#define ONE "sdiv x4, x9, x8\r\n" \
            "add x9, x9, x4\r\n" \
            "sub x9, x9, x4\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        "mov x9, #0 \r\n"
        "sub x9, x9, #1 \r\n"
        "mov x8, #3 \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "x4", "x5", "memory");
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
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT) - 2;
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
#define ONE "udiv x4, x9, x8\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        "mov x9, #0 \r\n"
        "sub x9, x9, #1 \r\n"
        "mov x8, #3 \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "x4", "x5", "memory");
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
#define ONE "fadd d0, d0, d0\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"d0", "d1");
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
#define ONE "fadd d1, d0, d2\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"d0", "d1");
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
#define ONE "fmadd d0, d0, d0, d0\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"d0", "d1");
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
#define ONE "fmadd d1, d0, d3, d0\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"d0", "d1");
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
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
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
#define ONE "fmul d0, d0, d0\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"d0", "d1");
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
#define ONE "fmul d1, d0, d2\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"d0", "d1");
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
    double f = (__LOOP_COUNT * __INNER_COUNT) / 1.0e9 / (end - begin) / freq;
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
#define ONE "fdiv d4, d9, d10\r\n" \
            "fadd d9, d9, d4\r\n" \
            "fsub d9, d9, d4\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        "mov x9, #0 \r\n"
        "sub x9, x9, #1 \r\n"
        "ucvtf d9, x9 \r\n"
        "mov x9, #3 \r\n"
        "scvtf d10, x9 \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9","d9", "d10", "d4");
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
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT) - 4;
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
#define ONE "fdiv d4, d9, d10\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        "mov x9, #0 \r\n"
        "sub x9, x9, #1 \r\n"
        "ucvtf d9, x9 \r\n"
        "mov x9, #3 \r\n"
        "scvtf d10, x9 \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9","d9", "d10", "d4");
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
#define ONE "fsqrt d4, d4\r\n"
    asm volatile(
        ".align 8 \r\n"
        "1: \r\n"
        // "mov x9, #0 \r\n"
        // "sub x9, x9, #1 \r\n"
        // "ucvtf d9, x9 \r\n"
        // "mov x9, #3 \r\n"
        // "scvtf d10, x9 \r\n"
        HUNDRED
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9","d9", "d10", "d4");
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
    double f = 1.0e9 * (end - begin) * freq / (__LOOP_COUNT * __INNER_COUNT);
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
