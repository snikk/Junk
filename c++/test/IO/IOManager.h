#ifndef __IOManager_h__
#define __IOManager_h__

#include <vector>

namespace B201 {

    class IOManager
    {
    public:
        static bool readFileToBuffer(std::string filePath, const char** buffer);
    };
}

#endif
