#include <stdio.h>
#include <stdlib.h>

#ifndef __APPLE__
#include <GL/glew.h>
#endif

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
    printf("Created program = %d\n", program);
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
    checkError("Finished deleting objects.");

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
	if (!source) {
		printf("Coun't open file %s\n", shader);
		glDeleteShader(shaderObj);
		return 0;
	}

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
    CHK_ERR("glUseProgram!");
}

void Shader::unuse() {
    glUseProgram(0);
    CHK_ERR("glUseProgram 0");
}

void Shader::destroy() {
    glDeleteProgram(program);
}

void Shader::addAttribute(const char* name) {
    GLint posLoc = glGetAttribLocation(program, name);
    CHK_ERR("glGetAttribLocation!");
    attributes[name] = posLoc;
}

GLint Shader::getAttribute(const char* name) {
    const auto& it = attributes.find(name);
    if (it != attributes.end())
        return it->second;

    return -1;
}

GLint Shader::getUniform(const char* name) {
    GLint uniform = glGetUniformLocation(program, name);
    checkError("glGetUniformLocation()");
    return uniform;
}

