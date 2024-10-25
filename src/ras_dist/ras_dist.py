import os
import sys
import csv
import math

class RAS_capacity:
    def generate_header(depth):
        tmp = open("test.h", "w")
        for i in range(0,depth):
            if(i == depth -1):
                tmp.write("int foo_func(int a){\n")
            else:
                tmp.write("int foo_func"+str(i)+"(int a){\n")

            if(i == 0): tmp.write(";\n")
            else:
                tmp.write("foo_func"+str(i-1)+"(a);\n")
                tmp.write("a ++;\n")
            tmp.write("return a;}\n")
        tmp.write("\n")

    def br_num_inc(cur_num):
        return cur_num + 1
    def interval_inc(cur_num):
        return cur_num + 1

# run test
min_num = 1
max_num = 128
interval_max = 1
interval = 0
column_num = 0

# for interval in intervals :
print("\n>>>>> Running RAS(Dist) Capacity Test")
while interval < interval_max:
    br_num = min_num
    # print("RAS test running interval:"+str(interval))
    pos = 0
    while br_num < max_num:
        # print("------------ generate code ------------")
        RAS_capacity.generate_header(br_num)

        # print("------------ compile code ------------")
        command = "gcc test.c -o ras_dist_test"
        # command = "xmake --build btb_test"
        os.system(command)

        # print("------------ run test ------------")
        command = "./ras_dist_test >> res.txt"
        os.system(command)

        # print("------------ control ------------")
        br_num  = RAS_capacity.br_num_inc(br_num)
        # print("br_num: ",br_num,"interval: ",interval)
    column_num = column_num + 1
    interval = RAS_capacity.interval_inc(interval)

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
        res_time.append(float(lines[pos])/(br_num)*freq)
        br_num  = RAS_capacity.br_num_inc(br_num)
        # print(res_time[pos])
        pos = pos + 1
    interval = RAS_capacity.interval_inc(interval)

output_file = open("output.res","w")
csv_writer = csv.writer(output_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

loop_size = int(pos/column_num)
br_num = min_num
for i in range(0,loop_size):
    row_content = []
    for j in range(0,column_num):
        row_content.append(res_time[i+j*loop_size])
    csv_writer.writerow(row_content)
    br_num  = RAS_capacity.br_num_inc(br_num)