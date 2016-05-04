#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct my_struct {
    int myInt;
    float myFloat;
    char* myChar;
    void (*testFunc)(struct my_struct*);
} MyStruct;

void myFunc(MyStruct* st) {
    printf("IMMA IN UR CALL MAKING MAH CALL!\n");
    printf("This object! | int = %d | float = %f | string = %s\n", st->myInt, st->myFloat, st->myChar);
}

void test(char** ptr) {
    char *copyStr = "This is my string.";
    int len = strlen(copyStr);
    *ptr = malloc(len);
    memset(*ptr, 0, len);
    strcpy(*ptr, copyStr);
}

void anotherTest(MyStruct** st) {
    *st = malloc(sizeof(MyStruct));
    memset(*st, 0, sizeof(MyStruct));
    (*st)->myInt = 123;
    (*st)->myFloat = 123.456;
    test(&((*st)->myChar));
    (*st)->testFunc = myFunc;
}

int main(int argc, char** argv) {
    printf("Hey there.  World.\n");

    char* myString;
    test(&myString);

    printf("Did this alloc alright? | myString = %s\n", myString);

    free(myString);

    MyStruct *st;

    anotherTest(&st);

    st->testFunc(st);

    free(st);

    return 0;
}
