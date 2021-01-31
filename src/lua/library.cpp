// SPDX-License-Identifier: GPL-3.0-only

#include <algorithm>
#include "../messaging/console_output.hpp"
#include "../messaging/message_box.hpp"
#include "../events/multiplayer_sound.hpp"
#include "../events/map_load.hpp"
#include "api/callback.hpp"
#include "api/optic.hpp"
#include "script.hpp"
#include "library.hpp"

namespace Harmony::Lua {
    static Library *library = nullptr;
 
    std::vector<Script> &Library::get_scripts() noexcept {
        return this->scripts;
    }

    Script *Library::get_script(std::string name) noexcept {
        for(std::size_t i = 0; i < this->scripts.size(); i++) {
            if(this->scripts[i].get_name() == name) {
                return &this->scripts[i];
            }
        }
        return nullptr;
    }

    Script *Library::get_script(lua_State *state) noexcept {
        for(std::size_t i = 0; i < this->scripts.size(); i++) {
            if(this->scripts[i].get_state() == state) {
                return &this->scripts[i];
            }
        }
        return nullptr;
    }

    void Library::load_script(lua_State *state) noexcept {
        this->scripts.emplace_back(state);
            
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
        for(std::size_t i = 0; i < this->scripts.size(); i++) {
            if(this->scripts[i].get_state() == state) {
                this->scripts.erase(this->scripts.begin() + i);
            }
        }
    }


    void Library::unload_all_scripts() noexcept {
        this->scripts.clear();
    }

    void Library::unload_global_scripts() noexcept {
        auto it = this->scripts.begin();
        while(it != this->scripts.end()) {
            std::string script_type = it->get_type();
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
            std::string script_type = it->get_type();
            if(script_type == "map") {
                break;
            }
            it++;
        }
        this->scripts.erase(it);
    }

    Library::Library() noexcept {
        library = this;

        // Set up library events
        add_map_load_event(Library::on_map_load, EVENT_PRIORITY_BEFORE);
        add_multiplayer_sound_event(Library::multiplayer_sound_event);
    }
    
    void Library::on_map_load() noexcept {
        library->unload_map_script();
    }

    int Library::lua_unload_script(lua_State *state) noexcept {
        library->unload_script(state);
        return 0;
    }

    bool Library::multiplayer_sound_event(HaloData::MultiplayerSound sound) noexcept {
        auto &scripts = library->get_scripts();
        bool allow = true;
        for(auto &script : scripts) {
            auto *state = script.get_state();
            auto &callbacks = script.get_callbacks("multiplayer sound");
            for(auto &callback : callbacks) {
                lua_getglobal(state, callback.c_str());
                lua_pushstring(state, HaloData::string_from_multiplayer_sound(sound).c_str());
                if(lua_pcall(state, 1, 1, 0) == 0) {
                    if(allow) {
                        allow = lua_toboolean(state, -1);
                    }
                }
            }
        }
        return allow;
    }

    int luaopen_mods_harmony(lua_State *state) noexcept {
        // Create Harmony library table
        lua_newtable(state);

        // Set callback functions
        set_callback_functions(state);

        // Set optic functions
        set_optic_functions(state);

        // Load it!!
        library->load_script(state);
        
        return 1;
    }
}
