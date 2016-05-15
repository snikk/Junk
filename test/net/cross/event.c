#include <stdio.h>
#include <stdlib.h>

typedef struct Test {
    int i;
    float f;
} Test;

void myFunc(Test* test, int* i) {
    test->i += *i;
    test->f *= (float) *i;
    (*i)++;
}

int main(int argc, char** argv) {
    printf("Hello, World.\n");

    int test = 1;
    Test t;
    t.i = 2;
    t.f = 1.234f;

    void (*func)(void*, void*) = myFunc;

    printf("t.i = %d | t.f = %f | test = %d.\n", t.i, t.f, test);
    func(&t, &test);
    printf("t.i = %d | t.f = %f | test = %d.\n", t.i, t.f, test);
    func(&t, &test);
    printf("t.i = %d | t.f = %f | test = %d.\n", t.i, t.f, test);
    func(&t, &test);
    printf("t.i = %d | t.f = %f | test = %d.\n", t.i, t.f, test);
    func(&t, &test);
    printf("t.i = %d | t.f = %f | test = %d.\n", t.i, t.f, test);
    func(&t, &test);
    printf("t.i = %d | t.f = %f | test = %d.\n", t.i, t.f, test);


    return 0;
}
