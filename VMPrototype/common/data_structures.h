#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

typedef struct LinkedList {
    void* data;
    struct LinkedList* n;
} LL;

typedef struct ST {
    char* key;
    int data;
    struct ST* left;
    struct ST* right;
} ST;

typedef struct STI {
    int key;
    void* data;
    struct STI* left;
    struct STI* right;
} STI;

typedef union _Value {
    char c;
    short s;
    int i;
    long l;
    float f;
    double d;
    char* str;
} Value;

typedef struct Stack {
    Value* data;
    struct Stack* n;
} Stack;

extern STI* stiNewNode(int key, void* data);
extern STI* stiFindMin(STI* root);
extern STI* stiFindMax(STI* root);
extern STI* stiFind(STI* root, int key);
extern STI* stiDelete(STI* root, int key);
extern void stiRelease(STI* root);
extern STI* stiPut(STI* root, int key, void* data);
extern void stiPrint(STI* root, char* (*printFunc)(void*));

extern ST* stNewNode(char* key, int data);
extern ST* stFindMin(ST* root);
extern ST* stFindMax(ST* root);
extern ST* stFind(ST* root, char* key);
extern ST* stDelete(ST* root, char* key);
extern void stRelease(ST* root);
extern ST* stPut(ST* root, char* key, int data);
extern void stPrint(ST* root);

extern void llDeleteLinkedList(LL** list);
extern void llAddItem(LL** list, void* item);
extern int llCount(LL** list);

extern void stackPush(Stack** stack, Value* val);
extern Value* stackPop(Stack** stack);

#endif
