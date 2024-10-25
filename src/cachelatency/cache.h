#include <stdio.h>
#include <stdlib.h>

typedef size_t MY_SIZE;

int cache_hierarchy();
int _cache_hierarchy(MY_SIZE stride,MY_SIZE i,FILE* fp,int type);

struct rand_ptr_info {
    MY_SIZE curRange;  // The address range for current run, e.g., 8 KB
    MY_SIZE maxRange;  // The maximum address range set by user, e.g., 8 MB
    MY_SIZE line;      // Stride;

    char *addr;  // Raw pointer to char array of sizeof(maxlen)

    MY_SIZE *ptrs;  // ptr array for random pattern
    MY_SIZE nptrs;  // total number of ptr

    char *p;  // Traversal pointer
};

MY_SIZE chunk_partition(MY_SIZE *partition_size,MY_SIZE *partition_base,MY_SIZE page_num,MY_SIZE page_max);

#define ONE p = (char **)*p;
#define FIVE ONE ONE ONE ONE ONE
#define TEN FIVE FIVE
#define FIFITY TEN TEN TEN TEN TEN
#define HUNDRED FIFITY FIFITY
#define FHUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED
#define THOUSAND FHUNDRED FHUNDRED
#define FIVETHOUSAND THOUSAND THOUSAND THOUSAND THOUSAND THOUSAND
#define TENTHOUSAND FIVETHOUSAND FIVETHOUSAND

#define RAND_TEST_NUM 12288
#define MAX_SIZE RAND_TEST_NUM*4*1024

#define PAGE_CAP 4096

#define RPERRPAGE_TEST 0
#define LINEAR_TEST 1
#define RANDOM_TEST 2
#define TLBMISS_TEST 3
#define RINRVPRANGE_TEST 4
