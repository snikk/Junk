#include "DebugView.h"
#include "../util/Util.h"
#include <cstring>
#include "../common.h"

DebugView::DebugView() {
}

DebugView::~DebugView() {
    free(_vertices);
    _shader.destroy();
}

void DebugView::init() {
    _shader.init("shader/passthrough.vert", "shader/passthrough.frag");
    _shader.addAttribute("position");
    _shader.addAttribute("color");
    
    // Generate the VAO if it isn't already generated
    if (_vao == 0) {
        glGenVertexArrays(1, &_vao);
    }
    
    // Bind the VAO. All subsequent opengl calls will modify it's state.
    glBindVertexArray(_vao);

    //G enerate the VBO if it isn't already generated
    if (_vbo == 0) {
        glGenBuffers(1, &_vbo);
    }
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    GLint posLoc = _shader.getAttribute("position");
    CHK_ERR("Get Position!");
    GLint colLoc = _shader.getAttribute("color");
    checkError("get Color!");

    //Tell opengl what attribute arrays we need
    glEnableVertexAttribArray(posLoc);
    glEnableVertexAttribArray(colLoc);

    //This is the position attribute pointer
    glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, position));
    //This is the position attribute pointer
    glVertexAttribPointer(colLoc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, color));

    glBindVertexArray(0);

    _max = 16;
    _count = 0;
    grow();
}

void DebugView::clear() {
    _count = 0;
}

void DebugView::setColor(int color) {
    _vertices[_count].color.set(color);
}

void DebugView::move(float x, float y) {
    this->move(x, y, _vertices[_count > 0 ? _count - 1 : 0].color.get());
}

void DebugView::move(float x, float y, int color) {
    if (_count + 3 > _max)
        grow();

    if (_count > 0) {
        memcpy(&_vertices[_count], &_vertices[_count - 1], sizeof(DebugVertex));
        _count++;
        _vertices[_count].color.set(0);
        lineTo(x, y, 0);
        lineTo(x, y, color);
    } else {
        lineTo(x, y, color);
    }
}

void DebugView::lineTo(float x, float y) {
    this->lineTo(x, y, _vertices[_count > 0 ? _count - 1 : 0].color.get());
}

void DebugView::lineTo(float x, float y, int color) {
    if (_count + 1 > _max)
        grow();

    _vertices[_count].position.set(x, y);
    _vertices[_count].color.set(color);
    _count++;
}

void DebugView::curveTo(float controlX, float controlY, float x, float y) {
    this->curveTo(controlX, controlY, x, y, _vertices[_count > 0 ? _count - 1 : 0].color.get());
}

void DebugView::curveTo(float controlX, float controlY, float x, float y, int color) {
    float dist = distance(_vertices[_count - 1].position.x, _vertices[_count - 1].position.y, controlX, controlY);
    dist += distance(controlX, controlY, x, y);
    int segments = dist / 100;

    float startX = _vertices[_count - 1].position.x;
    float startY = _vertices[_count - 1].position.y;

    for (int i = 1; i < segments; i++) {
        float per = (float) i / (float) segments;
        float xPos1 = lerp(startX, controlX, per);
        float yPos1 = lerp(startY, controlY, per);
        float xPos2 = lerp(controlX, x, per);
        float yPos2 = lerp(controlY, y, per);
        float lastX = lerp(xPos1, xPos2, per);
        float lastY = lerp(yPos1, yPos2, per);

        //printf("Position | i = %d | per = %f | pos1 = (%f, %f) | pos2 = (%f, %f) | last = (%f, %f)\n", i, per, xPos1, yPos1, xPos2, yPos2, lastX, lastY);

        lineTo(lastX, lastY, per);
    }
    lineTo(x, y, color);
}

void DebugView::draw(glm::mat4 projectionMatrix) {
    if (_count < _max / 2)
        shrink();

    _shader.use();
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    GLint pUniform = _shader.getUniform("mat");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    glBufferData(GL_ARRAY_BUFFER, _count * sizeof(DebugVertex), _vertices, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_LINE_STRIP, 0, _count);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    _shader.unuse();
}

void DebugView::grow() {
    _max = _max * 2;
    DebugVertex* newVertices = (DebugVertex*) malloc(_max * sizeof(DebugVertex));
    memcpy(newVertices, _vertices, _count * sizeof(DebugVertex));
    free(_vertices);
    _vertices = newVertices;
}

void DebugView::shrink() {
    if (_max <= 32)
        return;

    _max = _max / 2;
    DebugVertex* newVertices = (DebugVertex*) malloc(_max * sizeof(DebugVertex));
    memcpy(newVertices, _vertices, _count * sizeof(DebugVertex));
    free(_vertices);
    _vertices = newVertices;
}

