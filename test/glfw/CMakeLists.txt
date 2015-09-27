cmake_minimum_required (VERSION 2.8.11)
project (Zombie)

if (CMAKE_VERSION VERSION_LESS "3.1")
    set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
else ()
    set (CMAKE_CXX_STANDARD 11)
endif ()

set(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory (3rdparty/glfw)
include_directories (
    /Users/jglenn/dev/c++/glfw-3.1.1/include
	~/dev/c++/glm/
    ~/dev/c++/rapidjson/include/
    )
add_subdirectory (engine)
add_subdirectory (game)
