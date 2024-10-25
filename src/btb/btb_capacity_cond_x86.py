import os
import sys
import csv
import math

class BTB_capacity:
    def generate_header(num,dense):
        header_file = open("test.h", "w")
        if(num < 1024):
            header_file.write(" #define REPEAT 10000LL \n")
        elif(num < 1024 * 4):
            header_file.write(" #define REPEAT 1000LL \n")
        else:
            header_file.write(" #define REPEAT 500LL \n")
        header_file.write(" #define TEST_LOOP ")
        header_file.write("asm(\\\n")
        header_file.write("\"xor %%ecx, %%ecx \\r\\n\\t\" \\\n")
        header_file.write("\".align 256 \\r\\n\\t\" \\\n")
        header_file.write("\"2: \\n\\t\" \\\n")
        for i in range(0,num):
            header_file.write("\"1: jrcxz 1f\\n\\t\" \\\n")
            header_file.write("\".word 0x9066\\n\\t\" \\\n")
            for j in range(0,dense):
                header_file.write("\".long 0x00401f0f\\n\\t\" \\\n")
                # if(dense > 1): header_file.write("\".long 0x001f0f\\n\\t\" \\\n")
                # else         : header_file.write("\".long 0x001f0f\\n\\t\" \\\n")
        header_file.write("\"1: \" \\\n")
        header_file.write("\"dec %0 \\n\\t\" \\\n")
        header_file.write("\"jne 2b \\n\\t\" \\\n")
        header_file.write(" : \\\n :\"r\"(repeat) \\\n :);\n ")

    # def br_num_inc(cur_num):
    #     return cur_num + 1
    def br_num_inc(cur_num):
        if cur_num == 1 :
            nxt_num = cur_num + 15
        else:
            nxt_num = cur_num + 16
        # elif cur_num < 1024 :
        #     nxt_num = cur_num + 8
        # else:
        #     nxt_num = cur_num + 32
        return nxt_num
    
    def interval_inc(cur_num):
        nxt_num = 0
        tmp = math.log2(cur_num + 1)
        nxt_num = pow(2,tmp + 1)
        return int(nxt_num) - 1

## test code

# run test
min_num = 0
max_num = 1024 * 1
interval_max = pow(2,4)
interval = 0
column_num = 0

# for interval in intervals :
print("\n>>>>> Running BTB Capacity Test")
while interval < interval_max:
    br_num = min_num
    print("BTB test running interval:"+str(interval))
    pos = 0
    while br_num < max_num:
        # print("------------ generate code ------------")
        BTB_capacity.generate_header(br_num,interval)

        # print("------------ compile code ------------")
        command = "gcc test_x86.c -o test"
        # command = "xmake --build btb_test"
        os.system(command)

        # print("------------ run test ------------")
        command = "./test >> res.txt"
        os.system(command)

        # print("------------ control ------------")
        br_num  = BTB_capacity.br_num_inc(br_num)
        # print("br_num: ",br_num,"interval: ",interval)
    column_num = column_num + 1
    interval = BTB_capacity.interval_inc(interval)

# collect data
freq = float(sys.argv[1])
res_file = open("res.txt","r")
res_time = []
lines = res_file.readlines()
pos = 0
interval = 0
while interval < interval_max:
    br_num = min_num
    while br_num < max_num:
        res_time.append(float(lines[pos])/(br_num+1)*freq)
        br_num  = BTB_capacity.br_num_inc(br_num)
        # print(res_time[pos])
        pos = pos + 1
    interval = BTB_capacity.interval_inc(interval)

output_file = open("output.csv","w")
csv_writer = csv.writer(output_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
csv_writer.writerow([' ','4', '8', '16', '32', '64', '128', '256'])

loop_size = int(pos/column_num)
br_num = min_num
for i in range(0,loop_size):
    row_content = []
    row_content.append(br_num)
    for j in range(0,column_num):
        row_content.append(res_time[i+j*loop_size])
    csv_writer.writerow(row_content)
    br_num  = BTB_capacity.br_num_inc(br_num)