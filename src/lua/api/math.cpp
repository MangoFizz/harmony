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
        if(args == 1 || args == 4) {
            auto *script = library->get_script(state);
            auto &store = script->get_math_api_store();
            auto &curves = store.curves;

            Math::QuadraticBezier curve;
            if(args == 1) {
                std::string preset = luaL_checkstring(state, 1);
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
                float x1 = luaL_checknumber(state, 1);
                float y1 = luaL_checknumber(state, 2);
                float x2 = luaL_checknumber(state, 3);
                float y2 = luaL_checknumber(state, 4);
                curve = Math::QuadraticBezier({x1, y1}, {x2, y2});
            }

            curves.push_back(curve);
            lua_pushinteger(state, curves.size() - 1);

            return 1;
        }
        else {
            return luaL_error(state, "invalid number of arguments in harmony create_bezier_curve function");
        }
    }

    static int lua_get_bezier_curve_point(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 4 || args == 5) {
            auto *script = library->get_script(state);
            auto &store = script->get_math_api_store();
            auto &curves = store.curves;

            std::size_t handle = luaL_checkinteger(state, 1);
            auto initial_value = luaL_checkinteger(state, 2);
            auto final_value = luaL_checkinteger(state, 3);
            float t = luaL_checknumber(state, 4);
            
            bool reverse = false;
            if(args == 5) {
                reverse = lua_toboolean(state, 5);
            }

            if(handle > curves.size()) {
                return luaL_error(state, "invalid curve handle in harmony get_bezier_curve_point function");
            }

            // fool proof
            if(t > 1.0f) {
                t = 1;
            }
            else if(t < 0.0f) {
                t = 0;
            }

            auto &curve = curves[handle];
            auto point = curve.get_point(t, reverse);

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
        {"get_bezier_curve_point", lua_get_bezier_curve_point},
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