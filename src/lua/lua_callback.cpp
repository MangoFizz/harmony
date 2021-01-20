// SPDX-License-Identifier: GPL-3.0-only

#include <string>
#include <lua.hpp>
#include "../events/multiplayer_sound.hpp"
#include "../harmony.hpp"
#include "lua_script.hpp"
#include "lua_callback.hpp"

namespace Harmony::Lua {
    static bool multiplayer_sound_event(HaloData::MultiplayerSound sound) noexcept {
        auto &scripts = get_harmony().get_lua_scripts();
        bool allow = true;
        for(auto &script : scripts) {
            auto *state = script.get_state();
            auto &callbacks = script.get_callbacks("multiplayer sound");
            for(auto &callback : callbacks) {
                lua_getglobal(state, callback.c_str());
                lua_pushstring(state, HaloData::string_from_multiplayer_sound(sound).c_str());
                if(lua_pcall(state, 1, 1, 0) == 0) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
                }
            }
        }
        return allow;
    }

    void set_up_c_callbacks() noexcept {
        add_multiplayer_sound_event(multiplayer_sound_event);
    }

    int lua_set_callback(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            std::string callback = luaL_checkstring(state, 1);
            std::string function = luaL_checkstring(state, 2);

            if(callback == "multiplayer sound") {
                auto &harmony = get_harmony();
                auto *script  = harmony.get_lua_script(state);
                script->register_callback_function(callback.c_str(), function.c_str());
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
    }
}