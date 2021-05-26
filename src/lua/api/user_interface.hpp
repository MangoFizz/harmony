// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_API_USER_INTERFACE_HPP
#define HARMONY_LUA_API_USER_INTERFACE_HPP

#include <lua.hpp>

namespace Harmony::Lua {
    /**
     * Set UI Lua API into a given Lua stack
     */
    void set_user_interface_functions(lua_State *state) noexcept;
}

#endif
