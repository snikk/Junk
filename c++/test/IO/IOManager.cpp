#include <iostream>
#include "IOManager.h"
#include <fstream>

namespace B201 {

    bool IOManager::readFileToBuffer(std::string filePath, const char** buffer) {
        FILE *fp;

        fp = fopen(filePath.c_str(), "rb");

        if (fp == nullptr)
            return false;

        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        printf("Size of file %s is = %ld\n", filePath.c_str(), size);

        *buffer = (char*) malloc(sizeof(unsigned char) * (size + 1));
        memset((void*)*buffer, 0, size + 1);
        if (*buffer == nullptr) {
            fclose(fp);
            return false;
        }

        fread((void*)*buffer, 1, size, fp);
        fclose(fp);

        return true;
    }
}
