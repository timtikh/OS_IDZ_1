gcc reader4.c -o reader4.o
gcc process4.c -o process4.o
gcc writer4.c -o writer4.o
gcc manager4.c -o manager4.o

./manager4.o tests/test1.txt tests/test1_res.txt
./manager4.o tests/test2.txt tests/test2_res.txt
./manager4.o tests/test3.txt tests/test3_res.txt
./manager4.o tests/test4.txt tests/test4_res.txt
./manager4.o tests/test5.txt tests/test5_res.txt
