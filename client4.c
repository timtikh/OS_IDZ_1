#include <stdio.h>
#include <string.h>

int main() {
    char string[100];
    printf("Введите строку: ");
    fgets(string, 100, stdin);
    char letters[52] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";

    for (int i = 0; i < strlen(string); i++) {
        for (int j = 0; j < strlen(letters); j++) {
            if (string[i] == letters[j]) {
                int ascii = string[i];
                printf("0x%X ", ascii);
                break;
            } 
        }        
    }

    return 0;
}
