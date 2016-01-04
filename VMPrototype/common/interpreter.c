#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "data_structures.h"
#include "util.h"
#include "interpreter.h"
#include "view_node.h"
#include "platform/native.h"

#ifdef __ANDROID__
#include <android/log.h>
#endif

#define LOG_TAG "Jiff"

#ifdef _ANDROID_LOG_H
#define LOG(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##__VA_ARGS__)
#else
#define LOG(fmt, ...) printf(fmt"\n", ##__VA_ARGS__)
#endif

void runProgramCode(const char* contents, int fileSize) {
//    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "Hey hey hey!!!!!!!!!!!!!!!!");
    LOG("Hey hey hey!!!!!!!!!!!!!!!!");
    LOG("Hey hey hey!!!!!!!!!!!!!!!! | %d", 1234);
    LOG("Hey hey hey!!!!!!!!!!!!!!!! | fileSize = %d", fileSize);
    Stack* stack = NULL;
    STI* views = NULL;

    long ptr = 0;
    while (1) {
        if (ptr >= fileSize)
            break;

        OpCode code = contents[ptr++];
        LOG("OpCode = %d | ptr = %d | V_CREATE = %d", code, ptr, V_CREATE);
        switch (code) {
            case LIT_INT:
            {
                Value* val = (Value*) malloc(sizeof(Value));
                memcpy(val, &contents[ptr], 4);
                ptr += 4;
                LOG("val = 0x%08x", val);
                stackPush(&stack, val);
                LOG("LIT_INT = %d | hex = 0x%08x", val->i, val->i);
                break;
            }
            case LIT_BYTE:
            {
                Value* val = (Value*) malloc(sizeof(Value));
                memcpy(val, &contents[ptr], 1);
                ptr += 1;
                LOG("LIT_BYTE | val = 0x%08x", val);
                stackPush(&stack, val);
                break;
            }
            case LIT_FLOAT:
            {
                Value* val = (Value*) malloc(sizeof(Value));
                memcpy(val, &contents[ptr], 4);
                ptr += 4;
                stackPush(&stack, val);
                break;
            }
            case LIT_STRING:
            {
                int size;
                memcpy(&size, &contents[ptr], 4);
                ptr += 4;
                Value* val = (Value*) malloc(sizeof(Value));
                val->str = (char*)malloc(sizeof(char) * (size + 1));
                val->str[size] = '\0';
                memcpy(val->str, &contents[ptr], size);
                ptr += size;
                stackPush(&stack, val);
                break;
            }
            case V_CREATE:
            {
                Value* typeVal = stackPop(&stack);
                Value* idVal = stackPop(&stack);

                char type = typeVal->c;
                int id = idVal->i;

                free(typeVal);
                free(idVal);

                ViewNode* vn = (ViewNode*) malloc(sizeof(ViewNode));
                memset(vn, 0, sizeof(ViewNode));
                vn->id = id;
                vn->type = type;
                LOG("Did this get the property id? | id = 0x%08x | vn = 0x%08x | type = %d", vn->id, vn, vn->type);
                views = stiPut(views, vn->id, vn);

                switch (type) {
                    case RELATIVE:
                        LOG("Creating a relative stub obj! | id = %x\n", id);
                        break;
                    case VIEW:
                        LOG("Creating a view stub obj! | id = %x\n", id);
                        break;
                    case IMAGE:
                        LOG("Creating a image stub obj! | id = %x\n", id);
                        break;
                }

                //  TODO: Put stub into a temp map?
                //        This could be pushed to the stack if the next command
                //        is add child or passed as part of create with a
                //        parent id (nullable for root)
                break;
            }
            case V_SET_CHILD:
            {
                Value* childVal = stackPop(&stack);
                Value* parentVal = stackPop(&stack);

                int idChild = childVal->i;
                int idParent = parentVal->i;

                free(childVal);
                free(parentVal);

                LOG("ids | idChild = 0x%08x | idParent = 0x%08x", idChild, idParent);
                STI* childNode = stiFind(views, idChild);
                STI* parentNode = stiFind(views, idParent);

                LOG("foundNodes | childNode = 0x%08x | parentNode = 0x%08x", childNode, parentNode);
                ViewNode* child = (ViewNode*) childNode->data;
                ViewNode* parent = (ViewNode*) parentNode->data;

                LOG("Found Children | child = 0x%08x | parent = 0x%08x", child, parent);
                llAddItem(&parent->children, child);

                LOG("Add child(0x%x) to parent(0x%x)\n", idChild, idParent);
                break;
            }

            case V_SET_BACKGROUND_COLOR:
            {
                LOG("Works?");
                Value* colorVal = stackPop(&stack);
                Value* idVal = stackPop(&stack);

                int color = colorVal->i;
                int id = idVal->i;

                STI* node = stiFind(views, id);
                ViewNode* vn = (ViewNode*) node->data;

                vn->bgColor = color;

                LOG("Set background color of view(0x%x) to color = 0x%08x\n", id, color);
                break;
            }

            case V_SET_REL:
            {
                Value* relVal = stackPop(&stack);
                Value* v2Val = stackPop(&stack);
                Value* v1Val = stackPop(&stack);

                int rel = relVal->i;
                int v2 = v2Val->i;
                int v1 = v1Val->i;

                free(relVal);
                free(v2Val);
                free(v1Val);

                STI* v1Node = stiFind(views, v1);

                ViewNode* v1View = (ViewNode*) v1Node->data;

                Relationship* relation = (Relationship*) malloc(sizeof(Relationship));
                relation->relationship = rel;
                relation->otherID = v2;

                llAddItem(&v1View->relationships, relation);

                LOG("Set relationship between v1(0x%x) and v2(0x%x) to %d\n", v1, v2, rel);
                break;
            }

            case V_SET_MARGIN:
            {
                Value* bottomVal = stackPop(&stack);
                Value* rightVal = stackPop(&stack);
                Value* topVal = stackPop(&stack);
                Value* leftVal = stackPop(&stack);
                Value* viewVal = stackPop(&stack);

                int bottom = bottomVal->i;
                int right = rightVal->i;
                int top = topVal->i;
                int left = leftVal->i;
                int view = viewVal->i;

                free(bottomVal);
                free(rightVal);
                free(topVal);
                free(leftVal);
                free(viewVal);

                STI* viewNode = stiFind(views, view);

                ViewNode* vn = (ViewNode*) viewNode->data;

                vn->margins.left = left;
                vn->margins.top = top;
                vn->margins.right = right;
                vn->margins.bottom = bottom;

                LOG("Set margins of view(0x%x) to { %d, %d, %d, %d }\n", view, left, top, right, bottom);
                break;
            }

            case V_SET_DIMEN:
            {
                Value* heightVal = stackPop(&stack);
                Value* widthVal = stackPop(&stack);
                Value* viewVal = stackPop(&stack);

                int height = heightVal->i;
                int width = widthVal->i;
                int view = viewVal->i;

                free(heightVal);
                free(widthVal);
                free(viewVal);

                STI* viewNode = stiFind(views, view);

                ViewNode* vn = (ViewNode*) viewNode->data;

                vn->width = width;
                vn->height = height;

                LOG("Set dimensions of view(0x%x) to { %d, %d }\n", view, width, height);
                break;
            }

            case A_SET_CONTENT:
            {
                Value* viewVal = stackPop(&stack);

                int view = viewVal->i;

                free(viewVal);

                STI* viewNode = stiFind(views, view);

                ViewNode* vn = (ViewNode*) viewNode->data;

                sendViewToNative(vn);

                freeViewNode(vn);
                stiRelease(views);
                views = NULL;

                LOG("Set the content view of the current activity to %d\n", view);
                break;
            }

            case S_PRINT:
            {
                Value* val = stackPop(&stack);

                LOG("Hey.  I'm printing here! | str = %s\n", val->str);
                free(val->str);
                free(val);
                break;
            }
        }
    }

    LOG("-----------CLEARING STACK!!-----------\n");
    while (stack) {
        Value* val = stackPop(&stack);
        LOG("pop! | val = %lx\n", val->l);
        free(val);
    }
    LOG("-----------DONE CLEARING STACK!!-----------\n");
}


