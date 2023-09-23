gcc 7-process.c -o 7-process
rm /tmp/first-fifo & rm /tmp/second-fifo
./7-process tests/test1.txt tests/test1_res.txt
rm /tmp/first-fifo & rm /tmp/second-fifo
./7-process tests/test2.txt tests/test2_res.txt
rm /tmp/first-fifo & rm /tmp/second-fifo
./7-process tests/test3.txt tests/test3_res.txt
rm /tmp/first-fifo & rm /tmp/second-fifo
./7-process tests/test4.txt tests/test4_res.txt
rm /tmp/first-fifo & rm /tmp/second-fifo
./7-process tests/test5.txt tests/test5_res.txt
