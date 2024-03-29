// SPDX-License-Identifier: GPL-3.0-only

#include "../../harmony.hpp"
#include "../helpers.hpp"
#include "../script.hpp"
#include "../library.hpp"
#include "../../halo_data/sound.hpp"
#include "../../menu/widescreen.hpp"
#include "../../menu/widget_render.hpp"
#include "menu.hpp"

namespace Harmony::Lua {
    using namespace HaloData;

    static int lua_set_aspect_ratio(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            static auto &harmony = Harmony::get();
            static auto &library = harmony.get_lua_library_handler();

            std::uint16_t x = luaL_checknumber(state, 1);
            std::uint16_t y = luaL_checknumber(state, 2);

            Menu::set_menu_aspect_ratio(x, y);
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
                auto sound_id = get_tag_id(tag_path, TAG_CLASS_SOUND);
                if(!sound_id.is_null()) {
                    play_sound(sound_id);
                }
                else {
                    luaL_error(state, "invalid sound tag in harmony play_sound function");
                }
            }
            else if(lua_type(state, 1) == LUA_TNUMBER) {
                TagID sound_id = luaL_checkinteger(state, 1);
                if(get_tag(sound_id)) {
                    play_sound(sound_id);
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

    static int lua_get_widget_values(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 1) {
            WidgetID widget_id = luaL_checkinteger(state, 1);
            auto *widget = get_widget_from_id(widget_id);

            if(widget) {
                auto name = widget->name;
                auto tag_id = widget->tag_id.whole_id;
                auto left_bound = widget->left_bound;
                auto top_bound = widget->top_bound;
                auto opacity = widget->opacity;
                auto background_bitmap_index = widget->bitmap_index;
                auto text = reinterpret_cast<std::uint32_t>(widget->text);

                lua_newtable(state);                

                #define INSERT_ELEMENT(key, push_function) { \
                    lua_pushstring(state, #key); \
                    push_function(state, key); \
                    lua_settable(state, -3); \
                }

                INSERT_ELEMENT(name, lua_pushstring);
                INSERT_ELEMENT(tag_id, lua_pushinteger);
                INSERT_ELEMENT(left_bound, lua_pushinteger);
                INSERT_ELEMENT(top_bound, lua_pushinteger);
                INSERT_ELEMENT(opacity, lua_pushnumber);
                INSERT_ELEMENT(background_bitmap_index, lua_pushinteger);
                INSERT_ELEMENT(text, lua_pushinteger);

                if(widget->previous_widget) {
                    auto previous_widget = get_widget_id(widget->previous_widget);
                    INSERT_ELEMENT(previous_widget, lua_pushinteger);
                }

                if(widget->next_widget) {
                    auto next_widget = get_widget_id(widget->next_widget);
                    INSERT_ELEMENT(next_widget, lua_pushinteger);
                }

                if(widget->parent_widget) {
                    auto parent_widget = get_widget_id(widget->parent_widget);
                    INSERT_ELEMENT(parent_widget, lua_pushinteger);
                }

                if(widget->child_widget) {
                    auto child_widget = get_widget_id(widget->child_widget);
                    INSERT_ELEMENT(child_widget, lua_pushinteger);
                }

                if(widget->focused_child) {
                    auto focused_child = get_widget_id(widget->focused_child);
                    INSERT_ELEMENT(focused_child, lua_pushinteger);
                }

                #undef INSERT_ELEMENT

                return 1;
            }
            else {
                luaL_error(state, "invalid widget handle in harmony get_widget_values function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony get_widget_values function");
        }
        return 0;
    }

    static int lua_set_widget_values(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            // Get widget
            WidgetID widget_id = luaL_checkinteger(state, 1);
            auto *widget = get_widget_from_id(widget_id);
            if(!widget) {
                return luaL_error(state, "invalid widget handle in harmony set_widget_values function");
            }

            // Get table
            luaL_checktype(state, -1, LUA_TTABLE);

            auto left_bound = lua_get_table_field<std::uint16_t>(state, "left_bound", luaL_checknumber);
            auto top_bound = lua_get_table_field<std::uint16_t>(state, "top_bound", luaL_checknumber);
            auto opacity = lua_get_table_field<float>(state, "opacity", luaL_checknumber);
            auto bitmap_index = lua_get_table_field<std::uint16_t>(state, "background_bitmap_index", luaL_checkinteger);
            auto previous_widget_id = lua_get_table_field<std::uint32_t>(state, "previous_widget", luaL_checkinteger);
            auto next_widget_id = lua_get_table_field<std::uint32_t>(state, "next_widget", luaL_checkinteger);
            auto parent_widget_id = lua_get_table_field<std::uint32_t>(state, "parent_widget", luaL_checkinteger);
            auto child_widget_id = lua_get_table_field<std::uint32_t>(state, "child_widget", luaL_checkinteger);
            auto focused_child_id = lua_get_table_field<std::uint32_t>(state, "focused_child", luaL_checkinteger);


            #define SET_VALUE(field) { \
                if(field.has_value()) { \
                    widget->field = field.value(); \
                } \
            }

            #define SET_WIDGET(widget_name) { \
                if(widget_name ## _id.has_value()) { \
                    WidgetID widget_id = widget_name ## _id.value(); \
                    auto *widget_name = get_widget_from_id(widget_id); \
                    if(widget_name) { \
                        widget->widget_name = widget_name; \
                    } \
                } \
            }

            SET_VALUE(left_bound);
            SET_VALUE(top_bound);
            SET_VALUE(opacity);
            SET_VALUE(bitmap_index);
            SET_WIDGET(previous_widget);
            SET_WIDGET(next_widget);
            SET_WIDGET(parent_widget);
            SET_WIDGET(child_widget);
            SET_WIDGET(focused_child);

            #undef SET_VALUE
            #undef SET_WIDGET 
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony set_widget_values function");
        }
        return 0;
    }

    static int lua_open_widget(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            // Get widget tag ID
            auto widget_definition = TagID::null_id();
            if(lua_type(state, 1) == LUA_TSTRING) {
                const char *tag_path = luaL_checkstring(state, 1);
                widget_definition = get_tag_id(tag_path, TAG_CLASS_UI_WIDGET_DEFINITION);
                if(widget_definition.is_null()) {
                    luaL_error(state, "invalid widget tag path in harmony open_widget function");
                }
            }
            else {
                widget_definition = luaL_checkinteger(state, 1);
                if(!get_tag(widget_definition)) {
                    luaL_error(state, "invalid tag ID in harmony open_widget function");
                }
            }

            // Get history flag
            bool dont_push_history = lua_toboolean(state, 2);

            auto *new_widget = open_widget(widget_definition, dont_push_history);
            auto new_widget_id = get_widget_id(new_widget);

            lua_pushinteger(state, new_widget_id);
            return 1;
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony open_widget function");
        }
        return 0;
    }

    static int lua_close_widget(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 0) {
            close_widget();
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony close_widget function");
        }
        return 0;
    }

    static int lua_replace_widget(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            WidgetID widget_id = luaL_checkinteger(state, 1);
            auto widget_definition = TagID::null_id();
            
            if(lua_type(state, 1) == LUA_TSTRING) {
                const char *tag_path = luaL_checkstring(state, 2);
                widget_definition = get_tag_id(tag_path, TAG_CLASS_UI_WIDGET_DEFINITION);
                if(widget_definition.is_null()) {
                    luaL_error(state, "invalid widget tag path in harmony replace_widget function");
                }
            }
            else {
                widget_definition = luaL_checkinteger(state, 2);
                if(!get_tag(widget_definition)) {
                    luaL_error(state, "invalid widget tag ID in harmony replace_widget function");
                }
            }

            auto *widget = get_widget_from_id(widget_id);
            if(widget) {
                auto *new_widget = replace_widget(widget, widget_definition);
                auto new_widget_id = get_widget_id(new_widget);
                
                lua_pushinteger(state, new_widget_id);
            }
            else {
                lua_pushnil(state);
            }
            return 1;
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony replace_widget function");
        }
        return 0;
    }

    static int lua_reload_widget(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 0 || args == 1) {
            WidgetInstance *widget;
            if(args == 0) {
                auto &widget_globals = WidgetGlobals::get();
                widget = widget_globals.root_widget;
            }
            else {
                WidgetID widget_id = luaL_checkinteger(state, 1);
                widget = get_widget_from_id(widget_id);
            }

            if(widget) {
                auto *new_widget = reload_widget(widget);
                auto new_widget_id = get_widget_id(new_widget);

                lua_pushinteger(state, new_widget_id);
            }
            else {
                lua_pushnil(state);
            }
            return 1;
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony reload_widget function");
        }
        return 0;
    }

    static int lua_find_widgets(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args >= 1 && args <= 3) {
            auto widget_definition = TagID::null_id();
            if(lua_type(state, 1) == LUA_TSTRING) {
                const char *tag_path = luaL_checkstring(state, 1);
                widget_definition = get_tag_id(tag_path, TAG_CLASS_UI_WIDGET_DEFINITION);
                if(widget_definition.is_null()) {
                    luaL_error(state, "invalid widget tag path in harmony find_widgets function");
                }
            }
            else {
                widget_definition = luaL_checkinteger(state, 1);
                if(!get_tag(widget_definition)) {
                    luaL_error(state, "invalid widget tag ID in harmony find_widgets function");
                }
            }

            bool multiple_search = false;
            if(args == 2) {
                multiple_search = lua_toboolean(state, 2);
            }

            WidgetInstance *base_widget = nullptr;
            if(args == 3) {
                WidgetID widget_id = luaL_checkinteger(state, 2);
                auto *widget = get_widget_from_id(widget_id);
                if(widget) {
                    base_widget = widget;
                }
            }

            auto found_widgets = find_widgets(widget_definition, multiple_search, base_widget);
            if(multiple_search) {
                lua_newtable(state);
                for(std::size_t i = 0; i < found_widgets.size(); i++) {
                    lua_pushinteger(state, get_widget_id(found_widgets[i]));
                    lua_rawseti(state, -2, i + 1);
                }
            }
            else {
                if(!found_widgets.empty()) {
                    lua_pushinteger(state, get_widget_id(found_widgets[0]));
                }
                else {
                    lua_pushnil(state);
                }
            }

            return 1;
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony find_widgets function");
        }
        return 0;
    }

    static int lua_focus_widget(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 1) {
            WidgetID widget_id = luaL_checkinteger(state, 1);
            auto *widget = get_widget_from_id(widget_id);
            if(!widget) {
                return luaL_error(state, "invalid widget handle in harmony focus_widget function");
            }
            focus_widget(widget);
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony focus_widget function");
        }
        return 0;
    }

    static int lua_get_root_widget(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 0) {
            auto &widget_globals = WidgetGlobals::get();
            auto *root_widget = widget_globals.root_widget;

            if(root_widget) {
                lua_pushinteger(state, get_widget_id(root_widget));
            }
            else {
                lua_pushnil(state);
            }

            return 1;
        }
        else {
            return luaL_error(state, "invalid number of arguments in harmony insert_widget function");
        }
    }

    static int lua_block_input(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 1) {
            bool block_input = lua_toboolean(state, 1);
            if(block_input) {
                block_widget_input();
            }
            else {
                unblock_widget_input();
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony block_input function");
        }
        return 0;
    }

    static int lua_set_cursor_scale(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 1) {
            float scale = luaL_checknumber(state, 1);
            Menu::set_cursor_scale(scale);
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony set_cursor_scale function");
        }
        return 0;
    }

    static const luaL_Reg menu[] = {
        {"set_aspect_ratio", lua_set_aspect_ratio},
        {"play_sound", lua_play_sound},
        {"get_widget_values", lua_get_widget_values},
        {"set_widget_values", lua_set_widget_values},
        {"open_widget", lua_open_widget},
        {"close_widget", lua_close_widget},
        {"replace_widget", lua_replace_widget},
        {"reload_widget", lua_reload_widget},
        {"find_widgets", lua_find_widgets},
        {"focus_widget", lua_focus_widget},
        {"get_root_widget", lua_get_root_widget},
        {"block_input", lua_block_input},
        {"set_cursor_scale", lua_set_cursor_scale},
        {NULL, NULL}
    };

    void set_menu_functions(lua_State *state) noexcept {
        lua_create_functions_table(state, "menu", menu);
    }
}