#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

char* readFile(const char* filename);
GLuint createProgram(const char* vert, const char* frag);
GLuint createShader(const char* shader, GLenum type);
void checkError(const char* msg);

int main(int argc, char** argv) {

    printf("Hello, World!\n");

    if (!glfwInit()) {
        printf("Hey.... error!?\n");
        return 1;
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hey ho!", NULL, NULL);

    if (!window) {
        printf("No window was created!\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    const GLubyte* ver = glGetString(GL_VERSION);
    printf("This is the version = %s\n", ver);

    glUseProgram(23);
    checkError("Checking errors before creating program.");
    GLuint program = createProgram("test.vert", "test.frag");
    glUseProgram(program);

    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

    float data[] = {-0.5, -0.5, 
                   0.5, -0.5, 
                  -0.5,  0.5, 
                   0.5, -0.5, 
                   0.5,  0.5, 
                  -0.5,  0.5
    };

    GLint posLoc = glGetAttribLocation(program, "position");
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

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        checkError("Main Loop!");

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program);

    glfwTerminate();

    return 0;
}

char* readFile(const char* filename) {
    FILE* fp = fopen(filename, "rb");

    if (!fp) {
        printf("Error reading file | %s\n", filename);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (size == 0) {
        printf("Error reading size!\n");
        fclose(fp);
    }
    
    size++;
    char* str = (char*) malloc(sizeof(char) * size);

    memset(str, 0, size);

    fread(str, 1, size, fp);

    fclose(fp);

    return str;
}

GLuint createProgram(const char* vert, const char* frag) {
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

GLuint createShader(const char* shader, GLenum type) {
    GLuint shaderObj = glCreateShader(type);
    if (!shaderObj) {
        printf("Couldn't create shader object!\n");
        return 0;
    }

    char* source = readFile(shader);
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

