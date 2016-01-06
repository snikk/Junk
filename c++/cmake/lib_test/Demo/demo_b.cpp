#include "demo_b.h"
#include <stdio.h>

extern void localFunction(int myInt) {
    printf("Here is the local function | myInt = %d\n", myInt);
}
