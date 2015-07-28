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
#include <glm/glm.hpp>
#include <vector>
