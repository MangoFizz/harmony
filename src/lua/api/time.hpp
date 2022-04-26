// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_API_TIME_HPP
#define HARMONY_LUA_API_TIME_HPP

#include <string>
#include <map>
#include <chrono>
#include <lua.hpp>

namespace Harmony::Lua {
    struct ScriptTimeApiStore {
        /** Timestamps */
        std::map<std::string, std::chrono::steady_clock::time_point> timestamps;
    };

    /**
     * Set time Lua API into a given Lua stack
     */
    void set_time_api(lua_State *state) noexcept;
}

#endif
