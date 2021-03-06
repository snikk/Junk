#include "SpriteBatch.h"
#include "../util/util.h"
#include "../shader/Shader.h"
#include <algorithm>

SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::init(Shader* shader) {
    createVertexArray(shader);
}

void SpriteBatch::begin() {
    _renderBatches.clear();
   
    _glyphs.clear();
}

void SpriteBatch::end() {
    _glyphPointers.resize(_glyphs.size());
    for (int i = 0; i < _glyphs.size(); i++) {
        _glyphPointers[i] = &_glyphs[i];
    }

    sortGlyphs();
    createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color) {

    _glyphs.emplace_back(destRect, uvRect, texture, depth, color);
}

void SpriteBatch::renderBatch() {
    glBindVertexArray(_vao);

    for (int i = 0; i < _renderBatches.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

        glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
    }

    glBindVertexArray(0);

    checkError("SpriteBatch::renderBatches");
}

void SpriteBatch::createRenderBatches() {
    std::vector <Vertex> vertices;
    vertices.resize(_glyphPointers.size() * 6);

    if (_glyphPointers.empty()) {
        return;
    }

    int offset = 0; // current offset
    int cv = 0; // current vertex

    _renderBatches.emplace_back(offset, 6, _glyphPointers[0]->texture);
    vertices[cv++] = _glyphPointers[0]->topLeft;
    vertices[cv++] = _glyphPointers[0]->bottomLeft;
    vertices[cv++] = _glyphPointers[0]->bottomRight;
    vertices[cv++] = _glyphPointers[0]->bottomRight;
    vertices[cv++] = _glyphPointers[0]->topRight;
    vertices[cv++] = _glyphPointers[0]->topLeft;
    offset += 6;

    //Add all the rest of the glyphs
    for (int cg = 1; cg < _glyphPointers.size(); cg++) {

        // Check if this glyph can be part of the current batch
        if (_glyphPointers[cg]->texture != _glyphPointers[cg - 1]->texture) {
            // Make a new batch
            _renderBatches.emplace_back(offset, 6, _glyphPointers[cg]->texture);
        } else {
            // If its part of the current batch, just increase numVertices
            _renderBatches.back().numVertices += 6;
        }
        vertices[cv++] = _glyphPointers[cg]->topLeft;
        vertices[cv++] = _glyphPointers[cg]->bottomLeft;
        vertices[cv++] = _glyphPointers[cg]->bottomRight;
        vertices[cv++] = _glyphPointers[cg]->bottomRight;
        vertices[cv++] = _glyphPointers[cg]->topRight;
        vertices[cv++] = _glyphPointers[cg]->topLeft;
        offset += 6;
    }

    // Bind our VBO
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    // Orphan the buffer (for speed)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    // Upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void SpriteBatch::createVertexArray(Shader* shader) {
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

    GLint posLoc = shader->getAttribute("vertexPosition");
    CHK_ERR("Get vertexPosition!");
    GLint colLoc = shader->getAttribute("vertexColor");
    checkError("fragmentColor!");
    GLint texLoc = shader->getAttribute("vertexUV");
    checkError("texture UV!");
    GLint samLoc = shader->getUniform("sampler");
    checkError("Sampler!");

    //Tell opengl what attribute arrays we need
    glEnableVertexAttribArray(posLoc);
    glEnableVertexAttribArray(colLoc);
    glEnableVertexAttribArray(texLoc);

    //This is the position attribute pointer
    glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    //This is the position attribute pointer
    glVertexAttribPointer(colLoc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    //This is the UV attribute pointer
    glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);

}

void SpriteBatch::sortGlyphs() {
    std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
    return (a->texture < b->texture);
}
