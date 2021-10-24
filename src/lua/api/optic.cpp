// SPDX-License-Identifier: GPL-3.0-only

#include <filesystem>
#include "../../math/geometry.hpp"
#include "../../optic/animation.hpp"
#include "../../optic/handler.hpp"
#include "../../optic/render.hpp"
#include "../../harmony.hpp"
#include "../script.hpp"
#include "../library.hpp"
#include "optic.hpp"

namespace Harmony::Lua {
    static Library *library = nullptr;
    static Optic::Handler *optic_handler = nullptr;

    static int lua_create_animation(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 2) {
            // Arguments
            const char *name = luaL_checkstring(state, 1);
            long duration = luaL_checknumber(state, 2);

            try {
                optic->create_animation(name, duration);
            }
            catch(...) {
                luaL_error(state, "invalid animation name in create_animation function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony create_animation function");
        }
        return 0;
    }

    static int lua_set_animation_property(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 4 || args == 7) {
            auto *anim = optic->get_animation(luaL_checkstring(state, 1));
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
                    float x2 = luaL_checknumber(state, 3);
                    float y1 = luaL_checknumber(state, 4);
                    float y2 = luaL_checknumber(state, 5);
                    curve = Math::QuadraticBezier({x1, x2}, {y1, y2});
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
        if(args == 4) {
            // Arguments
            const char *name = luaL_checkstring(state, 1);
            std::string texture_path = std::string(script->get_data_path()) + "\\" + luaL_checkstring(state, 2);
            int width = luaL_checknumber(state, 3);
            int height = luaL_checknumber(state, 4);

            if(script->path_is_valid(texture_path)) {
                if(std::filesystem::exists(texture_path)) {
                    try {
                        optic->create_sprite(name, texture_path, width, height);
                    }
                    catch(...) {
                        luaL_error(state, "invalid name for sprite in harmony create_sprite function");
                    }
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
        if(args >= 7 && args <= 10) {
            // Arguments
            auto name = luaL_checkstring(state, 1);
            float pos_x = luaL_checknumber(state, 2);
            float pos_y = luaL_checknumber(state, 3);
            int opacity = luaL_checknumber(state, 4);
            float rotation = luaL_checknumber(state, 5);
            long duration = luaL_checknumber(state, 6);
            int max_renders = luaL_checknumber(state, 7);

            // Set up initial sprite state
            Optic::Sprite::State initial_state;
            initial_state.position = {pos_x, pos_y};
            initial_state.color.a = opacity;
            initial_state.rotation = rotation;

            try {
                optic->create_render_queue(name, initial_state, rotation, max_renders, duration);
            }
            catch(...) {
                luaL_error(state, "invalid name for render queue in harmony create_render_queue function");
            }

            auto *queue = optic->get_render_queue(name);

            if(args >= 8) {
                auto *fade_in = optic->get_animation(luaL_checkstring(state, 8));
                if(fade_in) {
                    queue->set_fade_in_anim(*fade_in);
                }
                else {
                    luaL_error(state, "invalid fade-in animation name is harmony create_render_queue function");
                }
            }

            if(args >= 9) {
                auto *fade_out = optic->get_animation(luaL_checkstring(state, 9));
                if(fade_out) {
                    queue->set_fade_out_anim(*fade_out);
                }
                else {
                    luaL_error(state, "invalid fade-out animation name is harmony create_render_queue function");
                }
            }

            if(args == 10) {
                auto *slide = optic->get_animation(luaL_checkstring(state, 10));
                if(slide) {
                    queue->set_slide_anim(*slide);
                }
                else {
                    luaL_error(state, "invalid slide animation name is harmony create_render_queue function");
                }
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony create_render_queue function");
        }
        return 0;
    }

    static int lua_render_sprite(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 2) {
            // Arguments
            auto sprite_name = luaL_checkstring(state, 1);
            auto queue_name = luaL_checkstring(state, 2);

            try {
                optic->render_sprite(sprite_name, queue_name);
            }
            catch(...) {
                luaL_error(state, "invalid arguments in harmony render_sprite function");
            }
        }
        else if(args == 6 || args == 7 || args == 8) {
            // Arguments
            auto sprite_name = luaL_checkstring(state, 1);
            float pos_x = luaL_checknumber(state, 2);
            float pos_y = luaL_checknumber(state, 3);
            int opacity = luaL_checknumber(state, 4);
            float rotation = RADIAN(luaL_checknumber(state, 5));
            long duration = luaL_checknumber(state, 6);
            
            Optic::Animation fade_in;
            if(args >= 7) {
                auto *anim = optic->get_animation(luaL_checkstring(state, 7));
                if(anim) {
                    fade_in = *anim;
                }
                else {
                    luaL_error(state, "invalid fade-in animation in harmony render_sprite function");
                }
            }

            Optic::Animation fade_out;
            if(args == 8) {
                auto *anim = optic->get_animation(luaL_checkstring(state, 8));
                if(anim) {
                    fade_out = *anim;
                }
                else {
                    luaL_error(state, "invalid fade-out animation in harmony render_sprite function");
                }
            }

            // Set initial state of sprite
            Optic::Sprite::State initial_state;
            initial_state.position = {pos_x, pos_y};
            initial_state.color.a = opacity;
            initial_state.rotation = rotation;

            try {
                // Render it!
                optic->render_sprite(sprite_name, initial_state, duration, fade_in, fade_out);
            }
            catch(...) {
                luaL_error(state, "invalid sprite in harmony render_sprite function");
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
            auto name = luaL_checkstring(state, 1);

            auto *queue = optic->get_render_queue(name);
            if(queue) {
                queue->clear();
            }
            else {
                luaL_error(state, "invalid queue name in harmony clear_queue_renders function");
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
        if(args == 2) {
            // Arguments
            const char *name = luaL_checkstring(state, 1);
            std::string sound_path = std::string(script->get_data_path()) + "\\" + luaL_checkstring(state, 2);

            if(script->path_is_valid(sound_path)) {
                if(std::filesystem::exists(sound_path)) {
                    try {
                        optic->create_sound(name, sound_path);
                    }
                    catch(...) {
                        luaL_error(state, "invalid name for sprite in harmony create_sound function");
                    }
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

    static int lua_create_playback_queue(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 1) {    
            // Arguments
            const char *name = luaL_checkstring(state, 1);

            try {
                optic->create_audio_queue(name);
            }
            catch(...) {
                luaL_error(state, "invalid queue name in create_playback_queue function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony create_playback_queue function");
        }
        return 0;
    }
    
    static int lua_play_sound(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 2) {    
            // Arguments
            auto sound_name = luaL_checkstring(state, 1);
            auto playback_queue_name = luaL_checkstring(state, 2);

            auto *sound = optic->get_sound(sound_name);
            if(sound) {
                auto *playback_queue = optic->get_audio_queue(playback_queue_name);
                if(playback_queue) {
                    auto handle = playback_queue->play(*sound);
                    lua_pushnumber(state, handle);
                }
                else {
                    luaL_error(state, "invalid playback queue name in play_sound function");
                }
            }
            else {
                luaL_error(state, "invalid sound name in play_sound function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony play_sound function");
        }
        return 1;
    }

    static int lua_stop_sound(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 2) {    
            // Arguments
            auto playback_queue_name = luaL_checkstring(state, 1);
            auto sound_handle = luaL_checknumber(state, 2);

            auto *playback_queue = optic->get_audio_queue(playback_queue_name);
            if(playback_queue) {
                playback_queue->stop(sound_handle);
            }
            else {
                luaL_error(state, "invalid playback queue name in stop_sound function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony stop_sound function");
        }
        return 0;
    }

    static int lua_clear_playback_queue(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        auto *optic = script->get_optic_container();

        int args = lua_gettop(state);
        if(args == 1) {    
            // Arguments
            auto playback_queue_name = luaL_checkstring(state, 1);

            auto *playback_queue = optic->get_audio_queue(playback_queue_name);
            if(playback_queue) {
                playback_queue->stopAll();
            }
            else {
                luaL_error(state, "invalid playback queue name in stop_sound function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony stop_sound function");
        }
        return 0;
    }

    static const struct luaL_Reg optic[] = {
        {"create_animation", lua_create_animation},
        {"set_animation_property", lua_set_animation_property},
        {"create_sprite", lua_create_sprite},
        {"create_render_queue", lua_create_render_queue},
        {"render_sprite", lua_render_sprite},
        {"clear_render_queue", lua_clear_render_queue},
        {"create_sound", lua_create_sound},
        {"create_playback_queue", lua_create_playback_queue},
        {"play_sound", lua_play_sound},
        {"stop_sound", lua_stop_sound},
        {"clear_playback_queue", lua_clear_playback_queue},
        {NULL, NULL}
    };

    void set_optic_functions(lua_State *state) noexcept {
        if(!library && !optic_handler) {
            auto &harmony = Harmony::get();
            library = &(harmony.get_lua_library_handler());
            optic_handler = &(harmony.get_optic_handler());
        }

        lua_pushstring(state, "optic");
        luaL_newlibtable(state, optic);
        luaL_setfuncs(state, optic, 0);

        lua_settable(state, -3);
    }
}