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
    
    int fd[2]; 
    ssize_t  size;
    char buffer[5000];
    char buffer2[20000];

    int stream = read(5, buffer, 5000);
    // printf("got from file: %s \n", buffer);                
    
    char letters[52] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";

    int cc = 0;
    for (int i = 0; i < 20000; i++) {
        buffer2[i] = ' ';
    }
    for (int i = 0; i < 5000; i++) {
        for (int j = 0; j < 52; j++) {
            if (buffer[i] != '@' && buffer[i] == letters[j]) {
                int n = buffer[i];
                char hex_val[12];
                // printf("number got: %c \n", n);     
                sprintf(hex_val, "0x%X ", n);
                if (hex_val[3]!='\0') {
                    buffer2[cc] = hex_val[0];
                    buffer2[cc+1] = hex_val[1];
                    buffer2[cc+2] = hex_val[2];
                    if (n>10){
                        buffer2[cc+3] = hex_val[3];
                        cc+=5;
                    } else {
                        cc+=4;
                    }
                    printf("%s ", hex_val);
                }
                
                
            } 
        }        
    }
    for (int i = 0; i < 19999; i++) {
        if (buffer2[i] == ' ' && buffer2[i+1] == ' '){
            buffer2[i] = '\0';
        }
    }
    printf("result: %s \n", buffer2);                

    size = write(11, buffer2, 20000);
    if (size > 0){printf("succes in giving data to writer");}
    exit(0);
}
