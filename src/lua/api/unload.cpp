// SPDX-License-Identifier: GPL-3.0-only

#include <string>
#include <lua.hpp>
#include "../library.hpp"
#include "../../menu/widescreen_override.hpp"
#include "../../harmony.hpp"
#include "unload.hpp"

namespace Harmony::Lua {
    int lua_unload_script(lua_State *state) noexcept {
        auto &harmony = get_harmony();
        auto &library = harmony.get_lua_library_handler();
        auto *script = library.get_script(state);
        if(strcmp(script->get_type(), "map") == 0) {
            /**
             * Restore UI frame aspect ratio before map script unload.
             * We can't put this in a map load callback because our event
             * is executed after Chimera's map load event, so our map 
             * script will load BEFORE we can restore the aspect ratio.
             */
            harmony.get_widescreen_override_handle().reset_frame_aspect_ratio();
        }
        library.unload_script(state);
        return 0;
    }

    void set_unload_functions(lua_State *state) noexcept {
        lua_pushstring(state, "unload");
        lua_pushcfunction(state, lua_unload_script);

        lua_settable(state, -3);
    }
}