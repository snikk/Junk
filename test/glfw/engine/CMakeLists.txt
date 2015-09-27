add_library (
    engine

    drawing/Camera.cpp
    drawing/SpriteBatch.cpp

    io/Error.cpp
    io/ImageLoader.cpp
    io/InputManager.cpp
    io/IOManager.cpp
    io/ResourceManager.cpp
    io/TextureCache.cpp
    io/Window.cpp

    memory/MemoryPool.cpp

    shader/Shader.cpp

    util/Util.cpp
    )

target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
