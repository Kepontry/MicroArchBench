#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "cache.h"

MY_SIZE *ptr_init_RinRVprange(MY_SIZE max, MY_SIZE scale) {
    MY_SIZE page_num = max*scale/PAGE_CAP;
    MY_SIZE page_cap = PAGE_CAP/scale;

    MY_SIZE *partition_size = (MY_SIZE *)malloc(page_num * sizeof(MY_SIZE));
    MY_SIZE *partition_base = (MY_SIZE *)malloc(page_num * sizeof(MY_SIZE));
    if (!partition_size || !partition_base) {
        printf("[ptr_init_RinRVprange] malloc fail\n");
        return NULL;
    }
    memset(partition_size, 0, page_num * sizeof(MY_SIZE));
    memset(partition_base, 0, page_num * sizeof(MY_SIZE));

    MY_SIZE chunk_num = chunk_partition(partition_size,partition_base,page_num,32);

    MY_SIZE i,j,v,o;
    for (i = 0; i < chunk_num; i++) {
        o = rand() % chunk_num;
        v = partition_size[o];
        partition_size[o] = partition_size[i];
        partition_size[i] = v;

        v = partition_base[o];
        partition_base[o] = partition_base[i];
        partition_base[i] = v;
    }

    // for (int i = 0; i < chunk_num; i++) {
    //     printf("id: %d ; base: %d ; size : %d\n",i,partition_base[i],partition_size[i]);
    // }

    MY_SIZE *ptrs = (MY_SIZE *)malloc(max * sizeof(MY_SIZE));
    if (!ptrs) {
        printf("[ptr_init_RinRVprange] malloc fail\n");
        return NULL;
    }
    memset(ptrs, 0, max * sizeof(MY_SIZE));

    MY_SIZE index = 0;
    for (i = 0; i < chunk_num; ++i) {
        MY_SIZE base = index;
        for(j = 0;j<partition_size[i]*page_cap;j++){
            ptrs[index++] = partition_base[i] * PAGE_CAP + j*scale;
        }

        for (j = 0 ; j < partition_size[i]*page_cap; j++) {
            o = rand() % (partition_size[i]*page_cap);
            v = ptrs[base + o];
            ptrs[base + o] = ptrs[j];
            ptrs[j] = v;
        }
    }

    free(partition_size);
    free(partition_base);

    return ptrs;/**/
}

MY_SIZE *ptr_init_RPerRPage(MY_SIZE max, MY_SIZE scale) {
    MY_SIZE page_num = max*scale/PAGE_CAP;
    MY_SIZE page_cap = PAGE_CAP/scale;

    MY_SIZE *pages = (MY_SIZE *)malloc(page_num * sizeof(MY_SIZE));
    if (!pages) {
        printf("[ptr_init_RPerRPage] malloc fail\n");
        return NULL;
    }
    memset(pages, 0, page_num * sizeof(MY_SIZE));

    MY_SIZE i,j,v,o;

    for (i = 0; i < page_num; ++i) {
        pages[i] = i;
    }

    for (i = 0; i < page_num; i++) {
        o = rand() % page_num;
        v = pages[o];
        pages[o] = pages[i];
        pages[i] = v;
    }

    MY_SIZE *ptrs = (MY_SIZE *)malloc(max * sizeof(MY_SIZE));
    if (!ptrs) {
        printf("[ptr_init_RPerRPage] malloc fail\n");
        return NULL;
    }
    memset(ptrs, 0, max * sizeof(MY_SIZE));

    for (i = 0; i < max; ++i) {
        ptrs[i] = pages[i*scale/PAGE_CAP] * PAGE_CAP + i*scale%PAGE_CAP;
    }

    MY_SIZE base;
    for (i = 0; i < max; i++) {
        o = rand() % page_cap;
        base = (i*scale/PAGE_CAP * PAGE_CAP)/scale;
        v = ptrs[base + o];
        ptrs[base + o] = ptrs[i];
        ptrs[i] = v;
    }

    free(pages);

    return ptrs;
}

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

MY_SIZE *ptr_init_Linear(MY_SIZE max, MY_SIZE scale) {
    MY_SIZE *ptrs = (MY_SIZE *)malloc(max * sizeof(MY_SIZE));

    if (!ptrs){
        printf("[ptr_init_Linear] malloc fail\n");
        return NULL;
    }
    memset(ptrs, 0, max * sizeof(MY_SIZE));

    MY_SIZE i;
    for (i = 0; i < max; ++i) {
        ptrs[i] = i * scale;
    }

    return ptrs;
}

MY_SIZE *ptr_init_Tlbmiss(MY_SIZE max, MY_SIZE scale) {
    MY_SIZE *ptrs = (MY_SIZE *)malloc(max * sizeof(MY_SIZE));

    if (!ptrs){
        printf("[ptr_init_Tlbmiss] malloc fail\n");
        return NULL;
    }
    memset(ptrs, 0, max * sizeof(MY_SIZE));

    MY_SIZE i;
    for (i = 0; i < max; ++i) {
        ptrs[i] = i * PAGE_CAP;
    }

    if (max < 2)
        return ptrs;

    MY_SIZE v, o;
    for (i = 0; i < max; i++) {
        o = rand() % max;
        v = ptrs[o];
        ptrs[o] = ptrs[i];
        ptrs[i] = v;
    }

    return ptrs;
}

void rnd_init(void *test_setting,int type)
{
    struct rand_ptr_info *setting = (struct rand_ptr_info *)test_setting;

    setting->nptrs = setting->curRange / setting->line;

    if(type == RPERRPAGE_TEST)
        setting->ptrs = ptr_init_RPerRPage(setting->nptrs, setting->line);
    else if(type == LINEAR_TEST)
        setting->ptrs = ptr_init_Linear(setting->nptrs, setting->line);
    else if(type == RANDOM_TEST)
        setting->ptrs = ptr_init_Random(setting->nptrs, setting->line);
    else if(type == TLBMISS_TEST)
        setting->ptrs = ptr_init_Tlbmiss(setting->nptrs, setting->line);
    else if(type == RINRVPRANGE_TEST)
        setting->ptrs = ptr_init_RinRVprange(setting->nptrs, setting->line);

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
    /* */
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

int _cache_hierarchy(MY_SIZE stride,MY_SIZE i,FILE* fp, int type)
{
    struct rand_ptr_info setting = {0};
    setting.maxRange = MAX_SIZE;
    MY_SIZE loop = 30;
    struct timeval timeStart,timeEnd;

    // init all data structure
    setting.line = stride;
    setting.curRange = i*4*1024;
    MY_SIZE traverse = (loop*setting.curRange) / (setting.line * 100);
    rnd_init(&setting,type);
 
    // warm-up 
    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeEnd, NULL);
    int warmup_loopnum = 200000000;
    int a=0;
    for(int i=0;i<warmup_loopnum;i++){
        a++;
    }

    // benchmark
    gettimeofday(&timeStart, NULL);
    cache_latency(&setting, traverse);
    gettimeofday(&timeEnd, NULL);

    double timeSpan = (timeEnd.tv_sec - timeStart.tv_sec)* 1000000 + (timeEnd.tv_usec - timeStart.tv_usec);
    fprintf(fp,"%ld\t%f\n",i*4,1000*timeSpan/(double)(traverse*100));

    free(setting.addr);
    free(setting.ptrs);

    return a;
}