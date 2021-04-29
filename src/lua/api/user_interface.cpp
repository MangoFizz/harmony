// SPDX-License-Identifier: GPL-3.0-only

#include "../../harmony.hpp"
#include "../script.hpp"
#include "../library.hpp"
#include "../../user_interface/widescreen_override.hpp"
#include "user_interface.hpp"

namespace Harmony::Lua {
    static int set_widescreen_aspect_ratio(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            static auto &harmony = get_harmony();
            auto &ws_override = harmony.get_widescreen_override_handle();

            std::uint16_t x = luaL_checknumber(state, 1);
            std::uint16_t y = luaL_checknumber(state, 2);

            ws_override.set_aspect_ratio(x, y);
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony set_widescreen_aspect_ratio function");
        }
        return 0;
    }

    static const struct luaL_Reg user_interface[] = {
        {"set_aspect_ratio", set_widescreen_aspect_ratio},
        {NULL, NULL}
    };

    void set_user_interface_functions(lua_State *state) noexcept {
        lua_pushstring(state, "ui");
        luaL_newlibtable(state, user_interface);
        luaL_setfuncs(state, user_interface, 0);

        lua_settable(state, -3);
    }
}