echo ">>>>> Running Indirect Branch Prediction Test(Branch Num) New"
gcc -O2 ijp.c -o ijp_test
# echo "---------- test start ----------"
./ijp_test > res.txt
# echo "---------- analysis start ----------"
# objdump -D test > test.S