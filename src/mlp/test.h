#include "cache.h"
#include <math.h>
#include <string.h>

#define PAGE_CAP 4096

#define RAND_TEST_NUM 8096*2
#define MAX_SIZE RAND_TEST_NUM*4*1024

#define INNER_LOOP 30
#define MAX_INTERLEAVE 30
