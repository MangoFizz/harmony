// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_LIBRARY_HPP
#define HARMONY_LUA_LIBRARY_HPP

#include <string>
#include <vector>
#include <lua.hpp>
#include "../events/multiplayer_sound.hpp"
#include "script.hpp"

namespace Harmony::Lua {
    class Library {
    public:
        /**
         * Get scripts
         * @return      Constant reference to scripts
         */
        std::vector<Script> &get_scripts() noexcept;

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
         * Unload all script
         */
        void unload_all_scripts() noexcept;

        /**
         * Unload global scripts
         */
        void unload_global_scripts() noexcept;

        /**
         * Unload map scripts
         */
        void unload_map_script() noexcept;

        /**
         * Constructor for Lua library
         */
        Library() noexcept;

        /** Events dispatchers */
        static bool multiplayer_sound_event(HaloData::MultiplayerSound sound) noexcept;

        /** 
         * Unload script callback
         * This function will be called when Chimera unloads a script, so we need to unload it too
         */
        static int lua_unload_script(lua_State *state) noexcept;

    private:
        /** Loaded scripts */
        std::vector<Script> scripts;
    };

    /**
     * Lua library entry point
     */
    extern "C" __declspec(dllexport) int luaopen_mods_harmony(lua_State *state) noexcept;
}

#endif 
