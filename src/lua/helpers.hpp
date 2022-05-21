// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_HELPERS_HPP
#define HARMONY_LUA_HELPERS_HPP

#include <functional>
#include <optional>
#include <map>
#include <cstdint>
#include <lua.hpp>
#include "../halo_data/widget.hpp"

namespace Harmony::Lua {
    /**
     * Create a library table
     * @param state         Lua state
     * @param name          Table name
     * @param functions     Arrays of functions to be registered
     */
    void lua_create_functions_table(lua_State *state, const char *name, const luaL_Reg *functions) noexcept;

    /**
     * Push a map to stack
     * @param state     Lua state
     * @param map       Map to be pushed
     */
    void lua_push_string_map(lua_State *state, std::map<std::string, std::string> map) noexcept;

    /**
     * Push a vector of strings to stack
     * @param state     Lua state
     * @param vector    Vector to be pushed
     */
    void lua_push_string_vector(lua_State *state, std::vector<std::string> vector) noexcept;

    /**
     * Push map
     */
    template <typename T>
    void lua_push_map(lua_State *state, std::map<std::string, T> map, std::function<void (lua_State *, T)> function) noexcept {
        lua_newtable(state);
        for(auto &pair : map) {
            lua_pushstring(state, pair.first.c_str());
            function(state, pair.second);
            lua_settable(state, -3);
        }
    }

    /**
     * Get field from table
     * @param state     Lua state
     * @param field     Field name
     * @param function  Lua function to use
     */
    template <typename T>
    std::optional<T> lua_get_table_field(lua_State *state, const char *field, std::function<T (lua_State *, int)> function) noexcept {
        std::optional<T> result;
        lua_getfield(state, 1, field);
        if(!lua_isnil(state, -1)) {
            result = function(state, -1);
            lua_pop(state, 1);
        }
        return result;
    }

    /** Unique ID for widget */
    union WidgetID {
        struct {
            std::uint16_t unique_id;
            std::uint16_t tag_index;
        };

        std::uint32_t id;

        WidgetID() {
            this->id = -1;
        }

        WidgetID(std::uint32_t id) {
            this->id = id;
        }
    };

    /**
     * Generate a unique ID for a given widget
    */
    std::uint32_t get_widget_id(HaloData::WidgetInstance *widget) noexcept;

    /**
     * Get a widget from its unique ID
    */
    HaloData::WidgetInstance *get_widget_from_id(WidgetID widget_id) noexcept;
}

#endif
