
tmp = open("test.h", "w")
for i in range(0,512):
    tmp.write("void foo_func"+str(i)+"(){;}\n")
tmp.write("\n")

tmp.write(" #define ASSIGN ")
for i in range(0,512):
    tmp.write(f"tgt[{i}] = foo_func{i};\\\n")
tmp.write("\n")

tmp.write(" #define TWO ")
for i in range(0,2):
    if(i  == 0):
        tmp.write(f"a[{i}] = tgt[pattern[i]]; a[{i}](); \\\n")
    else:
        tmp.write(f"a[{i}] = tgt[pattern[(i+16*{i})%MAXHIS]]; a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define FOUR ")
for i in range(0,4):
    if(i  == 0):
        tmp.write(f"a[{i}] = tgt[pattern[i]]; a[{i}](); \\\n")
    else:
        tmp.write(f"a[{i}] = tgt[pattern[(i+16*{i})%MAXHIS]]; a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define EIGHT ")
for i in range(0,8):
    if(i  == 0):
        tmp.write(f"a[{i}] = tgt[pattern[i]]; a[{i}](); \\\n")
    else:
        tmp.write(f"a[{i}] = tgt[pattern[(i+16*{i})%MAXHIS]]; a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define SIXTEEN ")
for i in range(0,16):
    if(i  == 0):
        tmp.write(f"a[{i}] = tgt[pattern[i]]; a[{i}](); \\\n")
    else:
        tmp.write(f"a[{i}] = tgt[pattern[(i+16*{i})%MAXHIS]]; a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define THIRTYTWO ")
for i in range(0,32):
    if(i  == 0):
        tmp.write(f"a[{i}] = tgt[pattern[i]]; a[{i}](); \\\n")
    else:
        tmp.write(f"a[{i}] = tgt[pattern[(i+16*{i})%MAXHIS]]; a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define SIXTYFOUR ")
for i in range(0,64):
    if(i  == 0):
        tmp.write(f"a[{i}] = tgt[pattern[i]]; a[{i}](); \\\n")
    else:
        tmp.write(f"a[{i}] = tgt[pattern[(i+16*{i})%MAXHIS]]; a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define HUNDRED ")
for i in range(0,128):
    if(i  == 0):
        tmp.write(f"a[{i}] = tgt[pattern[i]]; a[{i}](); \\\n")
    else:
        tmp.write(f"a[{i}] = tgt[pattern[(i+16*{i})%MAXHIS]]; a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define THUNDRED ")
for i in range(0,256):
    if(i  == 0):
        tmp.write(f"a[{i}] = tgt[pattern[i]]; a[{i}](); \\\n")
    else:
        tmp.write(f"a[{i}] = tgt[pattern[(i+16*{i})%MAXHIS]]; a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define FHUNDRED ")
for i in range(0,512):
    if(i  == 0):
        tmp.write(f"a[{i}] = tgt[pattern[i]]; a[{i}](); \\\n")
    else:
        tmp.write(f"a[{i}] = tgt[pattern[(i+16*{i})%MAXHIS]]; a[{i}](); \\\n")
tmp.write("\n")