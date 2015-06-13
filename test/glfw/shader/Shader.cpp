#include <stdio.h>
#include <stdlib.h>
#include "Shader.h"
#include "../io/IOManager.h"
#include "../util/Util.h"

Shader::Shader() { }

void Shader::init(const char* vertFile, const char* fragFile) {
    program = createProgram(vertFile, fragFile);
}

GLuint Shader::createProgram(const char* vert, const char* frag) {
    GLuint vertex = createShader(vert, GL_VERTEX_SHADER);
    if (!vertex) {
        checkError("Failed creating vertex shader");
        return 0;
    }

    GLuint fragment = createShader(frag, GL_FRAGMENT_SHADER);
    if (!fragment) {
        glDeleteShader(vertex);
        checkError("Failed creating fragment shader");
        return 0;
    }

    GLuint program = glCreateProgram();
    if (!program) {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        checkError("Failed creating program");
        return 0;
    }

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    checkError("Failed Attaching shaders to program.");
    glLinkProgram(program);
    checkError("Failed linking program.");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
} 

GLuint Shader::createShader(const char* shader, GLenum type) {
    GLuint shaderObj = glCreateShader(type);
    if (!shaderObj) {
        printf("Couldn't create shader object!\n");
        return 0;
    }

    char* source = IOManager::readFile(shader);
    printf("Creating shader with program! | program = %s\n", source);

    glShaderSource(shaderObj, 1, &source, NULL);

    free(source);

    GLint ret;

    glCompileShader(shaderObj);
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &ret);

    if (ret == GL_FALSE) {
        printf("Error creating shader object!\n");

        GLint logLength;
        glGetShaderiv(shaderObj, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLint infoLog;
            GLchar* info = (GLchar*) malloc(sizeof(GLchar) * logLength);

            glGetShaderInfoLog(shaderObj, logLength, &infoLog, info);
            

            printf("Shader failed with log.\n");
            printf("--------------------------------------------------\n");
            printf("%s\n", info);
            printf("--------------------------------------------------\n");
        }

        glDeleteShader(shaderObj);
        return 0;
    }

    return shaderObj;
}

void Shader::use() {
    glUseProgram(program);
}

void Shader::destroy() {
    glDeleteProgram(program);
}

