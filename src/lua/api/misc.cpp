// SPDX-License-Identifier: GPL-3.0-only

#include "../../command/command.hpp"
#include "../helpers.hpp"
#include "misc.hpp"

namespace Harmony::Lua {
    static int lua_split_command(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 1) {
            const char *full_command = luaL_checkstring(state, 1);
            auto slices = split_arguments(full_command);
            lua_push_string_vector(state, slices);
            return 1;
        }
        else {
            return luaL_error(state, "invalid number of arguments in harmony split_command function");
        }
    }

    static const struct luaL_Reg misc[] = {
        {"split_command", lua_split_command},
        {NULL, NULL}
    };

    void set_misc_functions(lua_State *state) noexcept {
        lua_create_functions_table(state, "misc", misc);
    }
}