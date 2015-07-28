#ifndef __IOMANAGER_H__
#define __IOMANAGER_H__

class IOManager {
public:
    static char* readFile(const char* filename);
    static char* readFile(const char* filename, long* size);
};

#endif

