// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_API_SERVER_HPP
#define HARMONY_LUA_API_SERVER_HPP

#include <lua.hpp>

namespace Harmony::Lua {
    /**
     * Set server Lua API into a given Lua stack
     */
    void set_server_functions(lua_State *state) noexcept;
}

#endif
