#include <stdio.h>
#include <stdlib.h>

typedef size_t MY_SIZE;

int cache_hierarchy();
int _cache_hierarchy1(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy2(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy3(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy4(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy5(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy6(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy7(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy8(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy9(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy10(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy11(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy12(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy13(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy14(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy15(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy16(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy17(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy18(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy19(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy20(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy21(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy22(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy23(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy24(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy25(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy26(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy27(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy28(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy29(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy30(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy32(MY_SIZE stride,MY_SIZE i,FILE* fp);
int _cache_hierarchy50(MY_SIZE stride,MY_SIZE i,FILE* fp);

struct rand_ptr_info {
    MY_SIZE curRange;  // The address range for current run, e.g., 8 KB
    MY_SIZE maxRange;  // The maximum address range set by user, e.g., 8 MB
    MY_SIZE line;      // Stride;

    char *addr;  // Raw pointer to char array of sizeof(maxlen)

    MY_SIZE *ptrs;  // ptr array for random pattern
    MY_SIZE nptrs;  // total number of ptr

    char *p;  // Traversal pointer
};

#define ONE p = (char **)*p;
#define FIVE ONE ONE ONE ONE ONE
#define TEN FIVE FIVE
#define FIFITY TEN TEN TEN TEN TEN
#define HUNDRED FIFITY FIFITY

#define ONE_2 p[0] = (char **)*(p[0]);p[1] = (char **)*(p[1]);
#define FIVE_2 ONE_2 ONE_2 ONE_2 ONE_2 ONE_2
#define TEN_2 FIVE_2 FIVE_2
#define FIFITY_2 TEN_2 TEN_2 TEN_2 TEN_2 TEN_2
#define HUNDRED_2 FIFITY_2 FIFITY_2

#define ONE_3 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];
#define FIVE_3 ONE_3 ONE_3 ONE_3 ONE_3 ONE_3
#define TEN_3 FIVE_3 FIVE_3
#define FIFITY_3 TEN_3 TEN_3 TEN_3 TEN_3 TEN_3
#define HUNDRED_3 FIFITY_3 FIFITY_3

#define ONE_4 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];
#define FIVE_4 ONE_4 ONE_4 ONE_4 ONE_4 ONE_4
#define TEN_4 FIVE_4 FIVE_4
#define FIFITY_4 TEN_4 TEN_4 TEN_4 TEN_4 TEN_4
#define HUNDRED_4 FIFITY_4 FIFITY_4

#define ONE_5 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];
#define FIVE_5 ONE_5 ONE_5 ONE_5 ONE_5 ONE_5
#define TEN_5 FIVE_5 FIVE_5
#define FIFITY_5 TEN_5 TEN_5 TEN_5 TEN_5 TEN_5
#define HUNDRED_5 FIFITY_5 FIFITY_5

#define ONE_6 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];
#define FIVE_6 ONE_6 ONE_6 ONE_6 ONE_6 ONE_6
#define TEN_6 FIVE_6 FIVE_6
#define FIFITY_6 TEN_6 TEN_6 TEN_6 TEN_6 TEN_6
#define HUNDRED_6 FIFITY_6 FIFITY_6

#define ONE_7 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];
#define FIVE_7 ONE_7 ONE_7 ONE_7 ONE_7 ONE_7
#define TEN_7 FIVE_7 FIVE_7
#define FIFITY_7 TEN_7 TEN_7 TEN_7 TEN_7 TEN_7
#define HUNDRED_7 FIFITY_7 FIFITY_7

#define ONE_8 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];
#define FIVE_8 ONE_8 ONE_8 ONE_8 ONE_8 ONE_8
#define TEN_8 FIVE_8 FIVE_8
#define FIFITY_8 TEN_8 TEN_8 TEN_8 TEN_8 TEN_8
#define HUNDRED_8 FIFITY_8 FIFITY_8

#define ONE_9 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];
#define FIVE_9 ONE_9 ONE_9 ONE_9 ONE_9 ONE_9
#define TEN_9 FIVE_9 FIVE_9
#define FIFITY_9 TEN_9 TEN_9 TEN_9 TEN_9 TEN_9
#define HUNDRED_9 FIFITY_9 FIFITY_9

#define ONE_10 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];
#define FIVE_10 ONE_10 ONE_10 ONE_10 ONE_10 ONE_10
#define TEN_10 FIVE_10 FIVE_10
#define FIFITY_10 TEN_10 TEN_10 TEN_10 TEN_10 TEN_10
#define HUNDRED_10 FIFITY_10 FIFITY_10

#define ONE_11 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];
#define FIVE_11 ONE_11 ONE_11 ONE_11 ONE_11 ONE_11
#define TEN_11 FIVE_11 FIVE_11
#define FIFITY_11 TEN_11 TEN_11 TEN_11 TEN_11 TEN_11
#define HUNDRED_11 FIFITY_11 FIFITY_11

#define ONE_12 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];
#define FIVE_12 ONE_12 ONE_12 ONE_12 ONE_12 ONE_12
#define TEN_12 FIVE_12 FIVE_12
#define FIFITY_12 TEN_12 TEN_12 TEN_12 TEN_12 TEN_12
#define HUNDRED_12 FIFITY_12 FIFITY_12

#define ONE_13 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];
#define FIVE_13 ONE_13 ONE_13 ONE_13 ONE_13 ONE_13
#define TEN_13 FIVE_13 FIVE_13
#define FIFITY_13 TEN_13 TEN_13 TEN_13 TEN_13 TEN_13
#define HUNDRED_13 FIFITY_13 FIFITY_13

#define ONE_14 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];
#define FIVE_14 ONE_14 ONE_14 ONE_14 ONE_14 ONE_14
#define TEN_14 FIVE_14 FIVE_14
#define FIFITY_14 TEN_14 TEN_14 TEN_14 TEN_14 TEN_14
#define HUNDRED_14 FIFITY_14 FIFITY_14

#define ONE_15 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];
#define FIVE_15 ONE_15 ONE_15 ONE_15 ONE_15 ONE_15
#define TEN_15 FIVE_15 FIVE_15
#define FIFITY_15 TEN_15 TEN_15 TEN_15 TEN_15 TEN_15
#define HUNDRED_15 FIFITY_15 FIFITY_15

#define ONE_16 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];
#define FIVE_16 ONE_16 ONE_16 ONE_16 ONE_16 ONE_16
#define TEN_16 FIVE_16 FIVE_16
#define FIFITY_16 TEN_16 TEN_16 TEN_16 TEN_16 TEN_16
#define HUNDRED_16 FIFITY_16 FIFITY_16

#define ONE_17 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];
#define FIVE_17 ONE_17 ONE_17 ONE_17 ONE_17 ONE_17
#define TEN_17 FIVE_17 FIVE_17
#define FIFITY_17 TEN_17 TEN_17 TEN_17 TEN_17 TEN_17
#define HUNDRED_17 FIFITY_17 FIFITY_17

#define ONE_18 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];
#define FIVE_18 ONE_18 ONE_18 ONE_18 ONE_18 ONE_18
#define TEN_18 FIVE_18 FIVE_18
#define FIFITY_18 TEN_18 TEN_18 TEN_18 TEN_18 TEN_18
#define HUNDRED_18 FIFITY_18 FIFITY_18

#define ONE_19 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];
#define FIVE_19 ONE_19 ONE_19 ONE_19 ONE_19 ONE_19
#define TEN_19 FIVE_19 FIVE_19
#define FIFITY_19 TEN_19 TEN_19 TEN_19 TEN_19 TEN_19
#define HUNDRED_19 FIFITY_19 FIFITY_19

#define ONE_20 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];
#define FIVE_20 ONE_20 ONE_20 ONE_20 ONE_20 ONE_20
#define TEN_20 FIVE_20 FIVE_20
#define FIFITY_20 TEN_20 TEN_20 TEN_20 TEN_20 TEN_20
#define HUNDRED_20 FIFITY_20 FIFITY_20

#define ONE_21 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];p[20] = (char **)*p[20];
#define FIVE_21 ONE_21 ONE_21 ONE_21 ONE_21 ONE_21
#define TEN_21 FIVE_21 FIVE_21
#define FIFITY_21 TEN_21 TEN_21 TEN_21 TEN_21 TEN_21
#define HUNDRED_21 FIFITY_21 FIFITY_21

#define ONE_22 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];p[20] = (char **)*p[20];p[21] = (char **)*p[21];
#define FIVE_22 ONE_22 ONE_22 ONE_22 ONE_22 ONE_22
#define TEN_22 FIVE_22 FIVE_22
#define FIFITY_22 TEN_22 TEN_22 TEN_22 TEN_22 TEN_22
#define HUNDRED_22 FIFITY_22 FIFITY_22

#define ONE_23 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];p[20] = (char **)*p[20];p[21] = (char **)*p[21];p[22] = (char **)*p[22];
#define FIVE_23 ONE_23 ONE_23 ONE_23 ONE_23 ONE_23
#define TEN_23 FIVE_23 FIVE_23
#define FIFITY_23 TEN_23 TEN_23 TEN_23 TEN_23 TEN_23
#define HUNDRED_23 FIFITY_23 FIFITY_23

#define ONE_24 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];p[20] = (char **)*p[20];p[21] = (char **)*p[21];p[22] = (char **)*p[22];p[23] = (char **)*p[23];
#define FIVE_24 ONE_24 ONE_24 ONE_24 ONE_24 ONE_24
#define TEN_24 FIVE_24 FIVE_24
#define FIFITY_24 TEN_24 TEN_24 TEN_24 TEN_24 TEN_24
#define HUNDRED_24 FIFITY_24 FIFITY_24

#define ONE_25 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];p[20] = (char **)*p[20];p[21] = (char **)*p[21];p[22] = (char **)*p[22];p[23] = (char **)*p[23];p[24] = (char **)*p[24];
#define FIVE_25 ONE_25 ONE_25 ONE_25 ONE_25 ONE_25
#define TEN_25 FIVE_25 FIVE_25
#define FIFITY_25 TEN_25 TEN_25 TEN_25 TEN_25 TEN_25
#define HUNDRED_25 FIFITY_25 FIFITY_25

#define ONE_26 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];p[20] = (char **)*p[20];p[21] = (char **)*p[21];p[22] = (char **)*p[22];p[23] = (char **)*p[23];p[24] = (char **)*p[24];p[25] = (char **)*p[25];
#define FIVE_26 ONE_26 ONE_26 ONE_26 ONE_26 ONE_26
#define TEN_26 FIVE_26 FIVE_26
#define FIFITY_26 TEN_26 TEN_26 TEN_26 TEN_26 TEN_26
#define HUNDRED_26 FIFITY_26 FIFITY_26

#define ONE_27 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];p[20] = (char **)*p[20];p[21] = (char **)*p[21];p[22] = (char **)*p[22];p[23] = (char **)*p[23];p[24] = (char **)*p[24];p[25] = (char **)*p[25];p[26] = (char **)*p[26];
#define FIVE_27 ONE_27 ONE_27 ONE_27 ONE_27 ONE_27
#define TEN_27 FIVE_27 FIVE_27
#define FIFITY_27 TEN_27 TEN_27 TEN_27 TEN_27 TEN_27
#define HUNDRED_27 FIFITY_27 FIFITY_27

#define ONE_28 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];p[20] = (char **)*p[20];p[21] = (char **)*p[21];p[22] = (char **)*p[22];p[23] = (char **)*p[23];p[24] = (char **)*p[24];p[25] = (char **)*p[25];p[26] = (char **)*p[26];p[27] = (char **)*p[27];
#define FIVE_28 ONE_28 ONE_28 ONE_28 ONE_28 ONE_28
#define TEN_28 FIVE_28 FIVE_28
#define FIFITY_28 TEN_28 TEN_28 TEN_28 TEN_28 TEN_28
#define HUNDRED_28 FIFITY_28 FIFITY_28

#define ONE_29 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];p[20] = (char **)*p[20];p[21] = (char **)*p[21];p[22] = (char **)*p[22];p[23] = (char **)*p[23];p[24] = (char **)*p[24];p[25] = (char **)*p[25];p[26] = (char **)*p[26];p[27] = (char **)*p[27];p[28] = (char **)*p[28];
#define FIVE_29 ONE_29 ONE_29 ONE_29 ONE_29 ONE_29
#define TEN_29 FIVE_29 FIVE_29
#define FIFITY_29 TEN_29 TEN_29 TEN_29 TEN_29 TEN_29
#define HUNDRED_29 FIFITY_29 FIFITY_29

#define ONE_30 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];p[20] = (char **)*p[20];p[21] = (char **)*p[21];p[22] = (char **)*p[22];p[23] = (char **)*p[23];p[24] = (char **)*p[24];p[25] = (char **)*p[25];p[26] = (char **)*p[26];p[27] = (char **)*p[27];p[28] = (char **)*p[28];p[29] = (char **)*p[29];
#define FIVE_30 ONE_30 ONE_30 ONE_30 ONE_30 ONE_30
#define TEN_30 FIVE_30 FIVE_30
#define FIFITY_30 TEN_30 TEN_30 TEN_30 TEN_30 TEN_30
#define HUNDRED_30 FIFITY_30 FIFITY_30


#define ONE_32 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];p[20] = (char **)*p[20];p[21] = (char **)*p[21];p[22] = (char **)*p[22];p[23] = (char **)*p[23];p[24] = (char **)*p[24];p[25] = (char **)*p[25];p[26] = (char **)*p[26];p[27] = (char **)*p[27];p[28] = (char **)*p[28];p[29] = (char **)*p[29];p[30] = (char **)*p[30];p[31] = (char **)*p[31];
#define FIVE_32 ONE_32 ONE_32 ONE_32 ONE_32 ONE_32
#define TEN_32 FIVE_32 FIVE_32
#define FIFITY_32 TEN_32 TEN_32 TEN_32 TEN_32 TEN_32
#define HUNDRED_32 FIFITY_32 FIFITY_32

#define ONE_50 p[0] = (char **)*p[0];p[1] = (char **)*p[1];p[2] = (char **)*p[2];p[3] = (char **)*p[3];p[4] = (char **)*p[4];p[5] = (char **)*p[5];p[6] = (char **)*p[6];p[7] = (char **)*p[7];p[8] = (char **)*p[8];p[9] = (char **)*p[9];p[10] = (char **)*p[10];p[11] = (char **)*p[11];p[12] = (char **)*p[12];p[13] = (char **)*p[13];p[14] = (char **)*p[14];p[15] = (char **)*p[15];p[16] = (char **)*p[16];p[17] = (char **)*p[17];p[18] = (char **)*p[18];p[19] = (char **)*p[19];p[20] = (char **)*p[20];p[21] = (char **)*p[21];p[22] = (char **)*p[22];p[23] = (char **)*p[23];p[24] = (char **)*p[24];p[25] = (char **)*p[25];p[26] = (char **)*p[26];p[27] = (char **)*p[27];p[28] = (char **)*p[28];p[29] = (char **)*p[29];p[30] = (char **)*p[30];p[31] = (char **)*p[31];p[33] = (char **)*p[33];p[33] = (char **)*p[33];p[34] = (char **)*p[34];p[35] = (char **)*p[35];p[36] = (char **)*p[36];p[37] = (char **)*p[37];p[38] = (char **)*p[38];p[39] = (char **)*p[39];p[32] = (char **)*p[32];p[41] = (char **)*p[41];p[44] = (char **)*p[44];p[43] = (char **)*p[43];p[44] = (char **)*p[44];p[45] = (char **)*p[45];p[46] = (char **)*p[46];p[47] = (char **)*p[47];p[48] = (char **)*p[48];p[49] = (char **)*p[49];
#define FIVE_50 ONE_50 ONE_50 ONE_50 ONE_50 ONE_50
#define TEN_50 FIVE_50 FIVE_50
#define FIFITY_50 TEN_50 TEN_50 TEN_50 TEN_50 TEN_50
#define HUNDRED_50 FIFITY_50 FIFITY_50