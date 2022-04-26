// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_SCRIPT_HPP
#define HARMONY_LUA_SCRIPT_HPP

#include <string>
#include <vector>
#include <map>
#include <lua.hpp>
#include "api/math.hpp"
#include "api/time.hpp"
#include "../optic/container.hpp"

namespace Harmony::Lua {
    class Script {
    friend class Library;
    public:
        enum CallbackType {
            CALLBACK_TYPE_MULTIPLAYER_EVENT,
            CALLBACK_TYPE_MULTIPLAYER_SOUND,
            CALLBACK_TYPE_MENU_ACCEPT,
            CALLBACK_TYPE_WIDGET_ACCEPT,
            CALLBACK_TYPE_WIDGET_BACK,
            CALLBACK_TYPE_WIDGET_LIST_TAB,
            CALLBACK_TYPE_WIDGET_MOUSE_BUTTON_PRESS,
            CALLBACK_TYPE_WIDGET_MOUSE_FOCUS,
            CALLBACK_TYPE_WIDGET_OPEN,
            CALLBACK_TYPE_WIDGET_SOUND,
            CALLBACK_TYPE_HS_FUNCTION,
            CALLBACK_TYPE_KEYPRESS,
            CALLBACK_TYPE_INVALID
        };

        /**
         * Get script name
         */
        std::string get_name() const noexcept;

        /**
         * Get script type
         */
        std::string get_type() const noexcept;

        /**
         * Get data path
         */
        std::string get_data_path() const noexcept;

        /**
         * Check if the path is inside of the script data directory
         * @param path  Path to check
         * @return      True if the path is valid, false if not
         */
        bool path_is_valid(std::string path) noexcept;

        /**
         * Get callbacks
         */
        std::vector<std::string> &get_callbacks(CallbackType callback) noexcept;
        
        /**
         * Register a callback
         */
        void add_callback(CallbackType callback, std::string function) noexcept;

        /**
         * Get optic container
         */
        Optic::Container *get_optic_container() noexcept;

        /**
         * Get math API store
         */
        ScriptMathApiStore &get_math_api_store() noexcept;

        /**
         * Get time API store
         */
        ScriptTimeApiStore &get_time_api_store() noexcept;

        /**
         * Get require count
         */
        std::size_t get_require_count() const noexcept;

        /**
         * Get script state
         */
        lua_State *get_state() noexcept;

        /**
         * Get global from script
         */
        std::string get_global(std::string name) const noexcept;


        /**
         * Print last error of script state
         */
        void print_last_error() noexcept;

        /**
         * Constructor for script
         * @param state     Pointer to Lua script state
         */
        Script(lua_State *state) noexcept;

        /**
         * Destructor for script
         */
        ~Script() noexcept;

        /**
         * Equals operator for std::find function
         */
        inline bool operator==(const std::string name) {
            return this->name == name;
        }

        /**
         * Get script name from state
         * @param state     Pointer to Lua script state
         * @param global    Name of the global
         * @return          Global value
         */
        static std::string get_global_from_state(lua_State *state, const char *global) noexcept;

        /**
         * Get script name from state
         * @param state     Pointer to Lua script state
         */
        static std::string get_script_name_from_state(lua_State *state) noexcept;

    private:
        /** Name of the script */
        std::string name;

        /** is the script global? */
        std::string type;

        /** Data directory */
        std::string data_path;

        /** Script callbacks */
        std::map<CallbackType, std::vector<std::string>> callbacks;

        /** Optic container */
        Optic::Container *optic_container;

        /** Math API store */
        ScriptMathApiStore math_api_store;

        /** Time API store */
        ScriptTimeApiStore time_api_store;

        /** Number of times this script required harmony */
        std::size_t require_count;

        /** The script itself */
        lua_State *script;

        /**
         * Get script data directory from state
         * @return      Data folder path
         */
        std::string get_script_data_path() noexcept;
    };
}

#endif
