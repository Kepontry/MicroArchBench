rm test
# python3 bp_arm.py
echo ">>>>> Running Branch Prediction Test"
gcc test.c -o bp_test
# echo "---------- test start ----------"
./bp_test > res.txt
# echo "---------- analysis start ----------"
# objdump -D test > test.S
