#include "TextureCache.h"
#include "ImageLoader.h"
#include "../drawing/Font.h"

typedef int bool;
#define true 1
#define false 0

void swap(int *i1, int *i2) {
    int tmp = *i2;
    *i2 = *i1;
    *i1 = tmp;
}

void sort(int *index, Pos *positions, int size) {
    for (int i = 1; i < size; i++) {
        for (int j = i; j > 0; j--) {
            if (positions[index[j]].height > positions[index[j - 1]].height) {
                swap(&index[j], &index[j - 1]);
            } else {
                break;
            }
        }
    }
}

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

FontTexture* TextureCache::getFontTexture(Font* f) {
    auto it = textureMap.find(f->name);

    if (it == textureMap.end()) {
        FontTexture* tex = (FontTexture*) malloc(sizeof(FontTexture);;
        tex.font = f;
        int size = f->chEnd - f->chStart;
        int indices[size];
        Pos positions[size];

        int sz = 32;
        unsigned char **final;

        for (int i = f->chStart; i < f->chEnd; i++) {
            if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
                printf("Couldn't load the character.\n");
                return NULL;
            }

            FT_GlyphSlot g = face->glyph;

            int idx = i - start;
            indices[idx] = idx;
            positions[idx].width = g->bitmap.width;
            positions[idx].height = g->bitmap.rows;
        }

        sort(indices, positions, size);

        int firstInCurrent;
        int sz = 32;
        bool fit = false;

        while (!fit) {
            fit = true;
            sz *= 2;
            positions[indices[0]].u = 0;
            positions[indices[0]].v = 0;
            firstInCurrent = indices[0];
            for (int i = 1; i < size; i++) {
                int newX = positions[indices[i - 1]].u + positions[indices[i - 1]].width + 1;
                if (newX + positions[indices[i]].width >= sz) {
                    positions[indices[i]].v = positions[firstInCurrent].v + positions[firstInCurrent].height + 1;
                    if (positions[indices[i]].v + positions[indices[i]].height >= sz) {
                        fit = false;
                        break;
                    }
                    positions[indices[i]].u = 0;
                    firstInCurrent = indices[i];
                } else {
                    positions[indices[i]].u = newX;
                    positions[indices[i]].v = positions[firstInCurrent].v;
                }
            }
        }

        glGenTextures(1, &tex.id);
        checkError("Gen Texture!");
        glActiveTexture(GL_TEXTURE0);
        checkError("Active Texture!");
        glBindTexture(GL_TEXTURE_2D, tex.id);
        checkError("Bind Texture!");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        checkError("Tex Image 2D!");

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        checkError("Param Wrap S!");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        checkError("Param Wrap T!");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        checkError("Parma Mag!");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        checkError("Param Min!");

        glGenerateMipmap(GL_TEXTURE_2D);
        checkError("Generate Mipmap!");
    }

    return it->second;
}
