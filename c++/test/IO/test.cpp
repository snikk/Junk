#include <iostream>
#include <string>
#include "IOManager.h"

int main(int argc, char** argv) {
    std::cout << "Hello world!" << std::endl;
    const char *str;

    if (argc == 1) {
        str = "another.txt";
    } else {
        str = argv[1];
    }

    char *buf;
    if (B201::IOManager::readFileToBuffer(str, (const char**) &buf)) {
        std::cout << "Read the file with contents | " << buf << std::endl;
        printf("length of str = %lu\n", strlen(buf));
    } else {
        std::cout << "Error reading file!" << std::endl;
        printf("error with printf!\n");
    }

    return 0;
}
