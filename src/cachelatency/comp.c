#include "cache.h"

MY_SIZE chunk_partition(MY_SIZE *partition_size,MY_SIZE *partition_base,MY_SIZE page_num,MY_SIZE page_max)
{
    MY_SIZE i;
    for (i = 0; i < page_num; ++i) {
        partition_size[i] = rand() % page_max + 1;
    }

    MY_SIZE bound=0;
    for (i = 0; i < page_num; ++i) {
        partition_base[i] = bound;
        bound += partition_size[i];
        if(bound >= page_num){
            // printf("%d ----- max = %d\n",i,page_num);
            break;
        }
    }

    partition_size[i] = partition_size[i] - (bound - page_num);
    // printf("\n");
    // for (int j = 0; j <= i; j++) {
    //     printf("%d : %d\t",partition_base[j],partition_size[j]);
    // }
    // printf("\n");

    return i+1;
}
