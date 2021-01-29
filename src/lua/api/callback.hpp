// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_API_CALLBACK_HPP
#define HARMONY_LUA_API_CALLBACK_HPP

#include <lua.hpp>

namespace Harmony::Lua {
    /**
     * Set callback functions in script
     */
    void set_callback_functions(lua_State *state) noexcept;
}


#endif
