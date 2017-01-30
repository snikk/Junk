#ifndef __FONT_H__
#define __FONT_H__

#include <ft2build.h>
#include FT_FREETYPE_H
#include "../util/Util.h"

class FontManager;

typedef struct Font {
public:
    char* name;

    int chStart;
    int chEnd;

    FT_Face face;

    friend class FontManager;
} Font;

class FontManager {
public:
    static FontManager& instance() {
        static FontManager manager;
        return manager;
    }

    int init() {
        int error = FT_Init_FreeType(&library);
        if (error) {
            printf("Hey there... an error occured. | error = %d\n", error);
            return 1;
        }

        return 0;
    }


    Font* getFont(const char* name, int size) {
        auto it = fonts.find(name);

        if (it == fonts.end()) {
            Font* f = (Font*) malloc(sizeof(Font));
            f->chStart = 32;
            f->chEnd = 127;

            f->name = strdup(name);

            if (FT_New_Face(library, name, 0, &f->face)) {
                printf("Couldn't open da font!\n");
                return NULL;
            }

            FT_Set_Pixel_Sizes(f->face, 0, size);

            fonts.insert(std::make_pair(name, f));

            return f;
        }

        return it->second;
    }

    void deleteFont(const char* name) {
        auto it = fonts.find(name);

        if (it != fonts.end()) {
            free(it->second);
            fonts.erase(name);
        }
    }

private:
    FT_Library library;

    FontManager();
    ~FontManager();
    FontManager(FontManager const&) = delete;
    void operator=(FontManager const&) = delete;

    std::map<const char*, Font*, cmp_str> fonts;
};

#endif
