#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#ifndef __APPLE__
#include <GL/glew.h>
#endif

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <map>
#include <memory>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#if defined(_DEBUG)
#   define GCC_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#   define GCC_NEW new
#endif

class Actor;
class ActorComponent;

typedef unsigned int ActorId;
typedef unsigned int ComponentId;

typedef std::shared_ptr<Actor> StrongActorPtr;
typedef std::weak_ptr<Actor> WeakActorPtr;
typedef std::shared_ptr<ActorComponent> StrongActorComponentPtr;
typedef std::weak_ptr<ActorComponent> WeakActorComponentPtr;

extern void printObj(const rapidjson::Value& data);

#include "common.tcc"

#endif
