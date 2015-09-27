#include "TextureCache.h"
#include "ImageLoader.h"

Texture TextureCache::getTexture(const char* texturePath) {

    //lookup the texture and see if its in the map
    auto mit = textureMap.find(texturePath);

    //check if its not in the map
    if (mit == textureMap.end()) {
        //Load the texture
        Texture newTexture = ImageLoader::loadPNG(texturePath);

        //Insert it into the map
        textureMap.insert(std::make_pair(texturePath, newTexture));

        return newTexture;
    }
    return mit->second;
}
