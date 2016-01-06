#include <stdio.h>
#include <stdlib.h>

typedef struct _Value {
    union {
        char c;
        short s;
        int i;
        long l;
        float f;
        double d;
    } val;
    char type;
    int type2;
} Value;

int main(int argc, char** argv) {
    printf("Hey hey hey\n");

    Value value;
    value.val.l = 2344873928098;
    value.type = 1;
    value.type2 = 1;

    printf("value = %hd\n", value.val.s);
    printf("value = %d\n", (int) value.val.c);
    printf("value = %d\n", value.val.i);
    printf("value = %lu\n", value.val.l);
    printf("value = %f\n", value.val.f);
    printf("value = %f\n", value.val.d);

    printf("\n\n");
    char* data = (char*) &value;
    int size = sizeof(value);
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n\n");

    printf("Size of void* = %lu\n", sizeof(void*));

    return 0;
}

