#include <stdio.h>
#include "mylib.h"

int main(int argc, char** argv) {
    printf("Hello world!\n");

    myFunction(123, 456);
    printf("Result! = %d\n", anotherFunction());

    return 0;
}
