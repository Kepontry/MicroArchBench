import os
import sys
import csv
import math

class Ifetch:
    def generate_header(num):
        header_file = open("test.h", "w")
        if(num < 1024 * 16):
            header_file.write(" #define REPEAT 500000LL \n")
        elif (num < 1024 * 256):
            header_file.write(" #define REPEAT 100000LL \n")
        elif (num < 1024 * 1024):
            header_file.write(" #define REPEAT 10000LL \n")
        else:
           header_file.write(" #define REPEAT 1000LL \n")
        header_file.write(" #define TEST_LOOP ")
        header_file.write("asm( \\\n")
        for i in range(0,num):
            # header_file.write("\"mov $0, %%r9\\n\\t\" \\\n")
            # header_file.write("\"mov $0, %%ax\\n\\t\" \\\n")
            # header_file.write("\"mov %%r8, %%rdx\\n\\t\" \\\n")
            header_file.write("\".long 0x00401f0f\\n\\t\" \\\n")
            # header_file.write("\"nop\\n\\t\" \\\n")
            # header_file.write("\"nop\\n\\t\" \\\n")
            # header_file.write("\"nop\\n\\t\" \\\n")
            # header_file.write("\"nop\\n\\t\" \\\n")
        header_file.write(" : \\\n : \\\n :\"rdx\");\n ")

    # def nop_num_inc(cur_num):
    #     if cur_num == 0:
    #         return 8
    #     nxt_num = 0
    #     tmp = int(math.log2(cur_num))
    #     nxt_num = pow(2,tmp) / 4
    #     return cur_num + int(nxt_num)
    
    def nop_num_inc(cur_num):
        if cur_num == 0:
            return 8
        nxt_num = 0
        tmp = int(math.log2(cur_num))
        nxt_num = pow(2,tmp) / 4
        return cur_num + int(nxt_num)

## test code

# run test
min_num = int(1024/4)
max_num = pow(2,22)

print("\n>>>>> Running Instruction Fetch Test")
nop_num = min_num
while nop_num < max_num:
    # print("------------ generate code ------------")
    Ifetch.generate_header(nop_num)
    # print("------------ compile code ------------")
    command = "gcc test.c -o test"
    os.system(command)
    # print("------------ run test ------------")
    command = "./test >> res.txt"
    ret = os.system(command)
    # print("------------ control ------------")
    # print(nop_num)
    nop_num  = Ifetch.nop_num_inc(nop_num)
    # print("nop_num: ",nop_num,"interval: ",interval)

# collect data
res_file = open("res.txt","r")
res_time = []
lines = res_file.readlines()
pos = 0

freq = float(sys.argv[1])
nop_num = min_num
while nop_num < max_num:
    if(nop_num == 0):
        res_time.append(0)
    else:
        res_time.append(nop_num/float(lines[pos])/freq)
    nop_num  = Ifetch.nop_num_inc(nop_num)
    pos = pos + 1

output_file = open("output.csv","w")
csv_writer = csv.writer(output_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

loop_size = int(pos)
nop_num = min_num
for i in range(0,loop_size):
    row_content = []
    row_content.append(nop_num*4/1024)
    row_content.append(res_time[i])
    csv_writer.writerow(row_content)
    nop_num  = Ifetch.nop_num_inc(nop_num)