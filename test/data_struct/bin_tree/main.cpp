#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _Node {
    void* data;
    struct _Node* left;
    struct _Node* right;
} Node;

void printNode(Node* n);

int main(int argc, char** argv) {
    printf("Hello World!\n");

    Node n1;
    Node n2;
    Node n3;

    printf("size of Node obj ptr = %lu\n", sizeof(&n1));
    printf("size of Node obj = %lu\n", sizeof(Node));
    printf("size of int ptr = %lu\n", sizeof(int*));
    printf("size of char ptr = %lu\n", sizeof(char*));

    memset(&n1, 0, sizeof(Node));
    memset(&n2, 0, sizeof(Node));
    memset(&n3, 0, sizeof(Node));

    int one = 1;
    int two = 2;
    int three = 3;

    n1.data = &one;
    n2.data = &two;
    n3.data = &three;

    n1.left = &n2;
    n2.right = &n3;

    printNode(&n1);

    return 0;
}

void printNode(Node* n) {
    printf("Node ptr = %d | data ptr = %d | data = %d\n", n, n->data, *(int*)(n->data));
    if (n->left != NULL)
        printNode(n->left);
    if (n->right != NULL)
        printNode(n->right);
}
