#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    char* str = "This is my string!";
    printf("str = %s\n", str);
    for (int i = 0; i < 100; i++) {
        int sz = strlen(str);
        char* copy = (char*) malloc(sizeof(char) * sz);
        memcpy(copy, str, sz);
        copy[sz] = '\0';
        printf("sz = %d | copy = %s\n", sz, copy);
        copy[3] = '\0';
        free(copy);
    }
    return 0;
}
