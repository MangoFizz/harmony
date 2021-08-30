// SPDX-License-Identifier: GPL-3.0-only

#include <algorithm>
#include "../messaging/console_output.hpp"
#include "../messaging/message_box.hpp"
#include "../events/d3d9_end_scene.hpp"
#include "../events/d3d9_reset.hpp"
#include "../events/map_load.hpp"
#include "../events/multiplayer_sound.hpp"
#include "../events/menu_back.hpp"
#include "../user_interface/widescreen_override.hpp"
#include "../harmony.hpp"
#include "api/callback.hpp"
#include "api/optic.hpp"
#include "api/user_interface.hpp"
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
        this->scripts.push_back(std::make_unique<Script>(state));

        // Set unload global funcion
        lua_pushcfunction(state, Library::lua_unload_script);
        lua_setglobal(state, "unload_harmony");

        // Set chimera unload callback
        lua_getglobal(state, "set_callback");
        lua_pushstring(state, "unload");
        lua_pushstring(state, "unload_harmony");
        if(lua_pcall(state, 2, 0, 0) != 0) {
            luaL_error(state, "failed to set harmony unload callback");
        }
    }

    void Library::unload_script(lua_State *state) noexcept {
        auto it = this->scripts.begin();
        while(it != this->scripts.end()) {
            auto *script = it->get();
            if(script->get_state() == state) {
                this->scripts.erase(it);
                break;
            }
            it++;
        }
    }

    void Library::unload_all_scripts() noexcept {
        this->scripts.clear();
    }

    void Library::unload_global_scripts() noexcept {
        auto it = this->scripts.begin();
        while(it != this->scripts.end()) {
            auto *script = it->get();
            std::string script_type = script->get_type();
            if(script_type == "global") {
                it = this->scripts.erase(it);
            }
            else {
                it++;
            }
        }
    }

    void Library::unload_map_script() noexcept {
        auto it = this->scripts.begin();
        while(it != this->scripts.end()) {
            auto *script = it->get();
            std::string script_type = script->get_type();
            if(script_type == "map") {
                this->scripts.erase(it);
                break;
            }
            it++;
        }
    }

    Library::Library() noexcept {
        library = this;

        // Set up library events
        add_map_load_event(Library::on_map_load, EVENT_PRIORITY_BEFORE);
        add_d3d9_end_scene_event(Library::on_d3d9_end_scene);
        add_d3d9_reset_event(Library::on_d3d9_reset);

        // Set up Lua script events
        add_multiplayer_sound_event(Library::multiplayer_sound_event);
        add_multiplayer_event(Library::multiplayer_event);
        add_menu_accept_event(Library::menu_accept);
        add_menu_back_event(Library::menu_back);
        add_menu_mouse_button_press_event(Library::menu_mouse_button_press);
        add_menu_list_tab_event(Library::menu_list_tab);
        add_menu_sound_event(Library::menu_sound);
    }
    
    void Library::on_map_load() noexcept {
        //library->unload_map_script();
    }

    void Library::on_d3d9_end_scene(LPDIRECT3DDEVICE9 device) noexcept {
        for(auto &script : library->get_scripts()) {
            auto &store = script.get()->get_optic_store();
            store.load_sprites(device);
        }
    }

    void Library::on_d3d9_reset(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS *) noexcept {
        for(auto &script : library->get_scripts()) {
            auto &store = script.get()->get_optic_store();
            store.release_sprites();
        }
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
                if(lua_pcall(state, 4, 1, 0) == 0) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
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
                if(lua_pcall(state, 1, 1, 0) == 0) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
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
                if(lua_pcall(state, 1, 1, 0) == 0) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
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
                if(lua_pcall(state, 1, 1, 0) == 0) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
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
                if(lua_pcall(state, 3, 1, 0) == 0) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
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
                if(lua_pcall(state, 2, 1, 0) == 0) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
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
                if(lua_pcall(state, 2, 1, 0) == 0) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
                }
            }
            it++;
        }
        return allow;
    }


    int Library::lua_unload_script(lua_State *state) noexcept {
        auto *script = library->get_script(state);
        if(strcmp(script->get_type(), "map") == 0) {
            /**
             * Restore UI frame aspect ratio before map script unload.
             * We can't put this in a map load callback because our event
             * is executed after Chimera's map load event, so our map 
             * script will load BEFORE we can restore the aspect ratio.
             */
            get_harmony().get_widescreen_override_handle().reset_frame_aspect_ratio();
        }
        library->unload_script(state);
        return 0;
    }

    int luaopen_mods_harmony(lua_State *state) noexcept {
        // Create Harmony library table
        lua_newtable(state);

        // Set callback functions
        set_callback_functions(state);

        // Set optic functions
        set_optic_functions(state);

        // Set UI functions only if script is NOT global
        if(Script::get_global_from_state(state, "script_type") == "map") {
            set_user_interface_functions(state);
        }

        // Load it!!
        library->load_script(state);
        
        return 1;
    }
}
