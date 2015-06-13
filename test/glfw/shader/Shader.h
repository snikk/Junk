#ifndef __SHADER_H__
#define __SHADER_H__

//#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

class Shader {
private:
    GLuint createProgram(const char* vert, const char* frag);
    GLuint createShader(const char* shader, GLenum type);

public:
    Shader();

    void init(const char* vertFile, const char* fragFile);

    void use();
    void destroy();

    int program;
};

#endif
