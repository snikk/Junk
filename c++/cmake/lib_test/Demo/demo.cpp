#include <stdio.h>
#include <hello.h>
#include "demo_b.h"

int main(int argc, char** argv) {
    printf("Hello World!\n");

    localFunction(123);
    callingMyFunction(456);

    return 0;
}


