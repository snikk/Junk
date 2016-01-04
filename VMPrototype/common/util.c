#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* readFile(const char* filename, long* size) {
    FILE* fp = fopen(filename, "rb");

    if (!fp) {
        printf("Error reading file | %s\n", filename);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    *size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (*size == 0) {
        printf("Error reading size!\n");
        return NULL;
    }
    
    *size = *size + 1;
    char* str = (char*) malloc(sizeof(char) * *size);

    memset(str, 0, *size);

    fread(str, 1, *size, fp);

    fclose(fp);

    return str;
}

LL* splitOnChar(char* str, char ch) {
    LL* ll = NULL;
    
    long curr = 0;
    long prev = 0;
    while (str[curr] != '\0') {
        while (str[curr] != '\0' && str[curr] != ch) {
            if (str[curr] == '"') {
                while (str[++curr] != '"') {}
            }
                        
            curr++;
        }
        if (str[curr] == '\0' && str[prev] == '\0')
            break;


        int size = curr - prev;
        printf("splitOnChar | curr = %d | prev = %d\n", curr, prev);
        if (size > 0) {
            char* copy = (char*) malloc(sizeof(char) * (size + 1));
            copy[size] = '\0';
            memcpy(copy, &str[prev], size);
            printf("splitOnChar | copy = \"%s\"\n", copy);
            llAddItem(&ll, copy);
        }

        prev = curr;
        while (str[curr] == ch) {
            curr++;
            prev++;
        }
    }

    return ll;
}

extern int getNewID() {
    static int currID = 0x7FF00000;

    return currID++;
}
