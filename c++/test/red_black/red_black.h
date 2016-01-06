#ifndef __RED_BLACK_H__
#define __RED_BLACK_H__

typedef struct RBNode {
    void* key;
    void* data;
    bool red;
    struct RBNode* parent;
    struct RBNode* left;
    struct RBNode* right;
} RBNode;

typedef struct RBTree {
} RBTree;

#endif
