#include <stdlib.h>
#include "BST.h"

RBTree* rb_createTree(int (*compKey) (const void*, const void*), 
                      void (*destKey) (void*), 
                      void (*destData) (void*)) {
    RBTree* newTree = (RBTree*) malloc(sizeof(RBTree));
    newTree->compKey = compKey;
    newTree->destKey = destKey;
    newTree->destData = destData;

    return newTree;
}

RBNode* rb_treeInsert(RBTree* tree, void* key, void* data) {
}

void rb_treePrint(RBTree* tree) {
}

void rb_delete(RBTree* tree, RBNode* node) {
}

void rb_treeDestroy(RBTree* tree) {
}

RBNode* rb_treePredecessor(RBTree* tree, RBNode* node) {
}

RBNode* rb_treeSuccessor(RBTree* tree, RBNode* node) {
}

RBNode* rb_exactQuery(RBTree* tree, void* key) {
}

void* rb_enumerate(RBTree* tree, void* low, void* high) {
}

void rb_nullFunction(void* data) {
}

void leftRotate(RBTree* tree, RBNode* node) {
    RBNode* tmp = node->right;
    node->right = tmp->left;

    if (tmp->left != NULL) tmp->left->parent = node;

    tmp->parent = node->parent;
    if (node == node->parent->left) {
        node->parent->left = tmp;
    } else {
        node->parent->right = tmp;
    }

    tmp->left = node;
    node->parent = tmp;
}

void rightRotate(RBTree* tree, RBNode* node) {
    RBNode* tmp;
    node->left = tmp->right;

    if (tmp->right != NULL) tmp->right->parent = node;

    tmp->parent = node->parent;
    if (node == node->parent->left) {
        node->parent->left = tmp;
    } else {
        node->parent->right = tmp;
    }

    tmp->right = node;
    node->parent = tmp;
}

