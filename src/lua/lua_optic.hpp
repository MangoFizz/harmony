// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_OPTIC_HPP
#define HARMONY_LUA_OPTIC_HPP

#include <string>
#include <map>
#include <lua.hpp>
#include "../math/geometry.hpp"
#include "../optic/animation.hpp"
#include "../optic/sprite.hpp"

namespace Harmony::Lua {
    struct OpticStore {
        /** Animations */
        std::map<std::string, Optic::Animation> animations;

        /** Sprites */
        std::map<std::string, Optic::Sprite> sprites;
    };
    
    /**
     * Set Optic Lua API into a given Lua stack
     */
    void set_optic_functions(lua_State *state) noexcept;
}

#endif
