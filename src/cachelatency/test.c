#define _GNU_SOURCE
#include <sched.h>
// #include <sys/sysinfo.h>

#include <stdio.h>
#include "cache.h"

// void set_cpu(int id)
// {
//     cpu_set_t mask;
//     CPU_ZERO(&mask);
//     CPU_SET(id, &mask);
//     if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
//     {
//         printf("warning: could not set CPU affinity \n");
//     }
// }

// void enviroment_setup()
// {
//     printf("try to set cpu affinity \n");
// 	set_cpu(0x0001);
//     printf("enviroment setup \n");
// }

int test_package(MY_SIZE i_stride,MY_SIZE stride,MY_SIZE init,FILE* fp,int type)
{

    MY_SIZE i;
    for (i = init; i < RAND_TEST_NUM; i+=i_stride) {

        _cache_hierarchy(stride,i,fp,type);

        if (i >= 3*1024)
        {
            i_stride = 32;
        }
        else if (i >= 256)
        {
            i_stride = 4;
        }
        // i_stride = 2;
    }

    return 0;
}

int main()
{
    //// enviroment probe
    // int CpuNum = get_nprocs();
    // printf("Cpu num : %d\n\n",CpuNum);

    //// enviroment setup
    // enviroment_setup();

    //// test setup
    printf("\n>>>>> Running Cache Latency Test\n");

    int type_array[5] = {RPERRPAGE_TEST,LINEAR_TEST,RANDOM_TEST,RINRVPRANGE_TEST,TLBMISS_TEST};
    int i;
    for(i=0;i<4;i++)
    {
        MY_SIZE i_stride = 2;
        MY_SIZE init = 2;
        int type = type_array[i];
        // int type = RPERRPAGE_TEST;
        // int type = LINEAR_TEST;
        // int type = RANDOM_TEST;
        // int type = TLBMISS_TEST;
        // int type = RINRVPRANGE_TEST;

        int stride = 64;
        if (type == TLBMISS_TEST)
            stride = PAGE_CAP;

        char* filename;

        if (type == TLBMISS_TEST)
        {
            filename = "./res/log/tlbmiss_res.txt";
            printf("TEST: tlbmiss\n");
        }
        else if (type == RPERRPAGE_TEST)
        {
            filename = "./res/log/rperrpage_res.txt";
            printf("TEST: rperrpage\n");
        }
        else if (type == RANDOM_TEST)
        {
            filename = "./res/log/random_res.txt";
            printf("TEST: random\n");
        }
        else if (type == LINEAR_TEST)
        {
            filename = "./res/log/linear_res.txt";
            printf("TEST: linear\n");
        }
        else if (type == RINRVPRANGE_TEST)
        {
            filename = "./res/log/rinrvprange_res.txt";
            printf("TEST: rinrvprange\n");
        }


        FILE* fp = fopen(filename , "w");

        test_package(i_stride,stride,init,fp,type);

        fclose(fp);
    }

    //// enviroment check
    // int cpu = 0;
    // while(1)
    // {
    //     int cur_cpu = sched_getcpu();
    //     if (cur_cpu != cpu) {
    //       printf("pre:%d, cur:%d\n", cpu, cur_cpu);
    //       cpu = cur_cpu;
    //     }
    // }

    return 0;
}