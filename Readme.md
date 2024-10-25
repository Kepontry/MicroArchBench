## Prerequest
    Xmake
    Matplotlib (pip install)
    Seaborn (pip install)

## Run
    python3 run.py
run.config decides which tests to run. 
```
intel_style

freq_test
#pipewidth_test
#instlantency_test
movelimination_test
ptchase_test
btbcapacity_test
itlbcapacity_test
```
To omit some tests, use "#" as above. \
Finally results will be in dir "res".

## Description
Using Xmake to automatically detect running platforms and compiling corresponding source codes. \
Using Matplotlib & Seaborn to generate figures. 


