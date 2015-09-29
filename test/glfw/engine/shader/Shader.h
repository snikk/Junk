#ifndef __SHADER_H__
#define __SHADER_H__

#include <common.h>
#include <unordered_map>

class Shader {
private:
    struct hsh_str {
        unsigned int operator()(const char* value) const {
            unsigned int hash;
            int offset = 'a' - 1;
            while (*value != '\0') {
                hash = hash << 1 | (*value - offset);
                value++;
            }
            return hash;
        }   
    };

    struct cmp_str {
        bool operator()(const char* lhs, const char* rhs) const {
            return std::strcmp(lhs, rhs) == 0;
        }   
    };

    GLuint createProgram(const char* vert, const char* frag);
    GLuint createShader(const char* shader, GLenum type);

    std::unordered_map<const char*, GLint, hsh_str, cmp_str> attributes;

public:
    Shader();

    void init(const char* vertFile, const char* fragFile);

    void use();
    void unuse();
    void destroy();

    void addAttribute(const char* name);
    GLint getAttribute(const char* name);
    GLint getUniform(const char* name);

    int program;
};

#endif
