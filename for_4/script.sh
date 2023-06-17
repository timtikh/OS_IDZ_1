gcc reader4.c -o reader4
gcc process4.c -o process4
gcc writer4.c -o writer4
gcc manager4.c -o manager4

./manager4 tests/test1.txt tests/test1_res.txt
./manager4 tests/test2.txt tests/test2_res.txt
./manager4 tests/test3.txt tests/test3_res.txt
./manager4 tests/test4.txt tests/test4_res.txt
./manager4 tests/test5.txt tests/test5_res.txt
