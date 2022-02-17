// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_LIBRARY_HPP
#define HARMONY_LUA_LIBRARY_HPP

#include <string>
#include <vector>
#include <lua.hpp>
#include "../events/multiplayer_event.hpp"
#include "../events/multiplayer_sound.hpp"
#include "../events/menu_accept.hpp"
#include "../events/menu_list_tab.hpp"
#include "../events/menu_mouse_button_press.hpp"
#include "../events/menu_sound.hpp"
#include "../halo_data/script.hpp"
#include "script.hpp"

namespace Harmony::Lua {
    class Library {
    public:
        /**
         * Get scripts
         * @return      Constant reference to scripts
         */
        std::vector<std::unique_ptr<Script>> &get_scripts() noexcept;

        /**
         * Get a script by name
         * @return      Pointer to script if exists, null if not
         */
        Script *get_script(std::string name) noexcept;

        /**
         * Get a script by state
         */
        Script *get_script(lua_State *state) noexcept;

        /**
         * Load a Lua script
         * @param state     Pointer to Lua script state
         */
        void load_script(lua_State *state) noexcept;

        /**
         * Unload script
         * @param state     Pointer to Lua script state
         */
        void unload_script(lua_State *state) noexcept;

        /**
         * Constructor for Lua library
         */
        Library() noexcept;

        /** 
         * Script events dispatchers
         */
        static bool multiplayer_event(HaloData::MultiplayerEvent type, HaloData::PlayerID local, HaloData::PlayerID killer, HaloData::PlayerID victim) noexcept;
        static bool multiplayer_sound_event(HaloData::MultiplayerSound sound) noexcept;
        static bool menu_accept(HaloData::TagID *tag_id) noexcept;
        static bool menu_back(HaloData::TagID menu_id) noexcept;
        static bool menu_mouse_button_press(HaloData::TagID tag_id, HaloData::MenuMouseButtonCode button_code) noexcept;
        static bool menu_list_tab(HaloData::MenuNavigationKeyCode key, HaloData::TagID list_id, HaloData::TagID button_id) noexcept;
        static bool menu_sound(HaloData::TagID button_id, HaloData::MenuSound sound) noexcept;
        static bool script_function(const char *name, HaloData::ScriptFunction *function, const std::uint32_t *params) noexcept;

        /** 
         * Unload script callback
         * This function is called when Chimera unloads a script, so we need to unload it here too
         */
        static int lua_unload_script(lua_State *state) noexcept;

    private:
        /** Loaded scripts */
        std::vector<std::unique_ptr<Script>> scripts;
    };

    /**
     * Lua library entry point
     */
    extern "C" __declspec(dllexport) int luaopen_mods_harmony(lua_State *state) noexcept;
}

#endif 
