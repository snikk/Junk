#include "Util.h"
#include <stdio.h>

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

void checkError(const char* msg) {
    GLenum err;
    const char* errorString;
    while ((err = glGetError()) != GL_NO_ERROR) {
        switch (err) {
            case GL_INVALID_ENUM:
                errorString = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                errorString = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                errorString = "GL_INVALID_OPERATION";
                break;
            //case GL_INVALID_FRAMEBUFFER_OPERATION:
                //errorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
                //break;
            case GL_OUT_OF_MEMORY:
                errorString = "GL_OUT_OF_MEMORY";
                break;
            //case GL_STACK_UNDERFLOW:
                //errorString = "GL_STACK_UNDERFLOW";
                //break;
            //case GL_STACK_OVERFLOW:
                //errorString = "GL_STACK_OVERFLOW";
                //break;
            default:
                errorString = "UNKNOWN_ERROR";
                break;
        }
        printf("----==== Caught an %s | %s\n", errorString, msg);
    }
}
