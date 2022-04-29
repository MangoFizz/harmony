// SPDX-License-Identifier: GPL-3.0-only

#include <stdexcept>
#include "../../server/status.hpp"
#include "../../halo_data/multiplayer_sounds.hpp"
#include "../helpers.hpp"
#include "multiplayer.hpp"

namespace Harmony::Lua {
    static int lua_query_server_status(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            const char *address = luaL_checkstring(state, 1);
            std::uint16_t port = luaL_checkinteger(state, 2);

            try {
                auto response = Server::query_status(address, port);
                auto status = Server::parse_status(response);

                lua_push_string_map(state, status);
            }
            catch(std::runtime_error &e) {
                lua_pushnil(state);
            }

            return 1;
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony query_server_status function");
        }
        return 0;
    }

    static int lua_mute_announcer(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 1) {
            bool setting = lua_toboolean(state, 1);
            HaloData::mute_announcer(setting);
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony mute_announcer function");
        }
        return 0;
    }

    static const struct luaL_Reg multiplayer[] = {
        {"query_server_status", lua_query_server_status},
        {"mute_announcer", lua_mute_announcer},
        {NULL, NULL}
    };

    void set_multiplayer_api(lua_State *state) noexcept {
        lua_create_functions_table(state, "multiplayer", multiplayer);
    }
}