#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "red-black.h"

typedef struct _Node {
    void* data;
    struct _Node* left;
    struct _Node* right;
} Node;

void printNode(Node* n);
int treeHeight(Node* n);

int main(int argc, char** argv) {
    printf("Hello World!\n");

    Node n1;
    Node n2;
    Node n3;
    Node n4;
    Node n5;
    Node n6;
    Node n7;
    Node n8;
    Node n9;
    Node n10;

    RBNode* rbN1;
    RBNode* rbN2;
    RBNode* rbN3;

    rb_add(&rbN1);

    printf("size of Node obj ptr = %lu\n", sizeof(&n1));
    printf("size of Node obj = %lu\n", sizeof(Node));
    printf("size of RBNode obj = %lu\n", sizeof(RBNode));
    printf("size of int ptr = %lu\n", sizeof(int*));
    printf("size of char ptr = %lu\n", sizeof(char*));

    memset(&n1, 0, sizeof(Node));
    memset(&n2, 0, sizeof(Node));
    memset(&n3, 0, sizeof(Node));
    memset(&n4, 0, sizeof(Node));
    memset(&n5, 0, sizeof(Node));
    memset(&n6, 0, sizeof(Node));
    memset(&n7, 0, sizeof(Node));
    memset(&n8, 0, sizeof(Node));
    memset(&n9, 0, sizeof(Node));
    memset(&n10, 0, sizeof(Node));

    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    int five = 5;
    int six = 6;
    int seven = 7;
    int eight = 8;
    int nine = 9;
    int ten = 10;

    n1.data = &one;
    n2.data = &two;
    n3.data = &three;
    n4.data = &four;
    n5.data = &five;
    n6.data = &six;
    n7.data = &seven;
    n8.data = &eight;
    n9.data = &nine;
    n10.data = &ten;

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;
    n3.left = &n6;
    n3.right = &n7;
    n4.left = &n8;
    n4.right = &n9;
    n5.left = &n10;

    printNode(&n1);

    int height = treeHeight(&n1);
    printf("Tree height = %d\n", height);

    return 0;
}

void printNode(Node* n) {
    int height = treeHeight(n);
    int totalWidth = height * height * 3;

    char* fmt = (char*) malloc(sizeof(char) * 10);
    memset(fmt, 0, 10);
    printf("Str = %s", fmt);
    printf("\n\n");
    snprintf(fmt, 10, "%%%dd", totalWidth / 2 + 4);
    //fmt[0] = '%';
    printf("%s", fmt);
    printf("\n\n");
    printf(fmt, *(int*)(n->data));
    printf("\n\n");
    free(fmt);
    printf("Node ptr = %d | data ptr = %d | data = %d\n", n, n->data, *(int*)(n->data));

    for (int i = 0; i < height; i++) {
    }
    /*
    if (n->left != NULL)
        printNode(n->left);
    if (n->right != NULL)
        printNode(n->right);
        */
}

int treeHeight(Node* n) {
    if (n == NULL) {
        return 0;
    }

    int left = treeHeight(n->left);
    int right = treeHeight(n->right);

    return (left > right ? left : right) + 1;
}
