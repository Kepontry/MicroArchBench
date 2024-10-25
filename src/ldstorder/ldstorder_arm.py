import os
import csv
import math

class Ldstorder:
    def generate_header(num,dense):
        header_file = open("test.h", "w")
        header_file.write(" #define REPEAT 10000LL \n")
        header_file.write(" #define TEST_LOOP ")
        header_file.write("asm( \\\n")
        header_file.write("\"2: \" \\\n")
        for i in range(0,num):
            header_file.write("\"str %1, [%2]\\n\\t\" \\\n")
            header_file.write("\"ldr %2, [%1]\\n\\t\" \\\n")
            for j in range(0,dense):
                header_file.write("\"nop \\n\\t\" \\\n")
        header_file.write("\"subs %0, %0, #1 \\n\\t\" \\\n")
        header_file.write("\"b.ne 2b \\n\\t\" \\\n")
        header_file.write(" : \\\n : \"r\"(repeat), \"r\"(pointer0), \"r\"(pointer1) \\\n :);\n ")

    def ld_num_inc(cur_num):
        return cur_num + 1
    
    def interval_inc(cur_num):
        nxt_num = 0
        tmp = math.log2(cur_num + 1)
        nxt_num = pow(2,tmp + 1)
        return int(nxt_num) - 1

## test code

# run test
min_num = 0
max_num = 256
interval_max = pow(2,0)
interval = 0
column_num = 0

# for interval in intervals :
while interval < interval_max:
    ld_num = min_num
    while ld_num < max_num:
        # print("------------ generate code ------------")
        Ldstorder.generate_header(ld_num,interval)

        # print("------------ compile code ------------")
        command = "gcc test.c -o test"
        os.system(command)

        # print("------------ run test ------------")
        command = "./test >> res.txt"
        ret = os.system(command)

        # command = "objdump -D test > test.S"
        # ret = os.system(command)

        # print("------------ control ------------")
        ld_num  = Ldstorder.ld_num_inc(ld_num)
        # print("ld_num: ",ld_num,"interval: ",interval)
    column_num = column_num + 1
    interval = Ldstorder.interval_inc(interval)

# collect data
res_file = open("res.txt","r")
res_time = []
lines = res_file.readlines()
pos = 0
interval = 0
while interval < interval_max:
    ld_num = min_num
    while ld_num < max_num:
        if(ld_num == 0):
            res_time.append(0)
        else:
            res_time.append(float(lines[pos])/ld_num)
        ld_num  = Ldstorder.ld_num_inc(ld_num)
        pos = pos + 1
    interval = Ldstorder.interval_inc(interval)

output_file = open("output.csv","w")
csv_writer = csv.writer(output_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
legend = ['']
for i in range(0,column_num):
    legend.append(f"{i}")
csv_writer.writerow(legend)

loop_size = int(pos/column_num)
ld_num = min_num
for i in range(0,loop_size):
    row_content = []
    row_content.append(ld_num)
    for j in range(0,column_num):
        row_content.append(res_time[i+j*loop_size])
    csv_writer.writerow(row_content)
    ld_num  = Ldstorder.ld_num_inc(ld_num)