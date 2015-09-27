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
    )

target_link_libraries (zombieGame glfw ${GLFW_LIBRARIES})
target_link_libraries (zombieGame engine)
