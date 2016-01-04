#ifndef __UTIL_H__
#define __UTIL_H__

#include "data_structures.h"

extern char* readFile(const char* filename, long* size);
extern LL* splitOnChar(char* str, char ch);
extern int getNewID();

#endif
