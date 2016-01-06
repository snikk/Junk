#include <iostream>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "My window", NULL, NULL);

    if (!window) {
        std::cout << "Hey.  There was an error" << std::endl;

        return 1;
    }

    glfwMakeContextCurrent(window);

    const GLubyte* str = glGetString(GL_VERSION);
    std::cout << "Version = " << str << std::endl;

    while( !glfwWindowShouldClose(window) )
    {
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
