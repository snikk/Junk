#include <stdio.h>
#include "mylib.h"

extern void myFunction(int param1, int param2) {
    printf("Multiplication! | result = %d\n", param1 * param2);
}

extern int anotherFunction() {
    return 123;
}

