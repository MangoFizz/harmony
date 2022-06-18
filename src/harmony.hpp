// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HPP
#define HARMONY_HPP

#include <vector>
#include <memory>
#include <filesystem>

namespace Harmony {
    class Command;
    class Config;
    class Signature;

    namespace Lua {
        class Library;
    }

    namespace Optic {
        class Handler;
    }

    namespace Menu {
        class WidescreenOverride;
    }

    /** Harmony class */
    class Harmony {
    public:
        /** 
         * Get a signature
         * @param name  Name of signature
         * @return      Reference to signature
         */
        Signature &get_signature(std::string name) noexcept;

        /** 
         * Look for a signature
         * @param name  Name of signature
         * @return      True if signature exists, false if not
         */
        bool signature_exists(std::string name) noexcept;

        /**
         * Get commands
         * @param command_name  name of the desired command
         */
        Command *get_command(std::string command_name) noexcept;

        /**
         * Execute a command
         * @param command_name  name of the desired command
         */
        bool execute_command(std::string command_name, bool quiet = false) noexcept;

        /**
         * Load config
         */
        void load_config() noexcept;

        /**
         * Get config
         */
        Config &get_config() noexcept;

        /**
         * Get Lua library handler
         */
        Lua::Library &get_lua_library_handler() noexcept;

        /**
         * Get optic handler
         */
        Optic::Handler &get_optic_handler() noexcept;

        /**
         * Get widescreen override handle
         */
        Menu::WidescreenOverride &get_widescreen_override_handle() noexcept;

        /**
         * Get harmony data directory path
         */
        std::filesystem::path get_data_directory_path() noexcept;

        /**
         * Constructor for everything
         */
        Harmony();

        /**
         * Get current Harmony instance
         * @return  Reference to Harmony instance
         */
        static Harmony &get();

    private:
        /** Harmony signatures */
        std::vector<Signature> signatures;

        /** Harmony console commands */
        std::vector<Command> commands;

        /** Command configs */
        std::unique_ptr<Config> config;

        /** Lua handler */
        std::unique_ptr<Lua::Library> lua_handler;

        /** Optic Handler */
        std::unique_ptr<Optic::Handler> optic_handler;

        /** Widescreen override */
        std::unique_ptr<Menu::WidescreenOverride> widescreen_fix_override;

        /** Instance pointer */
        static Harmony *instance;
    };
}

#endif
