#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 5000
// As S_IFIFO doesn't work we have to make temporary fifos
#define FIRST_FIFO "/tmp/first-fifo"
#define SECOND_FIFO "/tmp/second-fifo"

int main(int argc, char *argv[])
{

    printf("\n\nStarting program for ASCII vowels converting for 5\n");
    // Naming canals
    const char *pipe_1 = "pipe1.fifo";
    const char *pipe_2 = "pipe2.fifo";
    // Checking if arguments in terminal are enough for work - must be input and output file names
    if (argc < 3)
    {
        printf("Error: not enough arguments. Please, enter input and output file names\n");
        exit(1);
    }
    // Receiving names of input and output files
    char *input_file = argv[1];
    char *output_file = argv[2];
    // opening input
    int in_fd = open(input_file, O_RDONLY);
    if (in_fd == -1)
    {
        perror("open");
        exit(1);
    }

    // opening output file
    int out_fd = open(output_file, O_WRONLY | O_CREAT, 0666);
    if (out_fd == -1)
    {
        perror("open");
        exit(1);
    }

    // Init and start of named channels
    if (mkfifo(FIRST_FIFO, 0666) < 0)
    {
        perror("mkfifo first fifo");
        exit(1);
    }
    if (mkfifo(SECOND_FIFO, 0666) < 0)
    {
        perror("mkfifo second fifo");
        exit(1);
    }

    int fd_first_read;
    int fd_first_write;
    int fd_second_read;
    int fd_second_write;
    pid_t pid_first, pid_second, pid_third;
    int status;

    // Starting ?son/daughter/child? processes
    pid_first = fork();
    if (pid_first == -1)
    {
        perror("fork");
        exit(1);
    }
    else if (pid_first == 0)
    {
        // First child process reading file
        printf("Child process #1 with id: %d with parent id: %d\n", (int)getpid(), (int)getppid());
        char buffer[BUF_SIZE];
        ssize_t read_bytes = read(in_fd, buffer, BUF_SIZE);
        if (read_bytes == -1)
        {
            perror("read");
            exit(1);
        }
        buffer[read_bytes] = '\0';

        // Opening first channel to write
        if ((fd_first_write = open(FIRST_FIFO, O_WRONLY)) == -1)
        {
            perror("open fifo_first_write");
            exit(1);
        }

        // Writing data into fifo first
        if (write(fd_first_write, buffer, read_bytes) == -1)
        {
            perror("write");
            exit(1);
        }

        // Closing channel
        if (close(fd_first_write) < 0)
        {
            perror("close");
            exit(1);
        }

        printf("Copied data to buffer from input file\n");
        printf("%s\n\n", buffer);

        exit(0);
    }

    pid_second = fork();
    if (pid_second == -1)
    {
        perror("fork");
        exit(1);
    }
    else if (pid_second == 0)
    {
        // Second child process making the magic (ASCII change)
        printf("Child process #2 with id: %d with parent id: %d\n", (int)getpid(), (int)getppid());

        if ((fd_first_read = open(FIRST_FIFO, O_RDONLY)) == -1)
        {
            perror("open fifo_first_read");
            exit(1);
        }

        // Reading data from first canal
        char buffer[BUF_SIZE];
        char outword[BUF_SIZE];
        ssize_t read_bytes = read(fd_first_read, buffer, BUF_SIZE);
        if (read_bytes == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buffer[read_bytes] = '\0';

        if (close(fd_first_read) < 0)
        {
            perror("close fifo_first_read");
            exit(1);
        }

        // Changing to hexedecimal ASCII
        int temp = 0;
        for (int i = 0; i < read_bytes; i++)
        {
            if (buffer[i] == 'a' || buffer[i] == 'e' || buffer[i] == 'i' || buffer[i] == 'o' || buffer[i] == 'u' || buffer[i] == 'A' || buffer[i] == 'E' || buffer[i] == 'I' || buffer[i] == 'O' || buffer[i] == 'U')
            {
                sprintf(outword + i + temp, "0x%02X ", buffer[i]);
                temp += 4;
            }
            else
            {
                sprintf(outword + i + temp, "%c ", buffer[i]);
                temp++;
            }
        }
        read_bytes = strlen(outword);
        printf("Final length: %ld \n", read_bytes);

        // Transferring data into second channel
        if ((fd_second_write = open(SECOND_FIFO, O_WRONLY)) == -1)
        {
            perror("open fifo_second_write");
            exit(1);
        }
        if (write(fd_second_write, outword, read_bytes) == -1)
        {
            perror("write");
            exit(1);
        }

        if (close(fd_second_write) < 0)
        {
            perror("close fifo_second_write");
            exit(1);
        }
        printf("result: %s \n", outword);

        exit(0);
    }

    pid_third = fork();
    if (pid_third == -1)
    {
        perror("fork");
        exit(1);
    }
    else if (pid_third == 0)
    {
        // Writing data into output file
        printf("Child process #3 with id: %d with parent id: %d\n", (int)getpid(), (int)getppid());

        if ((fd_second_read = open(SECOND_FIFO, O_RDONLY)) == -1)
        {
            perror("open fifo_second_read");
            exit(1);
        }

        // Reading second channel data
        char buffer[BUF_SIZE];
        ssize_t read_bytes = read(fd_second_read, buffer, BUF_SIZE);
        if (read_bytes == -1)
        {
            perror("read");
            exit(1);
        }
        buffer[read_bytes] = '\0';
        if (close(fd_second_read) < 0)
        {
            perror("close fifo_second_read");
            exit(1);
        }

        // writing outword in export file
        if (write(out_fd, buffer, read_bytes) == -1)
        {
            perror("write");
            exit(1);
        }

        exit(0);
    }

    // Closing named chanels and finishing file work
    if (close(fd_first_read) < 0)
    {
        perror("close");
        exit(-1);
    }
    if (close(fd_first_write) < 0)
    {
        perror("close");
        exit(-1);
    }
    if (close(fd_second_read) < 0)
    {
        perror("close");
        exit(-1);
    }
    if (close(fd_second_write) < 0)
    {
        perror("close");
        exit(-1);
    }
    if (close(in_fd) < 0)
    {
        perror("close");
        exit(-1);
    }
    if (close(out_fd) < 0)
    {
        perror("close");
        exit(-1);
    }
    if (unlink(FIRST_FIFO) == -1)
    {
        perror("Error deleting named channel");
        exit(1);
    }
    if (unlink(SECOND_FIFO) == -1)
    {
        perror("Error deleting named channel");
        exit(1);
    }
    waitpid(pid_first, &status, 0);
    waitpid(pid_second, &status, 0);
    waitpid(pid_third, &status, 0);

    exit(0);
}
