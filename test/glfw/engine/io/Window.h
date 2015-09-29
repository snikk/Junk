#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "../common.h"

class Window {
public:
    bool init(const char* name, int width, int height);
    bool init(const char* name, int width, int height, GLFWmonitor* monitor, GLFWwindow* share);

    void swapBuffers();

    GLFWwindow* window;
    int width;
    int height;
private:
};

#endif
