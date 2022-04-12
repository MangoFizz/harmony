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
    static Library *library = nullptr;

    static bool multiplayer_event(HaloData::MultiplayerEvent, HaloData::PlayerID, HaloData::PlayerID, HaloData::PlayerID) noexcept;
    static bool multiplayer_sound_event(HaloData::MultiplayerSound) noexcept;
    static bool widget_accept(HaloData::WidgetInstance *) noexcept;
    static bool widget_close(HaloData::WidgetInstance *) noexcept;
    static bool widget_mouse_button_press(HaloData::WidgetInstance *, HaloData::MouseButtonWidgetEvent::MouseButton) noexcept;
    static bool widget_list_tab(HaloData::GamepadButtonWidgetEvent::GamepadButton, HaloData::WidgetInstance *, HaloData::WidgetInstance *) noexcept;
    static bool widget_sound(HaloData::WidgetNavigationSound) noexcept;
    static bool script_function(const char *, HaloData::ScriptFunction *, const std::uint32_t *) noexcept;
    static void keypress(std::uint8_t, wchar_t, std::uint8_t) noexcept;

    int lua_set_callback(lua_State *state) noexcept {
        int args = lua_gettop(state);
        if(args == 2) {
            std::string callback_name = luaL_checkstring(state, 1);
            std::string function = luaL_checkstring(state, 2);

            auto callback_exists = [callback_name]() {
                #define CHECK_CALLBACK(callback) (callback == callback_name) {}

                if CHECK_CALLBACK("multiplayer event")
                else if CHECK_CALLBACK("multiplayer sound")
                else if CHECK_CALLBACK("menu accept")
                else if CHECK_CALLBACK("widget accept")
                else if CHECK_CALLBACK("widget back")
                else if CHECK_CALLBACK("widget list tab")
                else if CHECK_CALLBACK("widget mouse button press")
                else if CHECK_CALLBACK("widget sound")
                else if CHECK_CALLBACK("script function")
                else if CHECK_CALLBACK("key press")
                else return false;
                return true;
            };

            if(callback_exists()) {
                auto &harmony = Harmony::get();
                auto &handler = harmony.get_lua_library_handler();
                auto *script  = handler.get_script(state);
                script->add_callback(callback_name, function);
            }
            else {
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
        add_keypress_event(keypress);

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
            auto &callbacks = script->get_callbacks("multiplayer event");
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
            auto &callbacks = script->get_callbacks("multiplayer sound");
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
            
            auto &callbacks = script->get_callbacks("widget accept");
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

            auto &old_callbacks = script->get_callbacks("menu accept");
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
            auto &callbacks = script->get_callbacks("widget back");
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
            auto &callbacks = script->get_callbacks("widget list tab");
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
            auto &callbacks = script->get_callbacks("widget mouse button press");
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
            auto &callbacks = script->get_callbacks("widget sound");
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
            auto &callbacks = script->get_callbacks("script function");
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

    void keypress(std::uint8_t modifier, wchar_t character, std::uint8_t keycode) noexcept {
        auto &scripts = library->get_scripts();
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks("key press");
            for(auto &callback : callbacks) {
                lua_getglobal(state, callback.c_str());
                lua_pushinteger(state, modifier);
                lua_pushinteger(state, character);
                lua_pushinteger(state, keycode);
                if(!lua_pcall(state, 3, 0, 0) == LUA_OK) {
                    script->print_last_error();
                }
            }
            it++;
        }
    }
}
