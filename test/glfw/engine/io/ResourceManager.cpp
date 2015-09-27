#include "ResourceManager.h"

TextureCache ResourceManager::textureCache;

Texture ResourceManager::getTexture(const char* name) {
    return textureCache.getTexture(name);
}

