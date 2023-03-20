#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv) {

    char buffer[5000];
    for (int i = 0; i < 5000; i++) {
        buffer[i] = '@';
    }
    int stream = open(argv[1], O_RDONLY);
    ssize_t fromfile = read(stream, buffer, 5000);
    close(stream);
    write(6, buffer, fromfile);
    exit(0);
}
