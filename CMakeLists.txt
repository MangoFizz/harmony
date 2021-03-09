# Minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Set project info
project(harmony
    VERSION 1.0.0
    LANGUAGES C CXX ASM
)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Set C++ flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -masm=intel")

# Include Lua
include("ext/lua/lua.cmake")

add_library(harmony MODULE
    src/events/d3d9_end_scene.cpp
    src/events/d3d9_end_scene.S
    src/events/d3d9_reset.cpp
    src/events/d3d9_reset.S
    src/events/map_load.cpp
    src/events/multiplayer_event.cpp
    src/events/multiplayer_event.S
    src/events/multiplayer_sound.cpp
    src/events/multiplayer_sound.S
    src/events/tick.cpp
    src/halo_data/path.cpp
    src/halo_data/multiplayer_events.cpp
    src/halo_data/multiplayer_sounds.cpp
    src/halo_data/resolution.cpp
    src/halo_data/window.cpp
    src/lua/api/callback.cpp
    src/lua/api/optic.cpp
    src/lua/library.cpp
    src/lua/optic_store.cpp
    src/lua/script.cpp
    src/math/geometry.cpp
    src/memory/signatures/client.cpp
    src/memory/codecave.cpp
    src/memory/codefinder.cpp
    src/memory/signature.cpp
    src/messaging/console_output.cpp
    src/messaging/console_output.S
    src/messaging/message_box.cpp
    src/optic/animation.cpp
    src/optic/handler.cpp
    src/optic/render.cpp
    src/optic/sprite.cpp
    src/harmony.cpp
)

# Set Lua include path
target_include_directories(harmony
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/ext/lua"
)

# Set output name
set_target_properties(harmony PROPERTIES PREFIX "")
set_target_properties(harmony PROPERTIES OUTPUT_NAME "harmony")

# Set linker flags
set_target_properties(harmony PROPERTIES LINK_FLAGS "-static -static-libgcc -static-libstdc++")

# Set required libraris
target_link_libraries(harmony lua -ld3dx9 -ld3d9)

# Install harmony.dll
install(TARGETS harmony DESTINATION "${CMAKE_INSTALL_PREFIX}")
