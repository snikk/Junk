#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <commands.h>
#include <data_structures.h>
#include <util.h>

int getId() {
    static int CURRENT_ID = 0x7FF00000;
    return CURRENT_ID++;
}

int getView(ST** tree, char* name) {
    ST* node = stFind(*tree, name);
    if (node == NULL) {
        int id = getId();
        *tree = stPut(*tree, name, id);
        printf("getView() | name = %s | node = 0x%08x | id = 0x%08x\n", name, node, id);
        return id;
    }

    printf("getView() | name = %s | node = 0x%08x | id = 0x%08x\n", name, node, node->data);
    return node->data;
}

void addInt(FILE* fd, int i);
void addInt(FILE* fd, char* str) {
    int i = strtol(str, NULL, 0);
    addInt(fd, i);
}

void addInt(FILE* fd, int i) {
    int localI = i;
    char litInt = LIT_INT;
    fwrite(&litInt, sizeof(litInt), 1, fd);
    fwrite(&localI, sizeof(localI), 1, fd);
}

void addChar(FILE* fd, char c) {
    char litByte = LIT_BYTE;
    printf("Hey.  Printing char\n");
    printf("Hey.  Printing char = %d\n", c);
    fwrite(&litByte, sizeof(litByte), 1, fd);
    fwrite(&c, sizeof(c), 1, fd);
}

void addString(FILE* fd, char* str) {
    int size = strlen(str) - 2;
    char litString = LIT_STRING;
    fwrite(&litString, sizeof(litString), 1, fd);
    fwrite(&size, sizeof(size), 1, fd);
    fwrite(&str[1], sizeof(char), size, fd);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Need to pass a file and an output\n");
        return -1;
    }

    FILE* out = fopen(argv[2], "w+b");
    if (out == NULL) {
        printf("Problem opening the output file.\n");
        return -1;
    }

    ST* tree;

    long size;
    char* contents = readFile(argv[1], &size);
    LL* commands = splitOnChar(contents, '\n');
    LL* currentCommand = commands;

    while (currentCommand) {
        printf("currentCommand = %s\n", (char*)currentCommand->data);
        LL* components = splitOnChar((char*) currentCommand->data, ' ');
        LL* currComps = components;
        while (currComps) {
            printf("comp = %s\n", (char*)currComps->data);
            char code = getOpCode((char*)currComps->data);
            currComps = currComps->n;

            switch (code) {
                case V_CREATE: {
                    addInt(out, getView(&tree, (char*)currComps->data));
                    currComps = currComps->n;
                    addChar(out, getConstant((char*)currComps->data));
                    currComps = currComps->n;

                    fwrite(&code, sizeof(code), 1, out);
                    break;
                }
                case V_SET_CHILD: {
                    int id1 = getView(&tree, (char*)currComps->data);
                    currComps = currComps->n;
                    int id2 = getView(&tree, (char*)currComps->data);
                    currComps = currComps->n;

                    addInt(out, id1);
                    addInt(out, id2);
                    fwrite(&code, sizeof(code), 1, out);
                    break;
                }
                case V_SET_BACKGROUND_COLOR: {
                    addInt(out, getView(&tree, (char*)currComps->data));
                    currComps = currComps->n;
                    addInt(out, (char*)currComps->data);
                    currComps = currComps->n;
                    
                    fwrite(&code, sizeof(code), 1, out);
                    break;
                }
                case V_SET_MARGIN: {
                    addInt(out, getView(&tree, (char*)currComps->data));
                    currComps = currComps->n;
                    addInt(out, (char*)currComps->data);
                    currComps = currComps->n;
                    addInt(out, (char*)currComps->data);
                    currComps = currComps->n;
                    addInt(out, (char*)currComps->data);
                    currComps = currComps->n;
                    addInt(out, (char*)currComps->data);
                    currComps = currComps->n;
                    
                    fwrite(&code, sizeof(code), 1, out);
                    break;
                }
                case V_SET_REL: {
                    addInt(out, getView(&tree, (char*)currComps->data));
                    currComps = currComps->n;
                    addInt(out, getView(&tree, (char*)currComps->data));
                    currComps = currComps->n;
                    addInt(out, (int) getConstant((char*)currComps->data));
                    currComps = currComps->n;
                    
                    fwrite(&code, sizeof(code), 1, out);
                    break;
                }
                case A_SET_CONTENT: {
                    addInt(out, getView(&tree, (char*)currComps->data));
                    currComps = currComps->n;
                    
                    fwrite(&code, sizeof(code), 1, out);
                    break;
                }
                case V_SET_DIMEN: {
                    addInt(out, getView(&tree, (char*)currComps->data));
                    currComps = currComps->n;
                    addInt(out, (char*)currComps->data);
                    currComps = currComps->n;
                    addInt(out, (char*)currComps->data);
                    currComps = currComps->n;
                    
                    fwrite(&code, sizeof(code), 1, out);
                    break;
                }
                case S_PRINT: {
                    addString(out, (char*)currComps->data);
                    currComps = currComps->n;

                    fwrite(&code, sizeof(code), 1, out);
                    break;
                }
            }
        }

        currComps = components;
        while (currComps != NULL) {
            free(currComps->data);
            currComps = currComps->n;
        }
        free(components);
        currentCommand = currentCommand->n;
    }

    stRelease(tree);

    while (currentCommand) {
        free(currentCommand->data);
        currentCommand = currentCommand->n;
    }
    llDeleteLinkedList(&commands);
    free(contents);
}

