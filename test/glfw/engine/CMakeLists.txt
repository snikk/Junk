add_library (
    engine

    common.cpp

    actor/actor.cpp
    actor/ActorFactory.cpp
    actor/components/Pickup.cpp
    actor/components/PositionComponent.cpp
    actor/components/HealthComponent.cpp

    debug/DebugView.cpp

    drawing/Camera.cpp
    drawing/SpriteBatch.cpp

    events/EngineEvents.cpp
    events/EventManager.cpp

    network/Network.cpp

    io/Error.cpp
    io/ImageLoader.cpp
    io/InputManager.cpp
    io/IOManager.cpp
    io/ResourceManager.cpp
    io/TextureCache.cpp
    io/Window.cpp

    shader/Shader.cpp

    util/Util.cpp
    )

set(CMAKE_BUILD_TYPE Debug)

target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
