// SPDX-License-Identifier: GPL-3.0-only

#include <algorithm>
#include "lua_callback.hpp"
#include "lua_script.hpp"
#include "lua_optic.hpp"
#include "../harmony.hpp"
#include "library.hpp"

namespace Harmony::Lua {
    int luaopen_mods_harmony(lua_State *state) noexcept {
        lua_newtable(state);

        // Set callback functions
        set_callback_functions(state);
        lua_settable(state, -3);

        // Set optic functions
        set_optic_functions(state);
        lua_settable(state, -3);

        auto &harmony = get_harmony();
        auto &scripts = harmony.get_lua_scripts();

        auto *script = harmony.get_lua_script(Script::get_global(state, "script_name").c_str());
        if(script) {
            if(script->get_state() != state) {
                *script = Script(state);
            }
        }
        else {
            scripts.emplace_back(state);
        }
        
        return 1;
    }
}
