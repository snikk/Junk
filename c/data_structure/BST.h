typedef struct RBNode {
    void* key;
    void* data;

    int red;

    struct RBNode* parent;
    struct RBNode* left;
    struct RBNode* right;
} RBNode;

typedef struct RBTree {
    int (*compKey) (const void*, const void*);
    void (*destKey) (void*);
    void (*destData) (void*);

    RBNode* root;
} RBTree;

RBTree* rb_createTree(int (*compKey) (const void*, const void*), 
                      void (*destKey) (void*), 
                      void (*destData) (void*));

RBNode* rb_treeInsert(RBTree*, void*, void*);
void rb_treePrint(RBTree*);
void rb_delete(RBTree*, RBNode*);
void rb_treeDestroy(RBTree*);
RBNode* rb_treePredecessor(RBTree*, RBNode*);
RBNode* rb_treeSuccessor(RBTree*, RBNode*);
RBNode* rb_exactQuery(RBTree*, void*);
void* rb_enumerate(RBTree*, void*, void*);
void rb_nullFunction(void*);
