// SPDX-License-Identifier: GPL-3.0-only

#include "../../harmony.hpp"
#include "../script.hpp"
#include "../library.hpp"
#include "../../halo_data/sound.hpp"
#include "../../halo_data/widget.hpp"
#include "../../menu/widescreen_override.hpp"
#include "menu.hpp"

namespace Harmony::Lua {
    static int lua_set_widescreen_aspect_ratio(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            static auto &harmony = Harmony::get();
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

    static int lua_play_sound(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 1) {
            if(lua_type(state, 1) == LUA_TSTRING) {
                const char *tag_path = luaL_checkstring(state, 1);
                auto sound_id = HaloData::get_tag_id(tag_path, HaloData::TAG_CLASS_SOUND);
                if(!sound_id.is_null()) {
                    HaloData::play_sound(sound_id);
                }
                else {
                    luaL_error(state, "invalid sound tag in harmony play_sound function");
                }
            }
            else if(lua_type(state, 1) == LUA_TNUMBER) {
                HaloData::TagID sound_id = luaL_checkinteger(state, 1);
                if(HaloData::get_tag(sound_id)) {
                    HaloData::play_sound(sound_id);
                }
                else {
                    luaL_error(state, "invalid sound tag in harmony play_sound function");
                }
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony play_sound function");
        }
        return 0;
    }

    static int lua_open_widget(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            // Get widget tag ID
            auto widget_id = HaloData::TagID::null_id();
            if(lua_type(state, 1) == LUA_TSTRING) {
                const char *tag_path = luaL_checkstring(state, 1);
                widget_id = HaloData::get_tag_id(tag_path, HaloData::TAG_CLASS_UI_WIDGET_DEFINITION);
                if(widget_id.is_null()) {
                    luaL_error(state, "invalid widget tag path in harmony open_widget function");
                }
            }
            else {
                widget_id = luaL_checkinteger(state, 1);
                if(!HaloData::get_tag(widget_id)) {
                    luaL_error(state, "invalid tag ID in harmony open_widget function");
                }
            }

            // Get history flag
            bool dont_push_history = lua_toboolean(state, 1);

            HaloData::open_widget(widget_id, dont_push_history);
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony play_sound function");
        }
        return 0;
    }

    static const struct luaL_Reg menu[] = {
        {"set_aspect_ratio", lua_set_widescreen_aspect_ratio},
        {"play_sound", lua_play_sound},
        {"open_widget", lua_open_widget},
        {NULL, NULL}
    };

    void set_menu_functions(lua_State *state) noexcept {
        lua_pushstring(state, "ui");
        luaL_newlibtable(state, menu);
        luaL_setfuncs(state, menu, 0);

        lua_settable(state, -3);
    }
}