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
    static Optic::Handler *optic_handler = nullptr;

    static Script *get_script(lua_State *state) {
        auto &harmony = get_harmony();
        auto &handler = harmony.get_lua_library_handler();
        return handler.get_script(state);
    }

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
            auto *script = get_script(state);
            auto &optic_store = script->get_optic_store();
            auto &animations = optic_store.animations;
            
            const char *name = luaL_checkstring(state, 1);
            long duration = luaL_checknumber(state, 2);
            if(animations.find(name) == animations.end()) {
                animations[name] = Optic::Animation(Optic::Animation::StateTransform(), duration);
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
            auto *script = get_script(state);
            auto &optic_store = script->get_optic_store();
            auto &animations = optic_store.animations;

            const char *animation_name = luaL_checkstring(state, 1);
            auto target = Optic::Animation::get_target_from_string(luaL_checkstring(state, 2));

            if(animations.find(animation_name) != animations.end()) {
                if(target != Optic::Animation::TARGET_INVALID) {
                    Math::QuadraticBezier curve;
                    if(args == 4) {
                        std::string preset = luaL_checkstring(state, 3);
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
                        float x1 = luaL_checknumber(state, 3);
                        float x2 = luaL_checknumber(state, 4);
                        float y1 = luaL_checknumber(state, 5);
                        float y2 = luaL_checknumber(state, 6);
                        curve = Math::QuadraticBezier({x1, x2}, {y1, y2});
                    }

                    auto transform = animations[animation_name].get_transform();
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
                            transform.rotation = luaL_checknumber(state, -1);
                            break;
                    }

                    animations[animation_name].add_target(target, curve);
                    animations[animation_name].set_transform(transform);
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
        if(args == 4) {
            auto *script = get_script(state);
            auto &optic_store = script->get_optic_store();
            auto &sprites = optic_store.sprites;

            const char *name = luaL_checkstring(state, 1);
            std::string texture_path = std::string(script->get_data_path()) + "\\" + luaL_checkstring(state, 2);
            int width = luaL_checknumber(state, 3);
            int height = luaL_checknumber(state, 4);


            // check if the texture file exists
            if(sprites.find(name) == sprites.end()) {
                if(script->path_is_valid(texture_path)) {
                    if(std::filesystem::exists(texture_path)) {
                        sprites[name] = Optic::Sprite(texture_path.c_str(), width, height);
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

    static int lua_add_group(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args >= 5 && args <= 8) {
            auto name = get_optic_prefix(state) + luaL_checkstring(state, 1);
            if(!optic_handler->get_render_group(name.c_str())) {
                auto *script = get_script(state);
                auto &optic_store = script->get_optic_store();
                auto &animations = optic_store.animations;

                float pos_x = luaL_checknumber(state, 2);
                float pos_y = luaL_checknumber(state, 3);
                int opacity = luaL_checknumber(state, 4);
                long duration = luaL_checknumber(state, 5);

                auto &group = optic_handler->add_render_group(name.c_str(), {pos_x, pos_y}, opacity, 0, Optic::RenderGroup::ALIGN_LEFT, duration);

                if(args >= 6) {
                    const char *fade_in = luaL_checkstring(state, 6);
                    if(animations.find(fade_in) != animations.end()) {
                        group.set_fade_in_anim(animations[fade_in]);
                    }
                    else {
                        luaL_error(state, "invalid fade-in animation name is harmony add_animation_curve function");
                    }
                }

                if(args >= 7) {
                    const char *fade_out = luaL_checkstring(state, 7);
                    if(animations.find(fade_out) != animations.end()) {
                        group.set_fade_out_anim(animations[fade_out]);
                    }
                    else {
                        luaL_error(state, "invalid fade-out animation name is harmony add_animation_curve function");
                    }
                }

                if(args == 8) {
                    const char *slide = luaL_checkstring(state, 8);
                    if(animations.find(slide) != animations.end()) {
                        group.set_slide_anim(animations[slide]);
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
                auto *script = get_script(state);
                auto &optic_store = script->get_optic_store();
                auto &sprites = optic_store.sprites;

                const char *sprite_name = luaL_checkstring(state, 2);
                if(sprites.find(sprite_name) != sprites.end()) {
                    optic_handler->render_sprite(&sprites[sprite_name], group_name.c_str());
                }
                else {
                    luaL_error(state, "invalid sprite in harmony render_sprite function");
                }
            }
            else {
                luaL_error(state, "invalid group in harmony render_sprite function");
            }
        }
        else if(args == 5 || args == 6 || args == 7) {
            auto *script = get_script(state);
            auto &optic_store = script->get_optic_store();
            auto &sprites = optic_store.sprites;
            auto &animations = optic_store.animations;

            const char *sprite_name = luaL_checkstring(state, 1);
            if(sprites.find(sprite_name) != sprites.end()) {
                float pos_x = luaL_checknumber(state, 2);
                float pos_y = luaL_checknumber(state, 3);
                int opacity = luaL_checknumber(state, 4);
                long duration = luaL_checknumber(state, 5);
                
                Optic::Animation fade_in;
                Optic::Animation fade_out;

                if(args >= 6) {
                    const char *fade_in_name = luaL_checkstring(state, 6);
                    if(animations.find(fade_in_name) != animations.end()) {
                        fade_in = animations[fade_in_name];
                    }
                    else {
                        luaL_error(state, "invalid fade-in animation in harmony render_sprite function");
                    }
                }

                if(args == 7) {
                    const char *fade_out_name = luaL_checkstring(state, 7);
                    if(animations.find(fade_out_name) != animations.end()) {
                        fade_in = animations[fade_out_name];
                    }
                    else {
                        luaL_error(state, "invalid fade-out animation in harmony render_sprite function");
                    }
                }

                optic_handler->render_sprite(&sprites[sprite_name], {pos_x, pos_y}, opacity, 0, Optic::RenderGroup::ALIGN_LEFT, duration, fade_in, fade_out);
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
        {"add_group", lua_add_group},
        {"render_sprite", lua_render_sprite},
        {"clear_renders", lua_clear_renders},
        {NULL, NULL}
    };

    void set_optic_functions(lua_State *state) noexcept {
        if(!optic_handler) {
            optic_handler = &(get_harmony().get_optic_handler());
        }

        lua_pushstring(state, "optic");
        luaL_newlibtable(state, optic);
        luaL_setfuncs(state, optic, 0);

        lua_settable(state, -3);
    }
}