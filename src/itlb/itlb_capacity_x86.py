import os
import sys
import csv
import math

class ITLB_capacity:
    def generate_header(num,dense):
        header_file = open("test.h", "w")
        if(num < 256):
            header_file.write(" #define REPEAT 10000LL \n")
        elif(num < 1024):
            header_file.write(" #define REPEAT 1000LL \n")
        elif(num < 1024 * 4):
            header_file.write(" #define REPEAT 100LL \n")
        elif(num < 1024 * 8):
            header_file.write(" #define REPEAT 10LL \n")
        else:
            header_file.write(" #define REPEAT 10LL \n")
        header_file.write(" #define TEST_LOOP ")
        header_file.write("asm( \\\n")
        pos = 0
        for i in range(0,num):
            if(pos > 0):
                for j in range(0,pos):
                    header_file.write("\".long 0x00401f0f \\n\\t\" \\\n")
            header_file.write("\"1: jmp 1f\\n\\t\" \\\n")
            if(i == num - 1):
                for j in range(0,dense-1-pos):
                    if(j == 0): header_file.write("\".long 0x001f0f \\n\\t\" \\\n")
                    else:       header_file.write("\".long 0x00401f0f \\n\\t\" \\\n")
            else:
                for j in range(0,dense-pos):
                    if(j == 0): header_file.write("\".long 0x001f0f \\n\\t\" \\\n")
                    else:       header_file.write("\".long 0x00401f0f \\n\\t\" \\\n")
            pos = pos + 1
            if(pos >= dense):
                pos = 0
        header_file.write("\"1: \" \\\n")
        header_file.write(" : \\\n : \\\n :);\n ")

    # def br_num_inc(cur_num):
    #     return cur_num + 1
    def br_num_inc(cur_num):
        if cur_num == 1 :
            nxt_num = cur_num + 7
        # else:
        #     nxt_num = cur_num + 8
        elif cur_num < 2 * 1024 :
            nxt_num = cur_num + 8
        else:
            nxt_num = cur_num + 32
        return nxt_num
    
    def interval_inc(cur_num):
        nxt_num = 0
        tmp = math.log2(cur_num + 1)
        nxt_num = pow(2,tmp + 1)
        return int(nxt_num) - 1

## test code

# run test
min_num = 0
max_num = 1024 * 8
interval_max = pow(2,11)
interval = pow(2,10)
column_num = 0

# for interval in intervals :
print("\n>>>>> Running ITLB Capacity Test")
while interval < interval_max:
    br_num = min_num
    print("BTB test running interval:"+str(interval))
    pos = 0
    while br_num < max_num:
        # print("------------ generate code ------------")
        ITLB_capacity.generate_header(br_num,interval+16)

        # print("------------ compile code ------------")
        command = "gcc test.c -o test"
        # command = "xmake --build btb_test"
        os.system(command)

        # print("------------ run test ------------")
        command = "./test >> res.txt"
        os.system(command)

        # print("------------ control ------------")
        br_num  = ITLB_capacity.br_num_inc(br_num)
        # print("br_num: ",br_num,"interval: ",interval)
    column_num = column_num + 1
    interval = ITLB_capacity.interval_inc(interval)

# collect data
freq = float(sys.argv[1])
res_file = open("res.txt","r")
res_time = []
lines = res_file.readlines()
pos = 0
interval = pow(2,10)
while interval < interval_max:
    br_num = min_num
    while br_num < max_num:
        res_time.append(float(lines[pos])/(br_num+1)*freq)
        br_num  = ITLB_capacity.br_num_inc(br_num)
        # print(res_time[pos])
        pos = pos + 1
    interval = ITLB_capacity.interval_inc(interval)

output_file = open("output.csv","w")
csv_writer = csv.writer(output_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
csv_writer.writerow([' ','4096'])

loop_size = int(pos/column_num)
br_num = min_num
for i in range(0,loop_size):
    row_content = []
    row_content.append(br_num)
    for j in range(0,column_num):
        row_content.append(res_time[i+j*loop_size])
    csv_writer.writerow(row_content)
    br_num  = ITLB_capacity.br_num_inc(br_num)