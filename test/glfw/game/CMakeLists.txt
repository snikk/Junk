add_executable (
    zombieGame

    main.cpp
    MainGame.cpp

    zombie/Agent.cpp
    zombie/Bullet.cpp
    zombie/Gun.cpp
    zombie/Human.cpp
    zombie/Level.cpp
    zombie/Player.cpp
    zombie/Zombie.cpp

    zombie/actor/GameActorFactory.cpp

    zombie/actor/components/AI.cpp
    zombie/actor/components/Health.cpp
    zombie/actor/components/Render.cpp

    zombie/events/Events.cpp
    )

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

message ("This is the output!!!!!!!!!!!!!!!!")
message (${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message (${CMAKE_CURRENT_BINARY_DIR})
message (${CMAKE_BINARY_DIR})
add_custom_command (TARGET zombieGame PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources/actor/ ${CMAKE_CURRENT_BINARY_DIR}/actor/)
add_custom_command (TARGET zombieGame PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources/images/ ${CMAKE_CURRENT_BINARY_DIR}/images/)
add_custom_command (TARGET zombieGame PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources/level/ ${CMAKE_CURRENT_BINARY_DIR}/level/)
add_custom_command (TARGET zombieGame PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources/glsl/ ${CMAKE_CURRENT_BINARY_DIR}/shader/)
target_link_libraries (zombieGame ${PNG_LIBRARY})
target_link_libraries (zombieGame glfw ${GLFW_LIBRARIES})
target_link_libraries (zombieGame engine)
