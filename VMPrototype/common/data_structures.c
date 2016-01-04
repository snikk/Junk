#include "data_structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <android/log.h>

//////////////////////////////////////////////////
//      int Symbol table
//////////////////////////////////////////////////
STI* stiNewNode(int key, void* data) {
    STI* newNode = (STI*) malloc(sizeof(STI));
    newNode->key = key;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

STI* stiFindMin(STI* root) {
    if (root == NULL) return root;
    while (root->left != NULL)
        root = root->left;
    return root;
}

STI* stiFindMax(STI* root) {
    if (root == NULL) return root;
    while (root->right != NULL)
        root = root->right;
    return root;
}

STI* stiFind(STI* root, int key) {
    if (root == NULL) return root;
    else if (key < root->key) return stiFind(root->left, key);
    else if (key > root->key) return stiFind(root->right, key);
    else return root;
}

STI* stiDelete(STI* root, int key) {
    if (root == NULL) return root;
    else if (key < root->key) root = stiDelete(root->left, key);
    else if (key > root->key) root = stiDelete(root->right, key);
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } else if (root->left == NULL) {
            STI* temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            STI* temp = root;
            root = root->left;
            free(temp);
        } else {
            STI* temp = stiFindMin(root->right);
            root->key = temp->key;
            root->data = temp->data;
            root->right = stiDelete(root->right, temp->key);
        }
    }

    return root;
}

void stiRelease(STI* root) {
    if (root == NULL) return;
    stiRelease(root->left);
    stiRelease(root->right);
    free(root);
}

STI* stiPut(STI* root, int key, void* data) {
//    __android_log_print(ANDROID_LOG_DEBUG, "Jiff", "stiPut | root = 0x%08x | key = %d | 0x%08x", root, key, data);

    if (root == NULL) {
        root = stiNewNode(key, data);
        return root;
    }
    if (key < root->key) root->left = stiPut(root->left, key, data);
    else if (key > root->key) root->right = stiPut(root->right, key, data);
    else {
        root->data = data;
        root->key = key;
    }
    return root;
}

void stiPrint(STI* root, char* (*printFunc)(void*)) {
    if (root == NULL) return;

    stiPrint(root->left, printFunc);
    printf("node[%d] = %s\n", root->key, printFunc(root->data));
    stiPrint(root->right, printFunc);
}

//////////////////////////////////////////////////
//      Char* Symbol table
//////////////////////////////////////////////////
ST* stNewNode(char* key, int data) {
    ST* newNode = (ST*) malloc(sizeof(ST));
    newNode->key = key;
    int size = strlen(key);
    newNode->key = (char*)malloc(sizeof(char) * size);
    memcpy(newNode->key, key, size);
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

ST* stFindMin(ST* root) {
    if (root == NULL) return root;
    while (root->left != NULL)
        root = root->left;
    return root;
}

ST* stFindMax(ST* root) {
    if (root == NULL) return root;
    while (root->right != NULL)
        root = root->right;
    return root;
}

ST* stFind(ST* root, char* key) {
    if (root == NULL) return root;
    else if (strcmp(key, root->key) < 0) return stFind(root->left, key);
    else if (strcmp(key, root->key) > 0) return stFind(root->right, key);
    else return root;
}

ST* stDelete(ST* root, char* key) {
    if (root == NULL) return root;
    else if (strcmp(key, root->key) < 0) root = stDelete(root->left, key);
    else if (strcmp(key, root->key) > 0) root = stDelete(root->right, key);
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } else if (root->left == NULL) {
            ST* temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            ST* temp = root;
            root = root->left;
            free(temp);
        } else {
            ST* temp = stFindMin(root->right);
            root->key = temp->key;
            root->data = temp->data;
            root->right = stDelete(root->right, temp->key);
        }
    }

    return root;
}

void stRelease(ST* root) {
    if (root == NULL) return;
    stRelease(root->left);
    stRelease(root->right);
    free(root->key);
    free(root);
}

ST* stPut(ST* root, char* key, int data) {
    if (root == NULL) {
        root = stNewNode(key, data);
        return root;
    }
    if (strcmp(key, root->key) < 0) root->left = stPut(root->left, key, data);
    else if (strcmp(key, root->key) > 0) root->right = stPut(root->right, key, data);
    else {
        free(root->key);
        root->data = data;
        int size = strlen(key);
        root->key = (char*)malloc(sizeof(char) * size);
        memcpy(root->key, key, size);
    }
    return root;
}

void stPrint(ST* root) {
    if (root == NULL) return;

    if (root->left != NULL) stPrint(root->left);
    printf("node[%s] = %d\n", root->key, root->data);
    if (root->right != NULL) stPrint(root->right);
}

void llDeleteLinkedList(LL** list) {
    while (*list) {
        LL* next = (*list)->n;
        free(*list);
        *list = next;
    }
}

void llAddItem(LL** list, void* item) {
    LL* newNode = (LL*) malloc(sizeof(LL));
    memset(newNode, 0, sizeof(LL));
    newNode->data = item;
    LL* tail = *list;
    if (tail != NULL) {
        while (tail->n != NULL)
            tail = tail->n;
        tail->n = newNode;
    } else {
        *list = newNode;
    }
}

int llCount(LL** list) {
    if (*list == NULL)
        return 0;
    int count = 0;
    LL* curr = *list;
    while (curr != NULL) {
        curr = curr->n;
        count++;
    }

    return count;
}

void stackPush(Stack** stack, Value* val) {
    Stack* node = (Stack*)malloc(sizeof(Stack));
    node->n = *stack;
    node->data = val;
    *stack = node;
}

Value* stackPop(Stack** stack) {
    Stack* tmp = *stack;
    Value* ret = tmp->data;
    *stack = tmp->n;
    free(tmp);
    return ret;
}

