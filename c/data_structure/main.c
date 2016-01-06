#include <stdio.h>
#include "BST.h"

int comp(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

void destroyInt(void* i) {
    printf("Destroyed Key! | i = %d\n", *(int*)i);
}

void destroyData(void* d) {
    printf("Destroyed data! | d = %d\n", *(int*)d);
}

int main(int argc, char** argv) {
    printf("Hello, World!\n");

    RBTree* tree = rb_createTree(comp, destroyInt, destroyData);
    int first = 12;
    int second = 8;
    int res = tree->compKey(&first, &second);
    printf("first = %d | second = %d | res = %d\n", first, second, res);

    tree->destKey(&first);
    tree->destData(&second);

    return 0;
}
