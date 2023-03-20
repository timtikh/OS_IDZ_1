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
    char buffer[20000];
    ssize_t from_reader = read(10, buffer, 20000);

    int stream = open(argv[2], O_WRONLY);

    int w_stream = write(stream, buffer, from_reader);
    close(stream);
    exit(0);
}
