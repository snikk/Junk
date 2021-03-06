#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "../common.h" 
#include "Font.h"

struct Texture {
    GLuint id;
    int width;
    int height;
};

typedef struct Pos {
    int u;
    int v;
    short width;
    short height;
} Pos;

struct FontTexture {
    Texture tex;
    Font* font;
    int* indices;
    Pos* pos;
};

struct Position {
    GLfloat x;
    GLfloat y;

    void set(GLfloat xPos, GLfloat yPos) {
        x = xPos;
        y = yPos;
    }
};

struct ColorRGBA8 {
    ColorRGBA8() : r(0), g(0), b(0), a(0) { }
    ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
        r(R), g(G), b(B), a(A) { }
    ColorRGBA8(int color) { set(color); }
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;

    void set(int color) {  
        a = (color >> 24) & 0xFF;
        r = (color >> 16) & 0xFF;
        g = (color >> 8) & 0xFF;
        b = color & 0xFF;
    }

    int get() {
        return (a << 24) | (r << 16) | (g << 8) | b;
    }
};

struct UV {
    float u;
    float v;
};

struct Vertex {
    Position position;
    ColorRGBA8 color;
    UV uv;

    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }

    void setUV(float u, float v) {
        uv.u = u;
        uv.v = v;
    }
};

#endif
