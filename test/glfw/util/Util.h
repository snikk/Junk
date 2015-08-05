#ifndef __UTIL_H__
#define __UTIL_H__

#define CHK_ERR(msg) checkError(msg, __FILE__, __LINE__)

extern void checkError(const char* msg);
extern void checkError(const char* msg, const char* file, int line);

#endif

