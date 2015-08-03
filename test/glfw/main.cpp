#include <png.h>
#include "common.h"
#include <unistd.h>
#include "util/Util.h"
#include "shader/Shader.h"
#include "io/Window.h"
#include "io/IOManager.h"
#include "io/ImageLoader.h"
#include "io/TextureCache.h"
#include "io/InputManager.h"
#include "drawing/Texture.h"
#include "drawing/SpriteBatch.h"
#include "drawing/Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

void jsonTest();

int main(int argc, char** argv) {

	printf("Hello, World! | location = %s\n", argv[0]);

    Window win;
    win.init("Hey ho!", 640, 480, NULL, NULL);
    printf("window.width = %d | window.height = %d\n", win.width, win.height);

    glfwSetCursorPosCallback(win.window, InputManager::cursorFunction);
    glfwSetKeyCallback(win.window, InputManager::keyFunction);

    jsonTest();

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

    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

    TextureCache cache;
    struct Texture tex = cache.getTexture("images/coolrobot~ipad.png");

    Camera2D camera;
    camera.init(win.width, win.height);

    Shader shader;
    shader.init("shader/test.vert", "shader/test.frag");
    shader.use();
    checkError("Shader finished!");

    GLint samLoc = glGetUniformLocation(shader.program, "sampler");
    checkError("glGetUniformLocation!");
    GLint matLoc = glGetUniformLocation(shader.program, "mat");
    checkError("glGetUniformLocation!");

    glUniform1i(samLoc, 0);
    checkError("glUniform1i!");

    SpriteBatch sprites;
    sprites.init(&shader);
    ColorRGBA8 color(0xFF, 0xFF, 0x00, 0xFF);

    while (!glfwWindowShouldClose(win.window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        checkError("Clear!");

        camera.setPosition(InputManager::instance().getMouseCoords());
        camera.update();
        glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(camera.getCameraMatrix()));

        sprites.begin();

        const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f); 
        const glm::vec4 destRect(0.0f, 0.0f, 100.0f, 100.0f);    
        const glm::vec4 destRect2(20.0f, 20.0f, 100.0f, 100.0f);    
        const glm::vec4 destRect3(40.0f, 40.0f, 100.0f, 100.0f);    
        const glm::vec4 destRect4(70.0f, 70.0f, 100.0f, 100.0f);    

        sprites.draw(destRect, uvRect, tex.id, 0.0f, color);
        sprites.draw(destRect2, uvRect, tex.id, 0.0f, color);
        sprites.draw(destRect3, uvRect, tex.id, 0.0f, color);
        sprites.draw(destRect4, uvRect, tex.id, 0.0f, color);
        
        sprites.end();
        sprites.renderBatch();

        if (InputManager::instance().isKeyPressed(GLFW_KEY_SPACE)) {
            printf("Pressed space!\n");
        }

        if (InputManager::instance().isKeyDown(GLFW_KEY_A)) {
            printf("Left!\n");
        }

        if (InputManager::instance().isKeyDown(GLFW_KEY_D)) {
            printf("Right!\n");
        }

        if (InputManager::instance().isKeyDown(GLFW_KEY_W)) {
            printf("Up!\n");
        }

        if (InputManager::instance().isKeyDown(GLFW_KEY_S)) {
            printf("Down!\n");
        }

        glfwSwapBuffers(win.window);
        checkError("Swap Buffers!");
        //printf("Pre Poll\n");
        InputManager::instance().update();
        //InputManager::instance().print();
        glfwPollEvents();
        //printf("Post Poll\n");
        checkError("Poll Events!");

        usleep(1000000 / 60);
    }

    shader.destroy();

    glfwTerminate();

    return 0;
}

void jsonTest() {
    printf("JSON Parsing\n"); const char* json = IOManager::readFile("level/level.json"); printf("json = %s\n", json);
    rapidjson::Document d;
    d.Parse(json);
    if (d.HasParseError()) {
        printf("PARSE ERROR! | offset = %zu | %s\n", d.GetErrorOffset(), GetParseError_En(d.GetParseError()));
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    printf("---------------------------\n");
    printf("JSON Test!\n");
    printf("%s\n", buffer.GetString());
    printf("---------------------------\n");
}

