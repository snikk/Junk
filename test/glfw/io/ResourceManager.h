#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include "../drawing/Texture.h"
#include "TextureCache.h"

class ResourceManager {
public:
    static Texture getTexture(const char* name);
private:
    static TextureCache textureCache;
};

#endif
