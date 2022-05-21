// SPDX-License-Identifier: GPL-3.0-only

#include <filesystem>
#include "../../math/geometry.hpp"
#include "../../optic/animation.hpp"
#include "../../optic/handler.hpp"
#include "../../optic/render.hpp"
#include "../../harmony.hpp"
#include "../script.hpp"
#include "../library.hpp"
#include "../helpers.hpp"
#include "optic.hpp"

namespace Harmony::Lua {
    static Library *library = nullptr;
    static Optic::Handler *optic_handler = nullptr;

    static int lua_create_animation(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 1) {
            long duration = luaL_checknumber(state, 1);
            auto handle = optic->create_animation(duration);
            
            // Return animation handle
            lua_pushinteger(state, handle);
            return 1;
        }
        else {
            return luaL_error(state, "invalid number of arguments in harmony create_animation function");
        }
    }

    static int lua_set_animation_property(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 4 || args == 7) {
            auto *anim = optic->get_animation(luaL_checkinteger(state, 1));
            if(anim) {
                Math::QuadraticBezier curve;
                if(args == 4) {
                    std::string preset = luaL_checkstring(state, 2);
                    if(preset == "ease in") {
                        curve = Optic::Animation::ease_in();
                    }
                    else if(preset == "ease out") {
                        curve = Optic::Animation::ease_out();
                    }
                    else if(preset == "ease in out") {
                        curve = Optic::Animation::ease_in_out();
                    }
                    else if(preset == "linear") {
                        curve = Optic::Animation::linear();
                    }
                    else {
                        luaL_error(state, "invalid curve preset name in harmony set_animation_property function");
                    }
                }
                else {
                    float x1 = luaL_checknumber(state, 2);
                    float y1 = luaL_checknumber(state, 3);
                    float x2 = luaL_checknumber(state, 4);
                    float y2 = luaL_checknumber(state, 5);
                    curve = Math::QuadraticBezier({x1, y1}, {x2, y2});
                }

                auto property = Optic::Animation::get_render_property_from_string(luaL_checkstring(state, -2));
                if(property != Optic::Animation::RENDER_PROPERTY_INVALID) {
                    auto transform = anim->get_transform();
                    switch(property) {
                        case Optic::Animation::RENDER_PROPERTY_POSITION_X:
                            transform.position.x = luaL_checknumber(state, -1);
                            break;
                        case Optic::Animation::RENDER_PROPERTY_POSITION_Y:
                            transform.position.y = luaL_checknumber(state, -1);
                            break;
                        case Optic::Animation::RENDER_PROPERTY_OPACITY:
                            transform.opacity = luaL_checknumber(state, -1);
                            break;
                        case Optic::Animation::RENDER_PROPERTY_ROTATION:
                            transform.rotation = RADIAN(luaL_checknumber(state, -1));
                            break;
                        case Optic::Animation::RENDER_PROPERTY_SCALE_X:
                            transform.scale.x = luaL_checknumber(state, -1);
                            break;
                        case Optic::Animation::RENDER_PROPERTY_SCALE_Y:
                            transform.scale.y = luaL_checknumber(state, -1);
                            break;
                    }

                    anim->set_property_curve(property, curve);
                    anim->set_transform(transform);
                }
                else {
                    luaL_error(state, "invalid render property in harmony set_animation_property function");
                }
            }
            else {
                luaL_error(state, "invalid animation name in harmony set_animation_property function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony set_animation_property function");
        }
        return 0;
    }

    static int lua_create_sprite(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 3 || args == 7) {
            // Arguments
            std::string texture_path = std::string(script->get_data_path()) + "\\" + luaL_checkstring(state, 1);
            int frame_width = luaL_checknumber(state, 2);
            int frame_height = luaL_checknumber(state, 3);

            if(script->path_is_valid(texture_path)) {
                if(std::filesystem::exists(texture_path)) {
                    if(args == 3) {
                        auto handle = optic->create_sprite(texture_path, frame_width, frame_height);
                        lua_pushinteger(state, handle);
                    }
                    else {
                        auto rows = luaL_checkinteger(state, 4);
                        auto columns = luaL_checkinteger(state, 5);
                        auto frames = luaL_checkinteger(state, 6);
                        auto fps = luaL_checkinteger(state, 7);

                        auto handle = optic->create_sprite(texture_path, rows, columns, frames, fps, frame_width, frame_height);
                        lua_pushinteger(state, handle);
                    }
                    return 1;
                }
                else {
                    luaL_error(state, "texture does not exists in harmony create_sprite function");
                }
            }
            else {
                luaL_error(state, "invalid texture path in harmony create_sprite function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony create_sprite function");
        }
        return 0;
    }

    static int lua_create_render_queue(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args >= 6 && args <= 9) {
            // Arguments
            float pos_x = luaL_checknumber(state, 1);
            float pos_y = luaL_checknumber(state, 2);
            int opacity = luaL_checknumber(state, 3);
            float rotation = luaL_checknumber(state, 4);
            long duration = luaL_checknumber(state, 5);
            int max_renders = luaL_checknumber(state, 6);

            // Set up initial sprite state
            Optic::Sprite::State initial_state;
            initial_state.position = {pos_x, pos_y};
            initial_state.color.a = opacity;
            initial_state.rotation = rotation;

            auto handle = optic->create_render_queue(initial_state, rotation, max_renders, duration);

            auto *queue = optic->get_render_queue(handle);

            if(args >= 7) {
                auto *fade_in = optic->get_animation(luaL_checkinteger(state, 7));
                if(fade_in) {
                    queue->set_fade_in_anim(*fade_in);
                }
                else {
                    luaL_error(state, "invalid fade-in animation name is harmony create_render_queue function");
                }
            }

            if(args >= 8) {
                auto *fade_out = optic->get_animation(luaL_checkinteger(state, 8));
                if(fade_out) {
                    queue->set_fade_out_anim(*fade_out);
                }
                else {
                    luaL_error(state, "invalid fade-out animation name is harmony create_render_queue function");
                }
            }

            if(args == 9) {
                auto *slide = optic->get_animation(luaL_checkinteger(state, 9));
                if(slide) {
                    queue->set_slide_anim(*slide);
                }
                else {
                    luaL_error(state, "invalid slide animation name is harmony create_render_queue function");
                }
            }

            lua_pushinteger(state, handle);
            return 1;
        }
        else {
            return luaL_error(state, "invalid number of arguments in harmony create_render_queue function");
        }
    }

    static int lua_render_sprite(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 2) {
            // Arguments
            auto sprite_handle = luaL_checkinteger(state, 1);
            auto queue_handle = luaL_checkinteger(state, 2);

            try {
                optic->render_sprite(sprite_handle, queue_handle);
            }
            catch(...) {
                luaL_error(state, "invalid arguments in harmony render_sprite function");
            }
        }
        else if(args == 6 || args == 7 || args == 8) {
            // Arguments
            auto sprite_handle = luaL_checkinteger(state, 1);
            float pos_x = luaL_checknumber(state, 2);
            float pos_y = luaL_checknumber(state, 3);
            int opacity = luaL_checknumber(state, 4);
            float rotation = RADIAN(luaL_checknumber(state, 5));
            long duration = luaL_checknumber(state, 6);
            
            Optic::Animation fade_in;
            if(args >= 7) {
                auto *anim = optic->get_animation(luaL_checkinteger(state, 7));
                if(anim) {
                    fade_in = *anim;
                }
                else {
                    luaL_error(state, "invalid fade-in animation handle in harmony render_sprite function");
                }
            }

            Optic::Animation fade_out;
            if(args == 8) {
                auto *anim = optic->get_animation(luaL_checkinteger(state, 8));
                if(anim) {
                    fade_out = *anim;
                }
                else {
                    luaL_error(state, "invalid fade-out animation handle in harmony render_sprite function");
                }
            }

            // Set initial state of sprite
            Optic::Sprite::State initial_state;
            initial_state.position = {pos_x, pos_y};
            initial_state.color.a = opacity;
            initial_state.rotation = rotation;

            try {
                // Render it!
                optic->render_sprite(sprite_handle, initial_state, duration, fade_in, fade_out);
            }
            catch(...) {
                luaL_error(state, "invalid sprite handle in harmony render_sprite function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony render_sprite function");
        }
        return 0;
    }

    static int lua_clear_render_queue(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 1) {
            // Arguments
            auto handle = luaL_checkinteger(state, 1);

            auto *queue = optic->get_render_queue(handle);
            if(queue) {
                queue->clear();
            }
            else {
                luaL_error(state, "invalid render queue handle in harmony clear_queue_renders function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony clear_queue_renders function");
        }
        return 0;
    }

    static int lua_create_sound(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 1) {
            // Arguments
            std::string sound_path = std::string(script->get_data_path()) + "\\" + luaL_checkstring(state, 1);

            if(script->path_is_valid(sound_path)) {
                if(std::filesystem::exists(sound_path)) {
                    auto handle = optic->create_sound(sound_path);
                    
                    lua_pushinteger(state, handle);
                    return 1;
                }
                else {
                    luaL_error(state, "sound file does not exists in harmony create_sound function");
                }
            }
            else {
                luaL_error(state, "invalid sound path in harmony create_sound function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony create_sound function");
        }
        return 0;
    }

    static int lua_create_audio_engine(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 0) {    
            auto handle = optic->create_audio_engine();

            lua_pushinteger(state, handle);
            return 1;
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony create_audio_engine function");
        }
        return 0;
    }
    
    static int lua_play_sound(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 2 || args == 3) {    
            // Arguments
            auto sound_handle = luaL_checkinteger(state, 1);
            auto audio_engine_handle = luaL_checkinteger(state, 2);
            bool no_enqueue = false;
            
            if(args == 3) {
                no_enqueue = lua_toboolean(state, 3);
            }

            try {
                optic->play_sound(sound_handle, audio_engine_handle, no_enqueue);
            }
            catch(...) {
                luaL_error(state, "invalid argument(s) in play_sound function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony play_sound function");
        }
        return 1;
    }

    static int lua_clear_audio_engine(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 1) {    
            // Arguments
            auto playback_queue_handle = luaL_checkinteger(state, 1);

            auto *playback_queue = optic->get_audio_engine(playback_queue_handle);
            if(playback_queue) {
                playback_queue->stopAll();
            }
            else {
                luaL_error(state, "invalid audio engine handle in harmony clear_audio_engine function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony clear_audio_engine function");
        }
        return 0;
    }

    static int lua_set_audio_engine_gain(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 2) {    
            // Arguments
            auto engine_handle = luaL_checkinteger(state, 1);
            auto gain = luaL_checkinteger(state, 2);

            auto *playback_queue = optic->get_audio_engine(engine_handle);
            if(playback_queue) {
                if(gain > 100) {
                    gain = 100;
                }
                playback_queue->setGlobalVolume(static_cast<float>(gain) / 100);
            }
            else {
                luaL_error(state, "invalid audio engine handle in harmony set_audio_engine_gain function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony set_audio_engine_gain function");
        }
        return 0;
    }

    static const luaL_Reg optic[] = {
        {"create_animation", lua_create_animation},
        {"set_animation_property", lua_set_animation_property},
        {"create_sprite", lua_create_sprite},
        {"create_render_queue", lua_create_render_queue},
        {"render_sprite", lua_render_sprite},
        {"clear_render_queue", lua_clear_render_queue},
        {"create_sound", lua_create_sound},
        {"create_audio_engine", lua_create_audio_engine},
        {"play_sound", lua_play_sound},
        {"clear_audio_engine", lua_clear_audio_engine},
        {"set_audio_engine_gain", lua_set_audio_engine_gain},
        {NULL, NULL}
    };

    void set_optic_functions(lua_State *state) noexcept {
        auto &harmony = Harmony::get();
        library = &harmony.get_lua_library_handler();
        optic_handler = &harmony.get_optic_handler();

        lua_create_functions_table(state, "optic", optic);
    }
}