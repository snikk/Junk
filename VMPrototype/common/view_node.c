#include <stddef.h>
#include "view_node.h"
#include <stdlib.h>

void freeViewNode(ViewNode* now) {
    if (now->children != NULL) {
        LL* curr = now->children;
        while (curr != NULL) {
            freeViewNode(curr->data);
            curr = curr->n;
        }

        llDeleteLinkedList(&now->children);
    }
    if (now->relationships != NULL) {
        LL* curr = now->relationships;
        while (curr != NULL) {
            free(curr->data);
            curr = curr->n;
        }

        llDeleteLinkedList(&now->relationships);
    }

    free(now);
}