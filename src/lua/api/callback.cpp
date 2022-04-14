// SPDX-License-Identifier: GPL-3.0-only

#include <string>
#include <lua.hpp>
#include "../../events/map_load.hpp"
#include "../../events/multiplayer_sound.hpp"
#include "../../events/hs_function.hpp"
#include "../../events/keypress.hpp"
#include "../../events/multiplayer_event.hpp"
#include "../../events/multiplayer_sound.hpp"
#include "../../events/widget_accept.hpp"
#include "../../events/widget_close.hpp"
#include "../../events/widget_list_tab.hpp"
#include "../../events/widget_mouse_button_press.hpp"
#include "../../events/widget_sound.hpp"
#include "../../harmony.hpp"
#include "../helpers.hpp"
#include "../library.hpp"
#include "callback.hpp"

namespace Harmony::Lua {
    using CallbackType = Script::CallbackType;

    static Library *library = nullptr;

    static bool multiplayer_event(HaloData::MultiplayerEvent, HaloData::PlayerID, HaloData::PlayerID, HaloData::PlayerID) noexcept;
    static bool multiplayer_sound_event(HaloData::MultiplayerSound) noexcept;
    static bool widget_accept(HaloData::WidgetInstance *) noexcept;
    static bool widget_close(HaloData::WidgetInstance *) noexcept;
    static bool widget_mouse_button_press(HaloData::WidgetInstance *, HaloData::MouseButtonWidgetEvent::MouseButton) noexcept;
    static bool widget_list_tab(HaloData::GamepadButtonWidgetEvent::GamepadButton, HaloData::WidgetInstance *, HaloData::WidgetInstance *) noexcept;
    static bool widget_sound(HaloData::WidgetNavigationSound) noexcept;
    static bool script_function(const char *, HaloData::ScriptFunction *, const std::uint32_t *) noexcept;

    int lua_set_callback(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            std::string callback_name = luaL_checkstring(state, 1);
            std::string function = luaL_checkstring(state, 2);

            static constexpr const char *callback_names[] = {
                "multiplayer event",
                "multiplayer sound",
                "menu accept",
                "widget accept",
                "widget back",
                "widget list tab",
                "widget mouse button press",
                "widget sound",
                "hs function",
            };

            std::size_t i;
            std::size_t n = sizeof(callback_names) / sizeof(const char *);
            for(i = 0; i < n; i++) {
                if(callback_name == callback_names[i]) {
                    auto &harmony = Harmony::get();
                    auto &handler = harmony.get_lua_library_handler();
                    auto *script  = handler.get_script(state);
                    script->add_callback(static_cast<CallbackType>(i), function);
                    break;
                }
            }

            if(i == n) {
                luaL_error(state, "invalid callback in harmony set_callback function");
            }
        }
        else {
            luaL_error(state, "invalid number of arguments in harmony set_callback function");
        }
        return 0;
    }

    void set_callback_functions(lua_State *state) noexcept {
        auto &harmony = Harmony::get();
        library = &harmony.get_lua_library_handler();

        // Set up Lua script events
        add_multiplayer_sound_event(multiplayer_sound_event);
        add_multiplayer_event(multiplayer_event);
        add_widget_accept_event(widget_accept);
        add_widget_close_event(widget_close);
        add_widget_mouse_button_press_event(widget_mouse_button_press);
        add_widget_list_tab_event(widget_list_tab);
        add_widget_sound_event(widget_sound);
        add_hs_function_event(script_function);

        lua_pushstring(state, "set_callback");
        lua_pushcfunction(state, lua_set_callback);
        lua_settable(state, -3);
    }

    bool multiplayer_event(HaloData::MultiplayerEvent type, HaloData::PlayerID local, HaloData::PlayerID killer, HaloData::PlayerID victim) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks(CallbackType::CALLBACK_TYPE_MULTIPLAYER_EVENT);
            for(auto &callback : callbacks) {
                lua_getglobal(state, callback.c_str());
                lua_pushstring(state, HaloData::string_from_multiplayer_event(type).c_str());
                lua_pushinteger(state, local.whole_id);
                lua_pushinteger(state, killer.whole_id);
                lua_pushinteger(state, victim.whole_id);
                if(lua_pcall(state, 4, 1, 0) == LUA_OK) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
                }
                else {
                    script->print_last_error();
                }
            }
            it++;
        }
        return allow;
    }

    bool multiplayer_sound_event(HaloData::MultiplayerSound sound) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks(CallbackType::CALLBACK_TYPE_MULTIPLAYER_SOUND);
            for(auto &callback : callbacks) {
                lua_getglobal(state, callback.c_str());
                lua_pushstring(state, HaloData::string_from_multiplayer_sound(sound).c_str());
                if(lua_pcall(state, 1, 1, 0) == LUA_OK) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
                }
                else {
                    script->print_last_error();
                }
            }
            it++;
        }
        return allow;
    }

    bool widget_accept(HaloData::WidgetInstance *widget) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            
            auto &callbacks = script->get_callbacks(CallbackType::CALLBACK_TYPE_WIDGET_ACCEPT);
            for(auto &callback : callbacks) {
                auto widget_id = get_widget_id(widget);
                
                lua_getglobal(state, callback.c_str());
                lua_pushinteger(state, widget_id);
                if(lua_pcall(state, 1, 1, 0) == LUA_OK) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
                }
                else {
                    script->print_last_error();
                }
            }

            auto &old_callbacks = script->get_callbacks(CallbackType::CALLBACK_TYPE_MENU_ACCEPT);
            for(auto &callback : old_callbacks) {
                lua_getglobal(state, callback.c_str());
                lua_pushinteger(state, widget->tag_id.whole_id);
                if(lua_pcall(state, 1, 1, 0) == LUA_OK) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
                }
                else {
                    script->print_last_error();
                }
            }

            it++;
        }
        return allow;
    }

    bool widget_close(HaloData::WidgetInstance *widget) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks(CallbackType::CALLBACK_TYPE_WIDGET_BACK);
            for(auto &callback : callbacks) {
                auto widget_id = get_widget_id(widget);
                
                lua_getglobal(state, callback.c_str());
                lua_pushinteger(state, widget_id);
                if(lua_pcall(state, 1, 1, 0) == LUA_OK) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
                }
                else {
                    script->print_last_error();
                }
            }
            it++;
        }
        return allow;
    }

    bool widget_list_tab(HaloData::GamepadButtonWidgetEvent::GamepadButton button, HaloData::WidgetInstance *list_widget, HaloData::WidgetInstance *pressed_widget) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks(CallbackType::CALLBACK_TYPE_WIDGET_LIST_TAB);
            for(auto &callback : callbacks) {
                auto list_widget_id = get_widget_id(list_widget);
                auto pressed_widget_id = get_widget_id(pressed_widget);
                auto button_string = HaloData::GamepadButtonWidgetEvent::to_string(button);
                
                lua_getglobal(state, callback.c_str());
                lua_pushstring(state, button_string.c_str());
                lua_pushinteger(state, list_widget_id);
                lua_pushinteger(state, pressed_widget_id);

                if(lua_pcall(state, 3, 1, 0) == LUA_OK) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
                }
                else {
                    script->print_last_error();
                }
            }
            it++;
        }
        return allow;
    }

    bool widget_mouse_button_press(HaloData::WidgetInstance *widget, HaloData::MouseButtonWidgetEvent::MouseButton mouse_button) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks(CallbackType::CALLBACK_TYPE_WIDGET_MOUSE_BUTTON_PRESS);
            for(auto &callback : callbacks) {
                auto widget_id = get_widget_id(widget);
                auto mouse_button_string = HaloData::MouseButtonWidgetEvent::to_string(mouse_button);
                
                lua_getglobal(state, callback.c_str());
                lua_pushinteger(state, widget_id);
                lua_pushstring(state, mouse_button_string.c_str());
                if(lua_pcall(state, 2, 1, 0) == LUA_OK) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
                }
                else {
                    script->print_last_error();
                }
            }
            it++;
        }
        return allow;
    }

    bool widget_sound(HaloData::WidgetNavigationSound sound) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks(CallbackType::CALLBACK_TYPE_WIDGET_SOUND);
            for(auto &callback : callbacks) {
                auto sound_string = HaloData::to_string(sound);

                lua_getglobal(state, callback.c_str());
                lua_pushstring(state, sound_string.c_str());
                if(lua_pcall(state, 1, 1, 0) == LUA_OK) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
                }
                else {
                    script->print_last_error();
                }
            }
            it++;
        }
        return allow;
    }

    bool script_function(const char *name, HaloData::ScriptFunction *function, const std::uint32_t *params) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks(CallbackType::CALLBACK_TYPE_HS_FUNCTION);
            for(auto &callback : callbacks) {
                lua_getglobal(state, callback.c_str());
                lua_pushstring(state, name);
                lua_pushstring(state, function->name);
                
                // Get parameters
                lua_newtable(state);
                for(std::size_t i = 0; i < function->parameter_count; i++) {
                    switch(function->get_parameters()[i]) {
                        case HaloData::ScriptFunction::DATA_TYPE_BOOLEAN: {
                            lua_pushboolean(state, *reinterpret_cast<const std::uint8_t *>(params + i));
                            break;
                        }

                        case HaloData::ScriptFunction::DATA_TYPE_REAL: {
                            lua_pushnumber(state, *reinterpret_cast<const float *>(params + i));
                            break;
                        }

                        case HaloData::ScriptFunction::DATA_TYPE_SHORT: {
                            lua_pushinteger(state, *reinterpret_cast<const std::uint16_t *>(params + i));
                            break;
                        }

                        case HaloData::ScriptFunction::DATA_TYPE_LONG: {
                            lua_pushinteger(state, params[i]);
                            break;
                        }

                        case HaloData::ScriptFunction::DATA_TYPE_STRING: {
                            lua_pushstring(state, reinterpret_cast<const char *>(params[i]));
                            break;
                        }

                        default: {
                            lua_pushinteger(state, params[i]);
                            break;
                        }
                    }
                    lua_rawseti(state, -2, i + 1);
                }

                if(lua_pcall(state, 3, 1, 0) == LUA_OK) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
                }
                else {
                    script->print_last_error();
                }
            }
            it++;
        }
        return allow;
    }
}
