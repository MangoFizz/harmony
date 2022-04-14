// SPDX-License-Identifier: GPL-3.0-only

#include <stdexcept>
#include "../../server/status.hpp"
#include "../helpers.hpp"
#include "server.hpp"

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
            luaL_error(state, "invalid number of arguments in harmony query_status function");
        }
        return 0;
    }

    static const struct luaL_Reg server[] = {
        {"query_status", lua_query_server_status},
        {NULL, NULL}
    };

    void set_server_functions(lua_State *state) noexcept {
        lua_pushstring(state, "server");
        luaL_newlibtable(state, server);
        luaL_setfuncs(state, server, 0);

        lua_settable(state, -3);
    }
}