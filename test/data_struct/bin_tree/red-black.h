#ifndef __red_black_h__
#define __red_black_h__

typedef struct _RBNode {
    void* data;
    struct _RBNode* left;
    struct _RBNode* right;
    struct _RBNode* parent;
} RBNode;

typedef struct _RBTree {
    RBNode* root;
    int (*comp)(RBNode*, RBNode*);
} RBTree;

int compare_func(RBNode* left, RBNode* right);

void rb_add(RBNode** root);

#endif
