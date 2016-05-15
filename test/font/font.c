#include <stdlib.h>
#include <stdio.h>

#include <ft2build.h>
#include FT_FREETYPE_H

typedef int bool;
#define true 1
#define false 0

typedef struct Pos {
    int x;
    int y;
    short width;
    short height;
} Pos;

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

void allocateFinal(unsigned char ***final, int size) {
    *final = malloc(sizeof(unsigned char*) * size);
    for (int i = 0; i < size; i++) {
        (*final)[i] = malloc(sizeof(unsigned char) * size);
        for (int j = 0; j < size; j++) {
            (*final)[i][j] = 0x99;
        }
    }
}

void freeFinal(unsigned char ***final, int size) {
    for (int i = 0; i < size; i++) {
        free((*final)[i]);
    }

    free(*final);
}

int main(int argc, char** argv) {
    printf("Rendering mah fontz\n");

    FT_Library library;

    int error = FT_Init_FreeType(&library);
    if (error) {
        printf("Hey there... an error occured. | error = %d\n", error);
        return 1;
    }

    FT_Face face;
    if (FT_New_Face(library, "courier_new.ttf", 0, &face)) {
        printf("Couldn't open da font!\n");
        return 1;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    int max = 127;
    int start = 32;
    int size = max - start;
    int *indices = malloc(sizeof(int) * size);
    Pos *positions = malloc(sizeof(Pos) * size);

    int sz = 32;
    unsigned char **final;

    for (int i = start; i < max; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            printf("Couldn't load the character.\n");
            return 1;
        }

        FT_GlyphSlot g = face->glyph;

        int idx = i - start;
        indices[idx] = idx;
        positions[idx].width = g->bitmap.width;
        positions[idx].height = g->bitmap.rows;

        printf("\n\n");

        for (int y = 0; y < g->bitmap.rows; y++) {
            for (int x = 0; x < g->bitmap.width; x++) {
                printf("%02x", g->bitmap.buffer[y * g->bitmap.width + x]);
            }
            printf("\n");
        }
    }

    sort(indices, positions, size);

    for (int i = 0; i < size; i++) {
        printf("%d | width = %d | height = %d\n", i, positions[indices[i]].width, positions[indices[i]].height);
    }

    for (int i = 0; i < size; i++) {
        if (FT_Load_Char(face, indices[i] + start, FT_LOAD_RENDER)) {
            printf("Couldn't load the character.\n");
            return 1;
        }

        FT_GlyphSlot g = face->glyph;

        printf("\n");

        for (int y = 0; y < g->bitmap.rows; y++) {
            for (int x = 0; x < g->bitmap.width; x++) {
                printf("%02x", g->bitmap.buffer[y * g->bitmap.width + x]);
            }
            printf("\n");
        }
    }

    allocateFinal(&final, sz);
    int firstInCurrent;
    bool fit = false;

    while (!fit) {
        fit = true;
        positions[indices[0]].x = 0;
        positions[indices[0]].y = 0;
        firstInCurrent = indices[0];
        for (int i = 1; i < size; i++) {
            int newX = positions[indices[i - 1]].x + positions[indices[i - 1]].width + 1;
            if (newX + positions[indices[i]].width >= sz) {
                positions[indices[i]].y = positions[firstInCurrent].y + positions[firstInCurrent].height + 1;
                if (positions[indices[i]].y + positions[indices[i]].height >= sz) {
                    fit = false;
                    printf("\n\nWoah there cowboy that didn't fit.\n\n");
                    break;
                }
                positions[indices[i]].x = 0;
                firstInCurrent = indices[i];
                printf("Fitting! | x = %d | y = %d\n", positions[indices[i]].x, positions[indices[i]].y);
            } else {
                positions[indices[i]].x = newX;
                positions[indices[i]].y = positions[firstInCurrent].y;
                printf("Fitting! | x = %d | y = %d\n", positions[indices[i]].x, positions[indices[i]].y);
            }

        }

        if (!fit) {
            freeFinal(&final, sz);
            sz *= 2;
            printf("Previous Size = %d | newSize = %d\n", sz / 2, sz);
            allocateFinal(&final, sz);
        }
    }

    printf("\n\n\n");

    for (int i = 0; i < size; i++) {
        if (FT_Load_Char(face, indices[i] + start, FT_LOAD_RENDER)) {
            printf("Couldn't load the character.\n");
            return 1;
        }

        FT_GlyphSlot g = face->glyph;

        /*
        for (int y = 0; y < g->bitmap.rows; y++) {
            for (int x = 0; x < g->bitmap.width; x++) {
                printf("%02x", g->bitmap.buffer[y * g->bitmap.width + x]);
            }
            printf("\n");
        }
        */
        printf("FINAL POSITION!! | x = %d | y = %d\n", positions[indices[i]].x, positions[indices[i]].y);

        for (int x = 0; x < positions[indices[i]].width; x++) {
            for (int y = 0; y < positions[indices[i]].height; y++) {
                final[positions[indices[i]].x + x][positions[indices[i]].y + y] = g->bitmap.buffer[y * g->bitmap.width + x];
                //final[positions[indices[i]].x + x][positions[indices[i]].y + y] += 0x11;
            }
        }
    }

    for (int i = 0; i < sz; i++) {
        final[i][i] = 0xcc;
    }

    printf("\n\n");
    for (int j = 0; j < sz; j++) {
        for (int i = 0; i < sz; i++) {
            printf("%02x", final[i][j]);
        }
        printf("\n");
    }

    freeFinal(&final, sz);

    free(indices);
    free(positions);

    printf("got to the end.\n");
    return 0;
}
