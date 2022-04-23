// SPDX-License-Identifier: GPL-3.0-only

#include "../../optic/animation.hpp"
#include "../../harmony.hpp"
#include "../library.hpp"
#include "../helpers.hpp"
#include "math.hpp"

namespace Harmony::Lua {
    static Library *library = nullptr;

    static int lua_create_bezier_curve(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2 || args == 5) {
            auto *script = library->get_script(state);
            auto &container = script->get_math_container();
            auto &curves = container.curves;

            auto *name = luaL_checkstring(state, 1);
            if(curves.find(name) != curves.end()) {
                return luaL_error(state, "invalid curve name in harmony create_bezier_curve function");
            }

            Math::QuadraticBezier curve;
            if(args == 2) {
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
                    luaL_error(state, "invalid curve name in harmony create_bezier_curve function");
                }
            }
            else {
                float x1 = luaL_checknumber(state, 2);
                float y1 = luaL_checknumber(state, 3);
                float x2 = luaL_checknumber(state, 4);
                float y2 = luaL_checknumber(state, 5);
                curve = Math::QuadraticBezier({x1, y1}, {x2, y2});
            }

            curves.insert_or_assign(name, curve);

            return 0;
        }
        else {
            return luaL_error(state, "invalid number of arguments in harmony create_bezier_curve function");
        }
    }

    static int lua_interpolate_value(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 4) {
            auto *script = library->get_script(state);
            auto &container = script->get_math_container();
            auto &curves = container.curves;

            auto *name = luaL_checkstring(state, 1);
            auto initial_value = luaL_checkinteger(state, 2);
            auto final_value = luaL_checkinteger(state, 3);
            float t = luaL_checknumber(state, 4);

            // fool proof
            if(t > 1.0f) {
                t = 1;
            }
            else if(t < 0.0f) {
                t = 0;
            }
            
            if(curves.find(name) == curves.end()) {
                return luaL_error(state, "invalid curve name in harmony interpolate_value function");
            }

            auto &curve = curves[name];
            auto point = curve.get_point(t);

            float transform = point.y * (final_value - initial_value);
            float result = transform + initial_value;
            lua_pushnumber(state, result);

            return 1;
        }
        else {
            return luaL_error(state, "invalid number of arguments in harmony interpolate_value function");
        }
    }

    static const luaL_Reg math[] = {
        {"create_bezier_curve", lua_create_bezier_curve},
        {"interpolate_value", lua_interpolate_value},
        {NULL, NULL}
    };

    void set_math_api(lua_State *state) noexcept {
        // Register functions table
        lua_create_functions_table(state, "math", math);

        // Get library handler
        auto &harmony = Harmony::get();
        library = &harmony.get_lua_library_handler();
    }
}