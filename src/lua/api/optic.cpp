// SPDX-License-Identifier: GPL-3.0-only

#include <filesystem>
#include "../../halo_data/resolution.hpp"
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

    /**
     * Get a prefix for each optics based on the script name
     * @return  Optic name prefix
     */
    static std::string get_optic_prefix(lua_State *state) noexcept {
        auto prefix = Script::get_global_from_state(state, "script_name") + "_";
        return prefix;
    }

    static int lua_register_animation(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            auto *script = library->get_script(state);
            auto &store = script->get_optic_store();
            
            const char *name = luaL_checkstring(state, 1);
            long duration = luaL_checknumber(state, 2);
            if(!store.get_animation(name)) {
                store.add_animation(name, Optic::Animation(Optic::Animation::StateTransform(), duration));
            }
            else {
                luaL_error(state, "invalid animation name. Animation already exists!");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony register_animation function");
        }
        return 0;
    }

    static int lua_add_animation_target(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 4 || args == 7) {
            auto *script = library->get_script(state);
            auto &store = script->get_optic_store();

            auto *anim = store.get_animation(luaL_checkstring(state, 1));
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
                        luaL_error(state, "invalid curve preset name in harmony add_animation_curve function");
                    }
                }
                else {
                    float x1 = luaL_checknumber(state, 2);
                    float x2 = luaL_checknumber(state, 3);
                    float y1 = luaL_checknumber(state, 4);
                    float y2 = luaL_checknumber(state, 5);
                    curve = Math::QuadraticBezier({x1, x2}, {y1, y2});
                }

                auto target = Optic::Animation::get_target_from_string(luaL_checkstring(state, -2));
                if(target != Optic::Animation::TARGET_INVALID) {
                    auto transform = anim->get_transform();
                    switch(target) {
                        case Optic::Animation::TARGET_POSITION_X:
                            transform.position.x = luaL_checknumber(state, -1);
                            break;
                        case Optic::Animation::TARGET_POSITION_Y:
                            transform.position.y = luaL_checknumber(state, -1);
                            break;
                        case Optic::Animation::TARGET_OPACITY:
                            transform.opacity = luaL_checknumber(state, -1);
                            break;
                        case Optic::Animation::TARGET_ROTATION:
                            transform.rotation = RADIAN(luaL_checknumber(state, -1));
                            break;
                        case Optic::Animation::TARGET_SCALE_X:
                            transform.scale.x = luaL_checknumber(state, -1);
                            break;
                        case Optic::Animation::TARGET_SCALE_Y:
                            transform.scale.y = luaL_checknumber(state, -1);
                            break;
                    }

                    anim->add_target(target, curve);
                    anim->set_transform(transform);
                }
                else {
                    luaL_error(state, "invalid target in harmony add_animation_curve function");
                }
            }
            else {
                luaL_error(state, "invalid animation name in harmony add_animation_curve function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony add_animation_curve function");
        }
        return 0;
    }

    static int lua_register_sprite(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 4 || args == 5) {
            auto *script = library->get_script(state);
            auto &store = script->get_optic_store();

            const char *name = luaL_checkstring(state, 1);
            std::string texture_path = std::string(script->get_data_path()) + "\\" + luaL_checkstring(state, 2);
            int width = luaL_checknumber(state, 3);
            int height = luaL_checknumber(state, 4);

            if(!store.get_sprite(name)) {
                // check if the texture file exists
                if(script->path_is_valid(texture_path)) {
                    if(std::filesystem::exists(texture_path)) {
                        if(args == 5){
                            std::string sound_path = std::string(script->get_data_path()) + "\\" + luaL_checkstring(state, 5);
                            if(script->path_is_valid(sound_path)) {
                                if(std::filesystem::exists(sound_path)) {
                                    store.add_sprite(name, Optic::Sprite(texture_path.c_str(), width, height), sound_path);
                                }
                                else {
                                    luaL_error(state, "sound file does not exists in harmony register_sprite function");
                                }
                            }
                        }
                        else {
                            store.add_sprite(name, Optic::Sprite(texture_path.c_str(), width, height));
                        }
                    }
                    else {
                        luaL_error(state, "texture does not exists in harmony register_sprite function");
                    }
                }
                else {
                    luaL_error(state, "invalid texture path in harmony register_sprite function");
                }
            }
            else {
                luaL_error(state, "invalid name for sprite in harmony register_sprite function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony register_sprite function");
        }
        return 0;
    }

    static int lua_create_group(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args >= 7 && args <= 10) {
            auto name = get_optic_prefix(state) + luaL_checkstring(state, 1);
            if(!optic_handler->get_render_group(name.c_str())) {
                auto *script = library->get_script(state);
                auto &store = script->get_optic_store();

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

                // Create group
                auto &group = optic_handler->add_render_group(name.c_str(), initial_state, 0, max_renders, duration, false);

                // Register group
                store.register_group(name);

                if(args >= 8) {
                    auto *fade_in = store.get_animation(luaL_checkstring(state, 8));
                    if(fade_in) {
                        group.set_fade_in_anim(*fade_in);
                    }
                    else {
                        luaL_error(state, "invalid fade-in animation name is harmony add_animation_curve function");
                    }
                }

                if(args >= 9) {
                    auto *fade_out = store.get_animation(luaL_checkstring(state, 9));
                    if(fade_out) {
                        group.set_fade_out_anim(*fade_out);
                    }
                    else {
                        luaL_error(state, "invalid fade-out animation name is harmony add_animation_curve function");
                    }
                }

                if(args == 10) {
                    auto *slide = store.get_animation(luaL_checkstring(state, 10));
                    if(slide) {
                        group.set_slide_anim(*slide);
                    }
                    else {
                        luaL_error(state, "invalid slide animation name is harmony add_animation_curve function");
                    }
                }
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony add_group function");
        }
        return 0;
    }

    static int lua_render_sprite(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            auto group_name = get_optic_prefix(state) + luaL_checkstring(state, 1);
            if(optic_handler->get_render_group(group_name.c_str())) {
                auto *script = library->get_script(state);
                auto &store = script->get_optic_store();

                auto *sprite = store.get_sprite(luaL_checkstring(state, 2));
                if(sprite) {
                    optic_handler->render_sprite(sprite, group_name.c_str());
                }
                else {
                    luaL_error(state, "invalid sprite in harmony render_sprite function");
                }
            }
            else {
                luaL_error(state, "invalid group in harmony render_sprite function");
            }
        }
        else if(args == 6 || args == 7 || args == 8) {
            auto *script = library->get_script(state);
            auto &store = script->get_optic_store();

            auto *sprite = store.get_sprite(luaL_checkstring(state, 1));
            if(sprite) {
                float pos_x = luaL_checknumber(state, 2);
                float pos_y = luaL_checknumber(state, 3);
                int opacity = luaL_checknumber(state, 4);
                float rotation = RADIAN(luaL_checknumber(state, 5));
                long duration = luaL_checknumber(state, 6);
                
                Optic::Animation fade_in;
                if(args >= 7) {
                    auto *anim = store.get_animation(luaL_checkstring(state, 7));
                    if(anim) {
                        fade_in = *anim;
                    }
                    else {
                        luaL_error(state, "invalid fade-in animation in harmony render_sprite function");
                    }
                }

                Optic::Animation fade_out;
                if(args == 8) {
                    auto *anim = store.get_animation(luaL_checkstring(state, 8));
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

                // Render it!
                optic_handler->render_sprite(sprite, initial_state, duration, fade_in, fade_out);
            }
            else {
                luaL_error(state, "invalid sprite in harmony render_sprite function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony render_sprite function");
        }
        return 0;
    }

    static int lua_clear_renders(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 1) {
            auto name = get_optic_prefix(state) + luaL_checkstring(state, 1);
            auto *group = optic_handler->get_render_group(name.c_str());
            if(group) {
                group->get_renders().clear();
            }
            else {
                luaL_error(state, "invalid group name in harmony clear_renders function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony clear_renders function");
        }
        return 0;
    }

    static const struct luaL_Reg optic[] = {
        {"register_animation", lua_register_animation},
        {"add_animation_target", lua_add_animation_target},
        {"register_sprite", lua_register_sprite},
        {"create_group", lua_create_group},
        {"render_sprite", lua_render_sprite},
        {"clear_group_renders", lua_clear_renders},
        {NULL, NULL}
    };

    void set_optic_functions(lua_State *state) noexcept {
        if(!library && !optic_handler) {
            auto &harmony = get_harmony();
            library = &(harmony.get_lua_library_handler());
            optic_handler = &(harmony.get_optic_handler());
        }

        lua_pushstring(state, "optic");
        luaL_newlibtable(state, optic);
        luaL_setfuncs(state, optic, 0);

        lua_settable(state, -3);
    }
}