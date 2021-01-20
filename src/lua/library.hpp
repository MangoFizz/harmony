// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_API
#define HARMONY_LUA_API

#include <lua.hpp>

namespace Harmony::Lua {
    /**
     * Lua library entry point
     */
    extern "C" __declspec(dllexport) int luaopen_mods_harmony(lua_State *state) noexcept;
}

#endif 
