#ifndef __WINDOW_H__
#define __WINDOW_H__

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

class Window {
public:
    bool init(const char* name, int width, int height);
    bool init(const char* name, int width, int height, GLFWmonitor* monitor, GLFWwindow* share);

    GLFWwindow* window;
private:
};

#endif