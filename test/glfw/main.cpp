#include <png.h>
#include "common.h"
#include "util/Util.h"
#include "shader/Shader.h"
#include "io/Window.h"
#include "io/IOManager.h"
#include "io/ImageLoader.h"
#include "io/TextureCache.h"
#include "drawing/Texture.h"
#include "drawing/SpriteBatch.h"
#include "drawing/Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

void cursorFun(GLFWwindow* window, double xPos, double yPos);

class KeyWrapper {
public:
    void keyFun(GLFWwindow* window, int key, int scancode, int action, int mods);
};
void jsonTest();

glm::vec2 camPos(0.25f, 0.25f);

int main(int argc, char** argv) {

	printf("Hello, World! | location = %s\n", argv[0]);

    Window win;
    win.init("Hey ho!", 1280, 960, NULL, NULL);
    printf("window.width = %d | window.height = %d\n", win.width, win.height);

    KeyWrapper keyWrapper;
    keyWrapper.keyFun(win.window, 1, 2, 3, 4);
    glfwSetCursorPosCallback(win.window, cursorFun);
    glfwSetKeyCallback(win.window, &(keyWrapper.keyFun));

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

        camera.setPosition(camPos);
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

        glfwSwapBuffers(win.window);
        checkError("Swap Buffers!");
        glfwPollEvents();
        checkError("Poll Events!");
    }

    shader.destroy();

    glfwTerminate();

    return 0;
}

void cursorFun(GLFWwindow* window, double xPos, double yPos) {
    camPos.x = xPos;
    camPos.y = yPos;
}

void jsonTest() {
    printf("JSON Parsing\n");
    const char* json = IOManager::readFile("level/level.json");
    rapidjson::Document d;
    d.Parse(json);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    printf("---------------------------\n");
    printf("JSON Test!\n");
    printf("%s\n", buffer.GetString());
    printf("---------------------------\n");
}

void KeyWrapper::keyFun(GLFWwindow* window, int key, int scancode, int action, int mods) {
    printf("KeyFun | key = %d | scancode = %d | action = %d | mods = %d\n", key, scancode, action, mods);
}
