// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_API_OPTIC_HPP
#define HARMONY_LUA_API_OPTIC_HPP

#include <lua.hpp>

namespace Harmony::Lua {
    /**
     * Set Optic Lua API into a given Lua stack
     */
    void set_optic_functions(lua_State *state) noexcept;
}

#endif
