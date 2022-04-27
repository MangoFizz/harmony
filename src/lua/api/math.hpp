// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_API_MATH_HPP
#define HARMONY_LUA_API_MATH_HPP

#include <string>
#include <vector>
#include <lua.hpp>
#include "../../math/geometry.hpp"

namespace Harmony::Lua {
    struct ScriptMathApiStore {
        /** Bezier curves */
        std::vector<Math::QuadraticBezier> curves; 
    };

    /**
     * Set math Lua API into a given Lua stack
     */
    void set_math_api(lua_State *state) noexcept;
}

#endif
