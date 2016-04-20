#ifndef __UTIL_H__
#define __UTIL_H__

#include <cmath>

#define CHK_ERR(msg) checkError(msg, __FILE__, __LINE__)

extern void checkError(const char* msg);
extern void checkError(const char* msg, const char* file, int line);

inline float distance(float x, float y) {
    return sqrtf(x * x + y * y);
}

inline float distance(float x1, float y1, float x2, float y2) {
    return distance(x2 - x1, y2 - y1);
}

inline float lerp(float start, float end, float per) {
    return (end - start) * per + start;
}

#endif

