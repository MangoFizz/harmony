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
     * Get field from table
     * @param state     Lua state
     * @param field     Field name
     * @param function  Lua function to use
     */
    template <typename T>
    std::optional<T> lua_get_table_field(lua_State *state, const char *field, std::function<T (lua_State *, int)> function) {
        std::optional<T> result;
        if(lua_getfield(state, 1, field)) {
            result = function(state, 1);
            lua_pop(state, -1);
        }
        return result;
    }

    /**
     * Push a map to stack
     * @param state     Lua state
     * @param map       Map to be pushed
     */
    void lua_push_string_map(lua_State *state, std::map<std::string, std::string> map) noexcept;

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
