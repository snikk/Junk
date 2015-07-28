#include <stdio.h>
#include "Window.h"

bool Window::init(const char* name, int width, int height) {
    return init(name, width, height, NULL, NULL);
}

bool Window::init(const char* name, int width, int height, GLFWmonitor* monitor, GLFWwindow* share) {
    if (!glfwInit()) {
        printf("Couldn't init glfw!\n");
        return false;
    }

    this->width = width;
    this->height = height;

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    window = glfwCreateWindow(width, height, name, monitor, share);

    if (!window) {
        printf("No window was created!\n");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

