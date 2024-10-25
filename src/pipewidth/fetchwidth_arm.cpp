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

void __attribute__ ((noinline)) crosspage(uint64_t cnt){
#undef ONE
#define ONE "nop\r\n"
    asm volatile(
        ".align 12 \r\n"
	THOUSAND
	TEN
	TEN
	ONE
	ONE
	ONE
    "1: \r\n"
        ONE
	"2: \r\n"
        ONE
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "v0", "x4", "x5", "memory");
}

void crosspage_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    crosspage(10000);
    double begin = second();
    crosspage(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * 4) / 1.0e9 / (end - begin) / freq;
    printf("Crosspage IPC: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Crosspage IPC: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) fetch8(uint64_t cnt){
#undef ONE
#define ONE "nop\r\n"
     asm volatile(
        ".align 12 \r\n"
	THOUSAND
	TEN
	TEN
        "1: \r\n"
	ONE
	ONE
	ONE
        ONE
        "2: \r\n"
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "v0", "x4", "x5", "memory");
}

void fetch8_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    fetch8(10000);
    double begin = second();
    fetch8(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * 12) / 1.0e9 / (end - begin) / freq;
    printf("Fetch8 IPC: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Fetch8 IPC: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) fetch10(uint64_t cnt){
#undef ONE
#define ONE "nop\r\n"
     asm volatile(
        ".align 12 \r\n"
	THOUSAND
	TEN
	TEN
        "1: \r\n"
	ONE
        "2: \r\n"
        ONE
	ONE
	ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "v0", "x4", "x5", "memory");
}

void fetch10_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    fetch10(10000);
    double begin = second();
    fetch10(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * 12) / 1.0e9 / (end - begin) / freq;
    printf("Fetch10 IPC: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "Fetch10 IPC: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) half_line_align(uint64_t cnt){
#undef ONE
#define ONE "nop\r\n"
     asm volatile(
        ".align 8 \r\n"
        TEN
        ONE
        ONE
        ONE
        ONE
        ONE
        "1: \r\n"
        "b 3f \r\n"
        "2: \r\n"
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        "3: \r\n"
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "v0", "x4", "x5", "memory");
}

void half_line_align_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    half_line_align(10000);
    double begin = second();
    half_line_align(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * 10) / 1.0e9 / (end - begin) / freq;
    printf("half_line_align IPC: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "half_line_align IPC: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) cross_line_align(uint64_t cnt){
#undef ONE
#define ONE "nop\r\n"
     asm volatile(
        ".align 8 \r\n"
        TEN
        ONE
        ONE
        ONE
        ONE
        ONE
        "1: \r\n"
        "b 3f \r\n"
        "2: \r\n"
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        "3: \r\n"
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "v0", "x4", "x5", "memory");
}

void cross_line_align_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    cross_line_align(10000);
    double begin = second();
    cross_line_align(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * 12) / 1.0e9 / (end - begin) / freq;
    printf("cross_line_align IPC: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "cross_line_align IPC: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

void __attribute__ ((noinline)) cross_line_conflict(uint64_t cnt){
#undef ONE
#define ONE "nop\r\n"
     asm volatile(
        ".align 8 \r\n"
        TEN
        ONE
        ONE
        ONE
        ONE
        ONE
        "1: \r\n"
        "b 3f \r\n"
        "2: \r\n"
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        "3: \r\n"
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        ONE
        "subs %0, %0, #1 \r\n"
        "b.ne 1b \r\n"
        :
        :"r"(cnt)
        :"x9", "x10", "v0", "x4", "x5", "memory");
}

void cross_line_conflict_test(string res_dir,double freq) {
    bool has_output_dir = false;
    string output_dir = res_dir + "/log/pipewidth.res";
    if(res_dir.length() > 0){
        has_output_dir = true;
    }

    cross_line_conflict(10000);
    double begin = second();
    cross_line_conflict(__LOOP_COUNT);
    double end = second();
    double f = (__LOOP_COUNT * 12) / 1.0e9 / (end - begin) / freq;
    printf("cross_line_conflict IPC: %f\n", f, 1/f);
    if(has_output_dir){
        ofstream output_file;
        output_file.open(output_dir,ios::app);
        output_file << f << endl;
        output_file.close();

        output_dir = res_dir + "/report.mk";
        output_file.open(output_dir,ios::app);
        output_file << "cross_line_conflict IPC: "<<f<<"\n"<< endl;
        output_file.close();
    }
}

int main(int argc, char* argv[]) {
    crosspage_test(argv[1],atof(argv[2]));
    fetch8_test(argv[1],atof(argv[2]));
    fetch10_test(argv[1],atof(argv[2]));
    half_line_align_test(argv[1],atof(argv[2]));
    cross_line_align_test(argv[1],atof(argv[2]));
    cross_line_conflict_test(argv[1],atof(argv[2]));
    return 0;
}
