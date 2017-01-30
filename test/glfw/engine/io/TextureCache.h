#ifndef __TEXTURE_CACHE_H__
#define __TEXTURE_CACHE_H__

#include <map>
#include "../drawing/Texture.h"
#include "../common.h"
#include "../util/Util.h"
#include <iostream>

class TextureCache {
public:
    Texture getTexture(const char* texturePath);
    FontTexture* getFontTexture(Font* f);

private:
    std::map<const char*, Texture, cmp_str> textureMap;
};

#endif
