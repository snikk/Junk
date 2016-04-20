#ifndef __DEBUG_VIEW_H__
#define __DEBUG_VIEW_H__

#include "../common.h"
#include "../shader/Shader.h"
#include "../drawing/Texture.h"

struct DebugVertex {
    Position position;
    ColorRGBA8 color;

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

    void setColor(int newColor) {
        setColor((newColor << 16) & 0xFF, (newColor << 8) & 0xFF, newColor & 0xFF, (newColor << 24) & 0xFF);
    }
};

class DebugView {
public:
    DebugView();
    ~DebugView();

    void init();
    
    void clear();

    void setColor(int color);

    void move(float x, float y);
    void move(float x, float y, int color);

    void lineTo(float x, float y);
    void lineTo(float x, float y, int color);

    void curveTo(float controlX, float controlY, float x, float y);
    void curveTo(float controlX, float controlY, float x, float y, int color);

    void draw(glm::mat4 projectionMatrix);
private:
    void grow();
    void shrink();

    Shader _shader;
    GLuint _vbo;
    GLuint _vao;

    DebugVertex* _vertices;
    int _count;
    int _max;
};

#endif
