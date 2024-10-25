#define _GNU_SOURCE
#include <sched.h>
// #include <sys/sysinfo.h>

#include <stdio.h>
#include "test.h"

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

int stride_add(int cur){
    int next = 0;
    int tmp = (int)log2(cur);
    // printf("tmp: %d %d",cur,tmp);
    next = pow(2,tmp) / 4;
    // printf("nxt: %d",next);
    if(next < 2) return cur + 2;
    return cur + (int)next;
}


int test_package(MY_SIZE i_stride,MY_SIZE stride,MY_SIZE init,FILE* fp,int interleave)
{

    MY_SIZE i;
    if(interleave == 1){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy1(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 2){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy2(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 3){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy3(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 4){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy4(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 5){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy5(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 6){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy6(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 7){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy7(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 8){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy8(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 9){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy9(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 10){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy10(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 11){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy11(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 12){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy12(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 13){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy13(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 14){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy14(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 15){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy15(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 16){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy16(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 17){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy17(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 18){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy18(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 19){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy19(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 20){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy20(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 21){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy21(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 22){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy22(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 23){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy23(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 24){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy24(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 25){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy25(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 26){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy26(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 27){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy27(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 28){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy28(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 29){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy29(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 30){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy30(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 32){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy32(stride,i,fp);
            //printf("TEST: running %ld\n",i);
            i = stride_add(i);
        }
    }else if(interleave == 50){
        i = init;
        while(i < RAND_TEST_NUM){
            _cache_hierarchy50(stride,i,fp);
        }
    }else{
        ;
    }

    return 0;
}

int main(int argc, char* argv[])
{
    //// enviroment probe
    // int CpuNum = get_nprocs();
    // printf("Cpu num : %d\n\n",CpuNum);

    //// enviroment setup
    // enviroment_setup();

    //// test setup
    char* filename[MAX_INTERLEAVE+2];
    filename[ 0] = "/log/mlp/random_res1.txt";
    filename[ 1] = "/log/mlp/random_res2.txt";
    filename[ 2] = "/log/mlp/random_res3.txt";
    filename[ 3] = "/log/mlp/random_res4.txt";
    filename[ 4] = "/log/mlp/random_res5.txt";
    filename[ 5] = "/log/mlp/random_res6.txt";
    filename[ 6] = "/log/mlp/random_res7.txt";
    filename[ 7] = "/log/mlp/random_res8.txt";
    filename[ 8] = "/log/mlp/random_res9.txt";
    filename[ 9] = "/log/mlp/random_res10.txt";
    filename[10] = "/log/mlp/random_res11.txt";
    filename[11] = "/log/mlp/random_res12.txt";
    filename[12] = "/log/mlp/random_res13.txt";
    filename[13] = "/log/mlp/random_res14.txt";
    filename[14] = "/log/mlp/random_res15.txt";
    filename[15] = "/log/mlp/random_res16.txt";
    filename[16] = "/log/mlp/random_res17.txt";
    filename[17] = "/log/mlp/random_res18.txt";
    filename[18] = "/log/mlp/random_res19.txt";
    filename[19] = "/log/mlp/random_res20.txt";
    filename[20] = "/log/mlp/random_res21.txt";
    filename[21] = "/log/mlp/random_res22.txt";
    filename[22] = "/log/mlp/random_res23.txt";
    filename[23] = "/log/mlp/random_res24.txt";
    filename[24] = "/log/mlp/random_res25.txt";
    filename[25] = "/log/mlp/random_res26.txt";
    filename[26] = "/log/mlp/random_res27.txt";
    filename[27] = "/log/mlp/random_res28.txt";
    filename[28] = "/log/mlp/random_res29.txt";
    filename[29] = "/log/mlp/random_res30.txt";
    filename[30] = "/log/mlp/random_res31.txt";
    filename[31] = "/log/mlp/random_res32.txt";


    printf("\n>>>>> Running MLP Test\n");

    int test_case[12] = {0,1,2,3,5,7,11,15,19,23,27,31};
    for(int i=0;i < 12; i++){
        MY_SIZE i_stride = 2;
        MY_SIZE init = 2;
        int stride = 64;
        int target_case = test_case[i];

        printf("TEST: random probe with interleave: %d\n",target_case+1);
        char source[100];
	    strcpy(source,argv[1]);
        FILE* fp = fopen(strcat(source,filename[target_case]) , "w");
        test_package(i_stride,stride,init,fp,target_case+1);
        fclose(fp);
    }
    // {
    //     MY_SIZE i_stride = 2;
    //     MY_SIZE init = 2;
    //     int stride = 64;

    //     printf("TEST: random probe with interleave: %d\n",40);
    //     FILE* fp = fopen("random_res40.txt" , "w");
    //     test_package(i_stride,stride,init,fp,40);
    //     fclose(fp);
    // }
    // {
    //     MY_SIZE i_stride = 2;
    //     MY_SIZE init = 2;
    //     int stride = 64;

    //     printf("TEST: random probe with interleave: %d\n",50);
    //     FILE* fp = fopen("random_res50.txt" , "w");
    //     test_package(i_stride,stride,init,fp,50);
    //     fclose(fp);
    // }

    return 0;
}