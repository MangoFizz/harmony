// SPDX-License-Identifier: GPL-3.0-only

#include <string>
#include <lua.hpp>
#include "../library.hpp"
#include "../../harmony.hpp"
#include "callback.hpp"

namespace Harmony::Lua {
    int lua_set_callback(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            std::string callback_name = luaL_checkstring(state, 1);
            std::string function = luaL_checkstring(state, 2);

            auto callback_exists = [callback_name]() {
                #define CHECK_CALLBACK(callback) (callback == callback_name) {}

                if CHECK_CALLBACK("multiplayer event")
                else if CHECK_CALLBACK("multiplayer sound")
                else if CHECK_CALLBACK("menu accept")
                else if CHECK_CALLBACK("menu back")
                else if CHECK_CALLBACK("menu list tab")
                else if CHECK_CALLBACK("menu mouse button press")
                else if CHECK_CALLBACK("menu sound")
                else return false;
                return true;
            };

            if(callback_exists()) {
                auto &harmony = Harmony::get();
                auto &handler = harmony.get_lua_library_handler();
                auto *script  = handler.get_script(state);
                script->add_callback(callback_name, function);
            }
            else {
                luaL_error(state, "invalid callback in harmony set_callback function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony set_callback function");
        }
        return 0;
    }

    void set_callback_functions(lua_State *state) noexcept {
        lua_pushstring(state, "set_callback");
        lua_pushcfunction(state, lua_set_callback);
     
        lua_settable(state, -3);
    }
}