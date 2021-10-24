// SPDX-License-Identifier: GPL-3.0-only

#include <algorithm>
#include "../events/d3d9_end_scene.hpp"
#include "../events/d3d9_reset.hpp"
#include "../events/map_load.hpp"
#include "../events/multiplayer_sound.hpp"
#include "../events/menu_back.hpp"
#include "../menu/widescreen_override.hpp"
#include "../harmony.hpp"
#include "api/callback.hpp"
#include "api/optic.hpp"
#include "api/menu.hpp"
#include "script.hpp"
#include "library.hpp"

namespace Harmony::Lua {
    static Library *library = nullptr;
 
    std::vector<std::unique_ptr<Script>> &Library::get_scripts() noexcept {
        return this->scripts;
    }

    Script *Library::get_script(std::string name) noexcept {
        for(std::size_t i = 0; i < this->scripts.size(); i++) {
            auto *script = this->scripts[i].get();
            if(script->get_name() == name) {
                return script;
            }
        }
        return nullptr;
    }

    Script *Library::get_script(lua_State *state) noexcept {
        for(std::size_t i = 0; i < this->scripts.size(); i++) {
            auto *script = this->scripts[i].get();
            if(script->get_state() == state) {
                return script;
            }
        }
        return nullptr;
    }

    void Library::load_script(lua_State *state) noexcept {
        auto *script = this->get_script(state);
        if(script) {
            script->require_count++;
        }
        else {
            this->scripts.push_back(std::make_unique<Script>(state));
        }
    }

    void Library::unload_script(lua_State *state) noexcept {
        auto it = this->scripts.begin();
        while(it != this->scripts.end()) {
            auto *script = it->get();
            if(script->get_state() == state) {
                // Look for require count
                if(script->get_require_count() == 1) {
                    /**
                     * Restore UI frame aspect ratio before unload map script.
                     * We can't put this in a map load callback because our event
                     * is executed after Chimera's map load event, so next map 
                     * script will load BEFORE we can restore the aspect ratio.
                     */
                    if(script->get_type() == "map") {
                        Harmony::get().get_widescreen_override_handle().reset_frame_aspect_ratio();
                    }

                    // Unload script
                    this->scripts.erase(it);
                }
                else {
                    script->require_count--;
                }

                break;
            }
            it++;
        }
    }

    Library::Library() noexcept {
        library = this;

        // Set up Lua script events
        add_multiplayer_sound_event(Library::multiplayer_sound_event);
        add_multiplayer_event(Library::multiplayer_event);
        add_menu_accept_event(Library::menu_accept);
        add_menu_back_event(Library::menu_back);
        add_menu_mouse_button_press_event(Library::menu_mouse_button_press);
        add_menu_list_tab_event(Library::menu_list_tab);
        add_menu_sound_event(Library::menu_sound);
    }

    bool Library::multiplayer_event(HaloData::MultiplayerEvent type, HaloData::PlayerID local, HaloData::PlayerID killer, HaloData::PlayerID victim) noexcept {
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

    bool Library::multiplayer_sound_event(HaloData::MultiplayerSound sound) noexcept {
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

    bool Library::menu_accept(HaloData::TagID *tag_id) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks("menu accept");
            for(auto &callback : callbacks) {
                lua_getglobal(state, callback.c_str());
                lua_pushinteger(state, tag_id->whole_id);
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

    bool Library::menu_back(HaloData::TagID menu_id) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks("menu back");
            for(auto &callback : callbacks) {
                lua_getglobal(state, callback.c_str());
                lua_pushinteger(state, menu_id.whole_id);
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

    bool Library::menu_list_tab(HaloData::MenuNavigationKeyCode key, HaloData::TagID list_id, HaloData::TagID button_id) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks("menu list tab");
            for(auto &callback : callbacks) {
                lua_getglobal(state, callback.c_str());
                lua_pushstring(state, HaloData::string_from_menu_key_code(key).c_str());
                lua_pushinteger(state, list_id.whole_id);
                lua_pushinteger(state, button_id.whole_id);
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

    bool Library::menu_mouse_button_press(HaloData::TagID tag_id, HaloData::MenuMouseButtonCode button_code) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks("menu mouse button press");
            for(auto &callback : callbacks) {
                lua_getglobal(state, callback.c_str());
                lua_pushinteger(state, tag_id.whole_id);
                lua_pushstring(state, HaloData::string_from_menu_mouse_button_code(button_code).c_str());
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

    bool Library::menu_sound(HaloData::TagID button_id, HaloData::MenuSound sound) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        auto it = scripts.begin();
        while(it != scripts.end()) {
            auto *script = it->get();
            auto *state = script->get_state();
            auto &callbacks = script->get_callbacks("menu sound");
            for(auto &callback : callbacks) {
                lua_getglobal(state, callback.c_str());
                lua_pushinteger(state, button_id.whole_id);
                lua_pushstring(state, HaloData::string_from_menu_sound(sound).c_str());
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

    int lua_unload_harmony(lua_State *state) noexcept {
        library->unload_script(state);
        return 0;
    }

    int lua_old_unload_harmony(lua_State *state) noexcept {
        return 0;
    }

    int luaopen_mods_harmony(lua_State *state) noexcept {
        // Create Harmony library table
        lua_newtable(state);

        // Set callback functions
        set_callback_functions(state);

        // Set optic functions
        set_optic_functions(state);

        // Load this only if it's a map script
        if(Script::get_global_from_state(state, "script_type") == "map") {
            // Load UI functions
            set_menu_functions(state);
        }

        /**
         * Set __gc metamethod
         * The garbage collector will call the unload function before collect the library table.
         */
        lua_createtable(state, 0, 1);
        lua_pushcfunction(state, lua_unload_harmony);
        lua_setfield(state, -2, "__gc");
        lua_setmetatable(state, -2);

        // Do not break scripts that uses old unload method
        lua_pushstring(state, "unload");
        lua_pushcfunction(state, lua_old_unload_harmony);
        lua_settable(state, -3);

        // Load it!!
        library->load_script(state);
        
        return 1;
    }
}
