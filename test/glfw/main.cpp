#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include "io/Window.h"
#include "util/Util.h"
#include "shader/Shader.h"

int main(int argc, char** argv) {

	printf("Hello, World! | location = %s\n", argv[0]);

    Window win;
    win.init("Hey ho!", 640, 480, NULL, NULL);

#ifndef __APPLE__
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		printf("Error: %s\n", glewGetErrorString(err));
		glfwTerminate();
		return 1;
	}
#endif

    const GLubyte* ver = glGetString(GL_VERSION);
    printf("This is the version = %s\n", ver);

    Shader shader;
    shader.init("shader/test.vert", "shader/test.frag");
    shader.use();

    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

    float data[] = {-0.5, -0.5, 
                   0.5, -0.5, 
                  -0.5,  0.5, 
                   0.5, -0.5, 
                   0.5,  0.5, 
                  -0.5,  0.5
    };

    GLint posLoc = glGetAttribLocation(shader.program, "position");
    printf("posLoc = %d\n", posLoc);
    checkError("glGetAttribLocation!");
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    checkError("glGenVertexArrays!");
    glBindVertexArray(vertexArrayID);
    checkError("glBindVertexArray!");

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    checkError("glGenBuffer!");
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    checkError("glBindBuffer!");
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    checkError("glBufferData!");

    glEnableVertexAttribArray(posLoc);
    glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    checkError("glVertexAttribPointer!");

    while (!glfwWindowShouldClose(win.window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        checkError("Main Loop!");

        glfwSwapBuffers(win.window);
        glfwPollEvents();
    }

    shader.destroy();

    glfwTerminate();

    return 0;
}

