// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_API_MULTIPLAYER_HPP
#define HARMONY_LUA_API_MULTIPLAYER_HPP

#include <lua.hpp>

namespace Harmony::Lua {
    /**
     * Set multiplayer Lua API into a given Lua stack
     */
    void set_multiplayer_api(lua_State *state) noexcept;
}

#endif
