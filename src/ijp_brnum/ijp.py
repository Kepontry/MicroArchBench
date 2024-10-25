
tmp = open("test.h", "w")
tmp.write(" #define TWO ")
for i in range(0,2):
    if(i  == 0):
        tmp.write(f"if(pattern[i]) a[{i}] = foo_func0; \\\n")
    else:
        tmp.write(f"if(pattern[(i+16*{i})%MAXHIS]) a[{i}] = foo_func0; \\\n")
    tmp.write(f"else           a[{i}] = foo_func1; \\\n")
    tmp.write(f"a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define FOUR ")
for i in range(0,4):
    if(i  == 0):
        tmp.write(f"if(pattern[i]) a[{i}] = foo_func0; \\\n")
    else:
        tmp.write(f"if(pattern[(i+16*{i})%MAXHIS]) a[{i}] = foo_func0; \\\n")
    tmp.write(f"else           a[{i}] = foo_func1; \\\n")
    tmp.write(f"a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define EIGHT ")
for i in range(0,8):
    if(i  == 0):
        tmp.write(f"if(pattern[i]) a[{i}] = foo_func0; \\\n")
    else:
        tmp.write(f"if(pattern[(i+16*{i})%MAXHIS]) a[{i}] = foo_func0; \\\n")
    tmp.write(f"else           a[{i}] = foo_func1; \\\n")
    tmp.write(f"a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define SIXTEEN ")
for i in range(0,16):
    if(i  == 0):
        tmp.write(f"if(pattern[i]) a[{i}] = foo_func0; \\\n")
    else:
        tmp.write(f"if(pattern[(i+16*{i})%MAXHIS]) a[{i}] = foo_func0; \\\n")
    tmp.write(f"else           a[{i}] = foo_func1; \\\n")
    tmp.write(f"a[{i}](); \\\n")
tmp.write("\n")  

tmp.write(" #define THIRTYTWO ")
for i in range(0,32):
    if(i  == 0):
        tmp.write(f"if(pattern[i]) a[{i}] = foo_func0; \\\n")
    else:
        tmp.write(f"if(pattern[(i+16*{i})%MAXHIS]) a[{i}] = foo_func0; \\\n")
    tmp.write(f"else           a[{i}] = foo_func1; \\\n")
    tmp.write(f"a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define SIXTYFOUR ")
for i in range(0,64):
    if(i  == 0):
        tmp.write(f"if(pattern[i]) a[{i}] = foo_func0; \\\n")
    else:
        tmp.write(f"if(pattern[(i+16*{i})%MAXHIS]) a[{i}] = foo_func0; \\\n")
    tmp.write(f"else           a[{i}] = foo_func1; \\\n")
    tmp.write(f"a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define HUNDRED ")
for i in range(0,128):
    if(i  == 0):
        tmp.write(f"if(pattern[i]) a[{i}] = foo_func0; \\\n")
    else:
        tmp.write(f"if(pattern[(i+16*{i})%MAXHIS]) a[{i}] = foo_func0; \\\n")
    tmp.write(f"else           a[{i}] = foo_func1; \\\n")
    tmp.write(f"a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define THUNDRED ")
for i in range(0,256):
    if(i  == 0):
        tmp.write(f"if(pattern[i]) a[{i}] = foo_func0; \\\n")
    else:
        tmp.write(f"if(pattern[(i+16*{i})%MAXHIS]) a[{i}] = foo_func0; \\\n")
    tmp.write(f"else           a[{i}] = foo_func1; \\\n")
    tmp.write(f"a[{i}](); \\\n")
tmp.write("\n")

tmp.write(" #define FHUNDRED ")
for i in range(0,512):
    if(i  == 0):
        tmp.write(f"if(pattern[i]) a[{i}] = foo_func0; \\\n")
    else:
        tmp.write(f"if(pattern[(i+16*{i})%MAXHIS]) a[{i}] = foo_func0; \\\n")
    tmp.write(f"else           a[{i}] = foo_func1; \\\n")
    tmp.write(f"a[{i}](); \\\n")
tmp.write("\n")