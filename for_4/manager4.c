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
    int fd_1[2], fd_2[2];
    pipe(fd_1);
    pipe(fd_2);
    for (int i = 0; i < 2; ++i) {
        dup2(fd_1[i], i + 5);
        dup2(fd_2[i], i + 10);
    }

    if (fork()) {
        execv("./reader4.o", argv);
    }
    if (fork()) {
        execv("./process4.o", argv);
    }
    if (fork()) {
        execv("./writer4.o", argv);
    }

    close(fd_1[0]);
    close(fd_1[1]);
    close(5);
    close(6);
    close(fd_2[0]);
    close(fd_2[1]);
    close(10);
    close(11);
    return 0;
    exit(0);

}

   