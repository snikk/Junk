#include "IOManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char* IOManager::readFile(const char* filename) {
    long size;
    return IOManager::readFile(filename, &size);
}

char* IOManager::readFile(const char* filename, long* size) {
    struct stat fileStat;
    stat(filename, &fileStat);
    printf("---------------------------------------------\n");
    printf("Stats for %s:\n", filename);
    printf("    access   = %li\n", fileStat.st_atime);
    printf("    modified = %li\n", fileStat.st_mtime);
    printf("    status   = %li\n", fileStat.st_ctime);
    printf("    filesize = %lli\n", fileStat.st_size);
    

    FILE* fp = fopen(filename, "rb");

    if (!fp) {
        printf("Error reading file | %s\n", filename);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    *size = ftell(fp);
    printf("    filesize (seek) = %li\n", *size);
    printf("---------------------------------------------\n");
    fseek(fp, 0, SEEK_SET);

    if (*size == 0) {
        printf("Error reading size!\n");
        fclose(fp);
    }
    
    *size = *size + 1;
    char* str = (char*) malloc(sizeof(char) * *size);

    memset(str, 0, *size);

    fread(str, 1, *size, fp);

    fclose(fp);

    return str;
}

