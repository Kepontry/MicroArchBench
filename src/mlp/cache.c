#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "test.h"

MY_SIZE *ptr_init_Random(MY_SIZE max, MY_SIZE scale) {
    MY_SIZE *ptrs = (MY_SIZE *)malloc(max * sizeof(MY_SIZE));

    if (!ptrs){
        printf("[ptr_init_Random] malloc fail\n");
        return NULL;
    }
    memset(ptrs, 0, max * sizeof(MY_SIZE));

    MY_SIZE i;
    for (i = 0; i < max; ++i) {
        ptrs[i] = i * scale;
    }

    MY_SIZE v, o;
    for (i = 0; i < max; i++) {
        o = rand() % max;
        v = ptrs[o];
        ptrs[o] = ptrs[i];
        ptrs[i] = v;
    }

    return ptrs;
}

void rnd_init(void *test_setting)
{
    struct rand_ptr_info *setting = (struct rand_ptr_info *)test_setting;

    setting->nptrs = setting->curRange / setting->line;

    setting->ptrs = ptr_init_Random(setting->nptrs, setting->line);

    char *addr = setting->addr = (char *)malloc(setting->maxRange+PAGE_CAP);
    long long addr_align = ((long long)addr) % PAGE_CAP;
    addr = addr + PAGE_CAP - addr_align;

    if (!setting->ptrs || !addr) {
        printf("[rnd_init] malloc fail\n");
        exit(0xdead);
    }

    MY_SIZE stride = setting->line;
    register MY_SIZE i, cur = setting->ptrs[0], next = 0;

    for (i = 1; i < setting->nptrs; i++) {
        next = setting->ptrs[i];
        *(char **)&addr[cur] = (char *)&addr[next];
        cur = next;
    }

    *(char **)&addr[cur] = (char *)&addr[setting->ptrs[0]];

    setting->p = addr;
}


int cache_latency(void *test_setting, MY_SIZE traverse)
{
    struct rand_ptr_info *setting = (struct rand_ptr_info *)test_setting;
    register char **p = (char **)setting->p;
    register MY_SIZE i = traverse;

    while (i-- > 0) {
        HUNDRED
    }

    setting->p = (char *)p;
    return 0;
}

int _cache_hierarchy1(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    struct rand_ptr_info setting = {0};
    setting.maxRange = MAX_SIZE;
    MY_SIZE loop = 50;
    struct timeval timeStart,timeEnd;

    // init all data structure
    setting.line = stride;
    setting.curRange = size*PAGE_CAP;
    MY_SIZE traverse = (loop*setting.curRange) / (setting.line * 100);
    rnd_init(&setting);
    // printf("INIT: setting done\n");
 
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);

    // benchmark
    gettimeofday(&timeStart, NULL);
    cache_latency(&setting, traverse);
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    free(setting.addr);
    free(setting.ptrs);

    return a;
}

int _cache_hierarchy2(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    struct rand_ptr_info setting[2] = {0};
    for(int i=0;i<2;i++){
        setting[i].maxRange = MAX_SIZE;
        // init all data structure
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
        // printf("INIT: setting[%d] done\n",i);
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    // printf("INIT: traverse: %ld\n",traverse);
    struct timeval timeStart,timeEnd;

        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);

    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        // printf("haha");
        register char **p[2];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        register MY_SIZE i = traverse;

        while (i-- > 0) {
            HUNDRED_2
        }

        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<2;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy3(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    struct rand_ptr_info setting[3] = {0};
    for(int i=0;i<3;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        register char **p[3];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        p[2] = (char **)setting[2].p;
        register MY_SIZE i = traverse;
        while (i-- > 0) {
            HUNDRED_3
        }
        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
        setting[2].p = (char *)(p[2]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<3;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy4(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    struct rand_ptr_info setting[4] = {0};
    for(int i=0;i<4;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[4];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        p[2] = (char **)setting[2].p;
        p[3] = (char **)setting[3].p;
        MY_SIZE i = traverse;
        while (i-- > 0) {
            HUNDRED_4
        }
        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
        setting[2].p = (char *)(p[2]);
        setting[3].p = (char *)(p[3]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<4;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy5(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    struct rand_ptr_info setting[5] = {0};
    for(int i=0;i<5;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        register char **p[5];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        p[2] = (char **)setting[2].p;
        p[3] = (char **)setting[3].p;
        p[4] = (char **)setting[4].p;
        register MY_SIZE i = traverse;
        while (i-- > 0) {
            HUNDRED_5
        }
        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
        setting[2].p = (char *)(p[2]);
        setting[3].p = (char *)(p[3]);
        setting[4].p = (char *)(p[4]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<5;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy6(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 6;
    struct rand_ptr_info setting[6] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        register char **p[6];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        p[2] = (char **)setting[2].p;
        p[3] = (char **)setting[3].p;
        p[4] = (char **)setting[4].p;
        p[5] = (char **)setting[5].p;
        register MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_6
        } 
        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
        setting[2].p = (char *)(p[2]);
        setting[3].p = (char *)(p[3]);
        setting[4].p = (char *)(p[4]);
        setting[5].p = (char *)(p[5]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy7(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 7;
    struct rand_ptr_info setting[7] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        register char **p[7];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        p[2] = (char **)setting[2].p;
        p[3] = (char **)setting[3].p;
        p[4] = (char **)setting[4].p;
        p[5] = (char **)setting[5].p;
        p[6] = (char **)setting[6].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_7
        } 
        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
        setting[2].p = (char *)(p[2]);
        setting[3].p = (char *)(p[3]);
        setting[4].p = (char *)(p[4]);
        setting[5].p = (char *)(p[5]);
        setting[6].p = (char *)(p[6]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy8(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 8;
    struct rand_ptr_info setting[8] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        register char **p[8];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        p[2] = (char **)setting[2].p;
        p[3] = (char **)setting[3].p;
        p[4] = (char **)setting[4].p;
        p[5] = (char **)setting[5].p;
        p[6] = (char **)setting[6].p;
        p[7] = (char **)setting[7].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_8
        } 
        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
        setting[2].p = (char *)(p[2]);
        setting[3].p = (char *)(p[3]);
        setting[4].p = (char *)(p[4]);
        setting[5].p = (char *)(p[5]);
        setting[6].p = (char *)(p[6]);
        setting[7].p = (char *)(p[7]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy9(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 9;
    struct rand_ptr_info setting[9] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        register char **p[9];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        p[2] = (char **)setting[2].p;
        p[3] = (char **)setting[3].p;
        p[4] = (char **)setting[4].p;
        p[5] = (char **)setting[5].p;
        p[6] = (char **)setting[6].p;
        p[7] = (char **)setting[7].p;
        p[8] = (char **)setting[8].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_9
        } 
        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
        setting[2].p = (char *)(p[2]);
        setting[3].p = (char *)(p[3]);
        setting[4].p = (char *)(p[4]);
        setting[5].p = (char *)(p[5]);
        setting[6].p = (char *)(p[6]);
        setting[7].p = (char *)(p[7]);
        setting[8].p = (char *)(p[8]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy10(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 10;
    struct rand_ptr_info setting[10] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        register char **p[10];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        p[2] = (char **)setting[2].p;
        p[3] = (char **)setting[3].p;
        p[4] = (char **)setting[4].p;
        p[5] = (char **)setting[5].p;
        p[6] = (char **)setting[6].p;
        p[7] = (char **)setting[7].p;
        p[8] = (char **)setting[8].p;
        p[9] = (char **)setting[9].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_10
        } 
        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
        setting[2].p = (char *)(p[2]);
        setting[3].p = (char *)(p[3]);
        setting[4].p = (char *)(p[4]);
        setting[5].p = (char *)(p[5]);
        setting[6].p = (char *)(p[6]);
        setting[7].p = (char *)(p[7]);
        setting[8].p = (char *)(p[8]);
        setting[9].p = (char *)(p[9]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy11(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 11;
    struct rand_ptr_info setting[11] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        register char **p[11];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        p[2] = (char **)setting[2].p;
        p[3] = (char **)setting[3].p;
        p[4] = (char **)setting[4].p;
        p[5] = (char **)setting[5].p;
        p[6] = (char **)setting[6].p;
        p[7] = (char **)setting[7].p;
        p[8] = (char **)setting[8].p;
        p[9] = (char **)setting[9].p;
        p[10] = (char **)setting[10].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_11
        } 
        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
        setting[2].p = (char *)(p[2]);
        setting[3].p = (char *)(p[3]);
        setting[4].p = (char *)(p[4]);
        setting[5].p = (char *)(p[5]);
        setting[6].p = (char *)(p[6]);
        setting[7].p = (char *)(p[7]);
        setting[8].p = (char *)(p[8]);
        setting[9].p = (char *)(p[9]);
        setting[10].p = (char *)(p[10]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy12(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 12;
    struct rand_ptr_info setting[12] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        register char **p[12];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        p[2] = (char **)setting[2].p;
        p[3] = (char **)setting[3].p;
        p[4] = (char **)setting[4].p;
        p[5] = (char **)setting[5].p;
        p[6] = (char **)setting[6].p;
        p[7] = (char **)setting[7].p;
        p[8] = (char **)setting[8].p;
        p[9] = (char **)setting[9].p;
        p[10] = (char **)setting[10].p;
        p[11] = (char **)setting[11].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_12
        } 
        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
        setting[2].p = (char *)(p[2]);
        setting[3].p = (char *)(p[3]);
        setting[4].p = (char *)(p[4]);
        setting[5].p = (char *)(p[5]);
        setting[6].p = (char *)(p[6]);
        setting[7].p = (char *)(p[7]);
        setting[8].p = (char *)(p[8]);
        setting[9].p = (char *)(p[9]);
        setting[10].p = (char *)(p[10]);
        setting[11].p = (char *)(p[11]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy13(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 13;
    struct rand_ptr_info setting[13] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        register char **p[13];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        p[2] = (char **)setting[2].p;
        p[3] = (char **)setting[3].p;
        p[4] = (char **)setting[4].p;
        p[5] = (char **)setting[5].p;
        p[6] = (char **)setting[6].p;
        p[7] = (char **)setting[7].p;
        p[8] = (char **)setting[8].p;
        p[9] = (char **)setting[9].p;
        p[10] = (char **)setting[10].p;
        p[11] = (char **)setting[11].p;
        p[12] = (char **)setting[12].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_13
        } 
        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
        setting[2].p = (char *)(p[2]);
        setting[3].p = (char *)(p[3]);
        setting[4].p = (char *)(p[4]);
        setting[5].p = (char *)(p[5]);
        setting[6].p = (char *)(p[6]);
        setting[7].p = (char *)(p[7]);
        setting[8].p = (char *)(p[8]);
        setting[9].p = (char *)(p[9]);
        setting[10].p = (char *)(p[10]);
        setting[11].p = (char *)(p[11]);
        setting[12].p = (char *)(p[12]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy14(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 14;
    struct rand_ptr_info setting[14] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[14];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_14
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy15(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 15;
    struct rand_ptr_info setting[15] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        register char **p[15];
        p[0] = (char **)setting[0].p;
        p[1] = (char **)setting[1].p;
        p[2] = (char **)setting[2].p;
        p[3] = (char **)setting[3].p;
        p[4] = (char **)setting[4].p;
        p[5] = (char **)setting[5].p;
        p[6] = (char **)setting[6].p;
        p[7] = (char **)setting[7].p;
        p[8] = (char **)setting[8].p;
        p[9] = (char **)setting[9].p;
        p[10] = (char **)setting[10].p;
        p[11] = (char **)setting[11].p;
        p[12] = (char **)setting[12].p;
        p[13] = (char **)setting[13].p;
        p[14] = (char **)setting[14].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_15
        } 
        setting[0].p = (char *)(p[0]);
        setting[1].p = (char *)(p[1]);
        setting[2].p = (char *)(p[2]);
        setting[3].p = (char *)(p[3]);
        setting[4].p = (char *)(p[4]);
        setting[5].p = (char *)(p[5]);
        setting[6].p = (char *)(p[6]);
        setting[7].p = (char *)(p[7]);
        setting[8].p = (char *)(p[8]);
        setting[9].p = (char *)(p[9]);
        setting[10].p = (char *)(p[10]);
        setting[11].p = (char *)(p[11]);
        setting[12].p = (char *)(p[12]);
        setting[13].p = (char *)(p[13]);
        setting[14].p = (char *)(p[14]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy16(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 16;
    struct rand_ptr_info setting[16] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[16];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_16
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy17(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 17;
    struct rand_ptr_info setting[17] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[17];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_17
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy18(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 18;
    struct rand_ptr_info setting[18] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[18];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_18
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy19(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 19;
    struct rand_ptr_info setting[19] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[19];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_19
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy20(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 20;
    struct rand_ptr_info setting[20] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[20];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_20
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy21(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 21;
    struct rand_ptr_info setting[21] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[21];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_21
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy22(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 22;
    struct rand_ptr_info setting[22] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[22];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_22
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy23(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 23;
    struct rand_ptr_info setting[23] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[23];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_23
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy24(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 24;
    struct rand_ptr_info setting[24] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[24];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_24
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy25(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 25;
    struct rand_ptr_info setting[25] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[25];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_25
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy26(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 26;
    struct rand_ptr_info setting[26] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[26];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_26
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy27(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 27;
    struct rand_ptr_info setting[27] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[27];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_27
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy28(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 28;
    struct rand_ptr_info setting[28] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[28];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_28
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy29(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 29;
    struct rand_ptr_info setting[29] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[29];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_29
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy30(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 30;
    struct rand_ptr_info setting[30] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[30];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_30
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}


int _cache_hierarchy32(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 32;
    struct rand_ptr_info setting[32] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[32];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_32
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}

int _cache_hierarchy50(MY_SIZE stride,MY_SIZE size,FILE* fp)
{
    int upper = 50;
    struct rand_ptr_info setting[50] = {0};
    for(int i=0;i<upper;i++){
        setting[i].maxRange = MAX_SIZE;
        setting[i].line = stride;
        setting[i].curRange = size*PAGE_CAP;
        rnd_init(&(setting[i]));
    }
    MY_SIZE traverse = (INNER_LOOP*setting[0].curRange) / (setting[0].line * 100);
    struct timeval timeStart,timeEnd;
        // warm-up 
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    // benchmark
    gettimeofday(&timeStart, NULL);
    if(1)
    {    
        char **p[50];
        for(int i=0; i<upper;i++) p[i] = (char **)setting[i].p;
        MY_SIZE i = traverse;
        while (i-- > 0){
            HUNDRED_50
        } 
        for(int i=0; i<upper;i++) setting[i].p = (char *)(p[i]);
    }
    gettimeofday(&timeEnd, NULL);

    long long timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld,%f\n",size*4,(double)1000*timeSpan);

    for(int i=0;i<upper;i++){
        free(setting[i].addr);
        free(setting[i].ptrs);
    }

    return a;
}