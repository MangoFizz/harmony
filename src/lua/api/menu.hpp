// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_API_MENU_HPP
#define HARMONY_LUA_API_MENU_HPP

#include <lua.hpp>
#include "../../halo_data/widget.hpp"

namespace Harmony::Lua {
    /**
     * Set UI Lua API into a given Lua stack
     */
    void set_menu_functions(lua_State *state) noexcept;
}

#endif
