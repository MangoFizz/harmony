// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_API_MISC_HPP
#define HARMONY_LUA_API_MISC_HPP

#include <lua.hpp>

namespace Harmony::Lua {
    /**
     * Set miscellaneous Lua functions into a given Lua stack
     */
    void set_misc_functions(lua_State *state) noexcept;
}

#endif
