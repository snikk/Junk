#ifndef __VIEW_NODE_H__
#define __VIEW_NODE_H__

#include "data_structures.h"

#ifdef __APPLE__
#include <MacTypes.h>
#endif

#ifndef __MACTYPES__
typedef struct _Rect {
    int top;
    int left;
    int right;
    int bottom;
} Rect;
#endif

typedef struct _Relationship {
    int otherID;
    int relationship;
} Relationship;

typedef struct _ViewNode {
    int id;
    LL* children;
    Rect margins;
    int width;
    int height;
    int bgColor;
    int type;
    LL* relationships;
} ViewNode;

extern void freeViewNode(ViewNode* now);

#endif
