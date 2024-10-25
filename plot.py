
import os
from pathlib import Path

print("------------ Env preparation ------------")
# Setup running environment.
# ./res for readable results; ./res/log for intermediate outputs
# Clear results from last run first
res_file = Path("./res")

# Test BTB
command = "python3 ./script/btb_figure.py"
os.system(command)

# Test ITLB
command = "python3 ./script/itlb_figure.py"
os.system(command)

# Test cache latency
command = "python3 ./script/cachelatency_figure_tmp.py"
os.system(command)

# Test memory bandwidth

# Test load-store forwarding
command = "python3 ./script/ldstforward_figure.py"
os.system(command)

# Test load-store order violation predictor
command = "python3 ./script/ldstorder_figure.py"
os.system(command)

# Test branch predictor (conditional)
command = "python3 ./script/bp_figure_heatmap.py"
os.system(command)

# Test indirect branch predictor(Br num)
command = "python3 ./script/ijp_figure_heatmap.py"
os.system(command)

# Test indirect branch predictor(Br num) New: avoiding conditional branches in main loops
command = "python3 ./script/ijp_new_figure_heatmap.py"
os.system(command)

# Test indirect branch predictor(Tgt num)
command = "python3 ./script/ijp_tgt_figure_heatmap.py"
os.system(command)

# Test indirect branch predictor(Tgt num) New: Adding conditional branches in main loops
command = "python3 ./script/ijp_tgt_new_figure_heatmap.py"
os.system(command)

# Test return address stack
command = "python3 ./script/ras_figure.py"
os.system(command)

# Test return address stack with distinct functions
command = "python3 ./script/ras_dist_figure.py"
os.system(command)

# Test instruction fetch
command = "python3 ./script/ifetch_figure.py"
os.system(command)

# Test core-to-core latency
command = "python3 ./script/c2clatency_figure.py"
os.system(command)

# Test memory level paralelism
command = "python3 ./script/mlp_figure.py"
os.system(command)

# Test Queue Capacity
command = "python3 ./script/robcap_figure.py"
os.system(command)

command = "python3 ./script/xprfcap_figure.py"
os.system(command)

command = "python3 ./script/cprfcap_figure.py"
os.system(command)

command = "python3 ./script/fprfcap_figure.py"
os.system(command)

command = "python3 ./script/ldqcap_figure.py"
os.system(command)

command = "python3 ./script/stqcap_figure.py"
os.system(command)

command = "python3 ./script/xiscap_figure.py"
os.system(command)

command = "python3 ./script/xciscap_figure.py"
os.system(command)

command = "python3 ./script/fiscap_figure.py"
os.system(command)

command = "python3 ./script/ldiscap_figure.py"
os.system(command)