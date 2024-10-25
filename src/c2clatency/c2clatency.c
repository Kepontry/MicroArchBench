#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

#define RETRY 100000000

static inline long long nano_second(void){
    struct timespec _t;
    clock_gettime(CLOCK_REALTIME, &_t);
    return _t.tv_sec * 1000000000ll + _t.tv_nsec;
}

// static inline double second(void){
//     struct timespec _t;
//     clock_gettime(CLOCK_REALTIME, &_t);
//     return _t.tv_sec + _t.tv_nsec/1.0e9;
// }

volatile size_t dummy __attribute__((aligned(64)));
volatile int start    __attribute__((aligned(64)));
size_t num_samples = 1000;
size_t num_round_trips = 5000;

int cmp (const void *a, const void *b) {
   return *(double*)a > *(double*)b;
}

void prepare(void) {
    register size_t trash = 0xbadbeef;
    register size_t i = 1000000000;
    do {
        trash += trash;
    } while (--i);
    asm volatile ("" : "+r"(trash));
}


void set_aff(int c) {
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(c, &mask);
    int retry = 0;
    while(sched_setaffinity(0, sizeof(cpu_set_t), &mask) != 0) {
        retry++;
        if(retry < RETRY);
        else{
            printf("%s:%d %s:%s\n", __FILE__, __LINE__, __func__, strerror(errno));
            exit(1);
        }
    }   
}
void *func1(void *a)
{
    set_aff((size_t)a);
    size_t n = num_round_trips * num_samples;
    size_t expected = 1;
    __atomic_fetch_add(&start, 1, __ATOMIC_RELAXED);
    while (start < 2);
    __sync_synchronize();
    for (register size_t i = 0; i < n; ++i) {
        while(!__atomic_compare_exchange_n(&dummy, (void*)&expected, 0, 1, __ATOMIC_RELAXED, __ATOMIC_RELAXED)) {
            expected = 1;
        };
    }
    return NULL;
}

void *func2(void *a)
{
    set_aff((size_t)a);
    long long begin, end, dt, v[1000];
    size_t expected = 0;
    __atomic_fetch_add(&start, 1, __ATOMIC_RELAXED);
    while (start < 2);
    __sync_synchronize();
    for (size_t i = 0; i < num_samples; i++)
    {
        begin = nano_second();
        for (register size_t i = 0; i < num_round_trips; ++i) {
            while(!__atomic_compare_exchange_n(&dummy, (void*)&expected, 1, 1, __ATOMIC_RELAXED, __ATOMIC_RELAXED)) {
                expected = 0;
            }
        }
        v[i] = nano_second() - begin;
    }

    double vd[1000];
    double ave = 0;
    for (size_t i = 0; i < num_samples; i++) {
        vd [i] = (double)v[i] / num_round_trips / 2;
        ave += vd[i];
    }
    ave /= num_samples;
    // qsort(vd, num_samples, sizeof(double), cmp);
    double stddev = 0;
    for (size_t i = 0; i < num_samples; i++) {
        stddev += pow(vd[i] - ave, 2);
    }
    stddev = pow(stddev, 0.5);
    // printf("%.1f(%.1f),", ave, stddev);
    printf("%.1f,", ave);
    return NULL;
}

int main(int argc, char **argv)
{
    if (argc >= 2)
    {
        num_samples = atol(argv[1]);
    }
    if (argc == 3)
    {
        num_round_trips = atol(argv[2]);
    }
    long ncpu = sysconf(_SC_NPROCESSORS_ONLN);
    // printf("ncpu:%ld\n", ncpu);
#define NT 2
    pthread_t tid[NT];
    for (long i = 0; i < ncpu; i++)
    {
        for (long j = 0; j < ncpu; j++)
        {
            if (i == j) {
                printf("0,");
                continue;
            }
            pthread_create(tid + 0, NULL, func1, (void*)i);
            pthread_create(tid + 1, NULL, func2, (void*)j);
            pthread_join(tid[0], NULL);
            pthread_join(tid[1], NULL);
            __atomic_store_n(&start, 0, __ATOMIC_SEQ_CST);
            fflush(stdout);
        }
        printf("\n");
    }
    return 0;
}
