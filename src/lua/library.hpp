// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_LIBRARY_HPP
#define HARMONY_LUA_LIBRARY_HPP

#include <string>
#include <vector>
#include <lua.hpp>

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
