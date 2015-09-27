#ifndef __IMAGE_LOADER_H__
#define __IMAGE_LOADER_H__

#include "../drawing/Texture.h"

class ImageLoader {
public:
    static Texture loadPNG(const char* name);
};

#endif
