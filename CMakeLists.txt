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
include("ext/lua53.cmake")

# Include Soloud
include("ext/soloud.cmake")

add_library(harmony MODULE
    src/command/command.cpp
    src/command/config.cpp
    src/command/commands/client.cpp
    src/command/commands/debug/client_player_update_log.cpp
    src/command/commands/debug/hs_debug.cpp
    src/command/commands/debug/signature.cpp
    src/debug/client_player_update_log.cpp
    src/debug/client_player_update_log.S
    src/events/console_command.cpp
    src/events/console_command.S
    src/events/d3d9_end_scene.cpp
    src/events/d3d9_end_scene.S
    src/events/d3d9_reset.cpp
    src/events/d3d9_reset.S
    src/events/hs_function.cpp
    src/events/hs_function.S
    src/events/keypress.cpp
    src/events/keypress.S
    src/events/map_load.cpp
    src/events/multiplayer_event.cpp
    src/events/multiplayer_event.S
    src/events/multiplayer_hit_sound.cpp
    src/events/multiplayer_hit_sound.S
    src/events/multiplayer_sound.cpp
    src/events/multiplayer_sound.S
    src/events/tick.cpp
    src/events/widget_accept.cpp
    src/events/widget_accept.S
    src/events/widget_close.cpp
    src/events/widget_close.S
    src/events/widget_list_tab.cpp
    src/events/widget_list_tab.S
    src/events/widget_mouse_button_press.cpp
    src/events/widget_mouse_button_press.S
    src/events/widget_mouse_focus.cpp
    src/events/widget_mouse_focus.S
    src/events/widget_open.cpp
    src/events/widget_open.S
    src/events/widget_sound.cpp
    src/events/widget_sound.S
    src/halo_data/color.cpp
    src/halo_data/console.cpp
    src/halo_data/console.S
    src/halo_data/master_volume.cpp
    src/halo_data/game_engine.cpp
    src/halo_data/input_devices.cpp
    src/halo_data/multiplayer_events.cpp
    src/halo_data/multiplayer_sounds.cpp
    src/halo_data/multiplayer_sounds.S
    src/halo_data/path.cpp
    src/halo_data/resolution.cpp
    src/halo_data/sound.cpp
    src/halo_data/sound.S
    src/halo_data/tag.cpp
    src/halo_data/tag.S
    src/halo_data/widget.cpp
    src/halo_data/widget.S
    src/halo_data/window.cpp
    src/lua/api/callback.cpp
    src/lua/api/math.cpp
    src/lua/api/multiplayer.cpp
    src/lua/api/optic.cpp
    src/lua/api/menu.cpp
    src/lua/api/misc.cpp
    src/lua/api/time.cpp
    src/lua/helpers.cpp
    src/lua/library.cpp
    src/lua/script.cpp
    src/math/geometry.cpp
    src/memory/codecave.cpp
    src/memory/codefinder.cpp
    src/memory/hook.cpp
    src/memory/memory.cpp
    src/memory/signature.cpp
    src/memory/signatures/client.cpp
    src/menu/widescreen_element_reposition_menu.S
    src/menu/widescreen_mouse.S
    src/menu/widescreen.cpp
    src/menu/widget_render.cpp
    src/menu/widget_render.S
    src/messaging/console_output.cpp
    src/messaging/exception.cpp
    src/messaging/message_box.cpp
    src/optic/animation.cpp
    src/optic/store.cpp
    src/optic/d3dx9.cpp
    src/optic/exception.cpp
    src/optic/handler.cpp
    src/optic/render.cpp
    src/optic/sound.cpp
    src/optic/sprite.cpp
    src/server/status.cpp
    src/harmony.cpp
)

# Set includes path
target_include_directories(harmony
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/ext/lua53"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/ext/soloud/include"
)

# Set output name
set_target_properties(harmony PROPERTIES PREFIX "")
set_target_properties(harmony PROPERTIES OUTPUT_NAME "harmony")

# Set linker flags
set_target_properties(harmony PROPERTIES LINK_FLAGS "-static -static-libgcc -static-libstdc++")

# Set required libraries
target_link_libraries(harmony lua53 soloud ws2_32)

# Install harmony.dll
install(TARGETS harmony DESTINATION "${CMAKE_INSTALL_PREFIX}")
