// SPDX-License-Identifier: GPL-3.0-only

#include "../../harmony.hpp"
#include "../library.hpp"
#include "../helpers.hpp"
#include "time.hpp"

namespace Harmony::Lua {
    static Library *library = nullptr;

    static int lua_set_timestamp(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 1) {
            auto *script = library->get_script(state);
            auto &store = script->get_time_api_store();
            auto &timestamps = store.timestamps;

            auto *timestamp_name = luaL_checkstring(state, 1);

            timestamps.insert_or_assign(timestamp_name, std::chrono::steady_clock::now());

            return 0;
        }
        else {
            return luaL_error(state, "invalid number of arguments in harmony set_timestamp function");
        }
    }

    static int lua_get_elapsed_milliseconds(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 1) {
            auto *script = library->get_script(state);
            auto &store = script->get_time_api_store();
            auto &timestamps = store.timestamps;

            auto *name = luaL_checkstring(state, 1);
            if(timestamps.find(name) == timestamps.end()) {
                return luaL_error(state, "invalid timestamp name in harmony get_elapsed_milliseconds function");
            }

            auto const &timestamp = timestamps[name];
            auto elapsed_time = std::chrono::steady_clock::now() - timestamp;
            auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time);

            lua_pushinteger(state, elapsed_milliseconds.count());

            return 1;
        }
        else {
            return luaL_error(state, "invalid number of arguments in harmony get_elapsed_milliseconds function");
        }
    }

    static int lua_get_elapsed_seconds(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 1) {
            auto *script = library->get_script(state);
            auto &store = script->get_time_api_store();
            auto &timestamps = store.timestamps;

            auto *name = luaL_checkstring(state, 1);
            if(timestamps.find(name) == timestamps.end()) {
                return luaL_error(state, "invalid timestamp name in harmony get_elapsed_seconds function");
            }

            auto const &timestamp = timestamps[name];
            auto elapsed_time = std::chrono::steady_clock::now() - timestamp;
            auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed_time);

            lua_pushinteger(state, elapsed_milliseconds.count());

            return 1;
        }
        else {
            return luaL_error(state, "invalid number of arguments in harmony get_elapsed_seconds function");
        }
    }

    static const luaL_Reg time[] = {
        {"set_timestamp", lua_set_timestamp},
        {"get_elapsed_milliseconds", lua_get_elapsed_milliseconds},
        {"get_elapsed_seconds", lua_get_elapsed_seconds},
        {NULL, NULL}
    };

    void set_time_api(lua_State *state) noexcept {
        // Register functions table
        lua_create_functions_table(state, "time", time);

        // Get library handler
        auto &harmony = Harmony::get();
        library = &harmony.get_lua_library_handler();
    }
}