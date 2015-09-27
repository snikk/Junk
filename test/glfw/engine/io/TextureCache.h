#ifndef __TEXTURE_CACHE_H__
#define __TEXTURE_CACHE_H__

#include <map>
#include "../drawing/Texture.h"
#include "../common.h"
#include <iostream>

struct cmp_str {
    bool operator()(const char* lhs, const char* rhs) const {
        return strcmp(lhs, rhs) < 0;
    }
};

class TextureCache {
public:
    Texture getTexture(const char* texturePath);

private:
    std::map<const char*, Texture, cmp_str> textureMap;
};

#endif
