// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_API_UNLOAD_HPP
#define HARMONY_LUA_API_UNLOAD_HPP

#include <lua.hpp>

namespace Harmony::Lua {
    /**
     * Set unload function in script
     */
    void set_unload_functions(lua_State *state) noexcept;
}


#endif
