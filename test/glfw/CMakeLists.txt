cmake_minimum_required (VERSION 2.8.11)
project (Zombie)

set(CMAKE_BUILD_TYPE Debug)

if (CMAKE_VERSION VERSION_LESS "3.1")
    set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
else ()
    set (CMAKE_CXX_STANDARD 11)
endif ()

set(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory (3rdparty/glfw)
find_package(PNG REQUIRED)
if (WIN32)
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()
	
include_directories (
    ${PNG_INCLUDE_DIR}
    3rdparty/glfw/include
	3rdparty/glm/
    3rdparty/rapidjson/include/
    3rdparty/fastdelegate/
    )
add_subdirectory (engine)
add_subdirectory (game)
