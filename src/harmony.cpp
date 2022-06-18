// SPDX-License-Identifier: GPL-3.0-only

#include <stdexcept>
#include <windows.h>
#include "command/command.hpp"
#include "command/config.hpp"
#include "debug/client_player_update_log.hpp"
#include "events/console_command.hpp"
#include "events/console_command.hpp"
#include "events/d3d9_end_scene.hpp"
#include "events/d3d9_reset.hpp"
#include "events/hs_function.hpp"
#include "events/keypress.hpp"
#include "events/widget_accept.hpp"
#include "events/widget_close.hpp"
#include "events/widget_list_tab.hpp"
#include "events/widget_mouse_button_press.hpp"
#include "events/widget_mouse_focus.hpp"
#include "events/widget_open.hpp"
#include "events/widget_sound.hpp"
#include "events/map_load.hpp"
#include "events/multiplayer_event.hpp"
#include "events/multiplayer_hit_sound.hpp"
#include "events/multiplayer_sound.hpp"
#include "events/tick.hpp"
#include "halo_data/path.hpp"
#include "lua/library.hpp"
#include "memory/signature.hpp"
#include "messaging/console_output.hpp"
#include "messaging/message_box.hpp"
#include "menu/widescreen_override.hpp"
#include "optic/handler.hpp"
#include "version.hpp"
#include "harmony.hpp"


namespace Harmony {
    static void first_tick() noexcept;
    static bool execute_commands(const char *command) noexcept;
    static void terminate() noexcept;

    Harmony *Harmony::instance = nullptr;

    Signature &Harmony::get_signature(std::string name) noexcept {
        for(auto &signature : this->signatures) {
            if(signature.get_name() == name) {
                return signature;
            }
        }

        // oops
        message_box("Signature %s does not exists. This may be a bug.", name);
        std::terminate();
    }

    bool Harmony::signature_exists(std::string name) noexcept {
        for(auto &signature : this->signatures) {
            if(signature.get_name() == name) {
                return true;
            }
        }
        return false;
    }

    Command *Harmony::get_command(std::string command_name) noexcept {
        for(auto &command : this->commands) {
            if(command.name() == command_name) {
                return &command;
            }
        }
        return nullptr;
    }

    bool Harmony::execute_command(std::string command_name, bool quiet) noexcept {
        auto input_slices = split_arguments(command_name);
        auto command = this->get_command(input_slices[0]);
        
        if(command) {
            bool output_enabled = output_is_enabled();
            if(quiet) {
                enable_output(false);
            }

            set_output_prefix(command->name());
            
            auto command_arguments = std::vector(input_slices.begin() + 1, input_slices.end());
            auto result = command->call(command_arguments);

            switch(result) {
                case CommandResult::COMMAND_RESULT_FAILED_NOT_ENOUGH_ARGUMENTS:
                    console_error("%s: Not enough arguments. Expected at least %d", command->name(), command->min_args());
                    break;
   
                case CommandResult::COMMAND_RESULT_FAILED_TOO_MANY_ARGUMENTS:
                    console_error("%s: Too many arguments. Expected at most %d", command->name(), command->max_args());
                    break;
   
                case CommandResult::COMMAND_RESULT_SUCCESS:
                    if(command->autosave() && command_arguments.size() > 0) {
                        this->config->set_settings_for_command(command->name(), command_arguments);
                    }
                    break;

                case CommandResult::COMMAND_RESULT_FAILED_ERROR_NOT_FOUND:
                    break;
   
                default:
                    console_warning("eep %s", input_slices[0].c_str());
                    break;
            }

            clear_output_prefix();

            if(quiet) {
                enable_output(output_enabled);
            }

            return true;
        }
        return false;
    }

    void Harmony::load_config() noexcept {
        this->config = std::make_unique<Config>(get_data_directory_path() / "commands.txt");\
        this->config->load();
    }

    Config &Harmony::get_config() noexcept {
        return *this->config;
    }

    Lua::Library &Harmony::get_lua_library_handler() noexcept{
        return *this->lua_handler;
    }

    Optic::Handler &Harmony::get_optic_handler() noexcept {
        return *this->optic_handler;
    }

    Menu::WidescreenOverride &Harmony::get_widescreen_override_handle() noexcept {
        return *this->widescreen_fix_override;
    }

    std::filesystem::path Harmony::get_data_directory_path() noexcept {
        return HaloData::get_path() / "harmony";
    }

    Harmony::Harmony() : signatures(Signature::find_signatures()), commands(Command::get_commands()) {
        // Set instance pointer
        instance = this;

        // Set up library handler
        this->lua_handler = std::make_unique<Lua::Library>();

        // Set up optic
        this->optic_handler = std::make_unique<Optic::Handler>();

        // Set up widescreen override
        this->widescreen_fix_override = std::make_unique<Menu::WidescreenOverride>();

        // Set error handling
        std::set_terminate(terminate);

        // Set up tick event hook
        set_up_tick_event();

        // Set up map load hook
        set_up_map_load_event();

        // Add first tick event
        add_tick_event(first_tick);
    }

    Harmony &Harmony::get() {
        return *Harmony::instance;
    }

    extern "C" std::byte *get_address_for_signature(const char *name) noexcept {
        return Harmony::get().get_signature(name).get_data();
    }

    static void first_tick() noexcept {
        auto &harmony = Harmony::get();

        // Delayed config load
        harmony.load_config();

        // remove this event, we only need to run it once
        remove_tick_event(first_tick);

        // Set up d3d9 events
        set_up_d3d9_end_scene_event();
        set_up_d3d9_reset_event();

        // Set up multiplayer events
        set_up_multiplayer_event();
        set_up_multiplayer_hit_sound_event();
        set_up_multiplayer_sounds_event();

        // Widget events
        set_up_widget_accept_event();
        set_up_widget_close_event();
        set_up_widget_mouse_button_press_event();
        set_up_widget_list_tab_event();
        set_up_widget_mouse_focus_event();
        set_up_widget_open_event();
        set_up_widget_sound_event();

        // Set up script event
        set_up_hs_function_event();

        // Set up input event
        set_up_keypress_event();

        // Set up console commands
        set_up_console_command_event();

        // Add execute command function
        add_console_command_event(execute_commands);

        // Set up debug stuff
        Debug::set_up_client_player_update_log();

        // Override Chimera's widescreen fix
        harmony.get_widescreen_override_handle().enable(true);
    }

    static bool execute_commands(const char *console_input) noexcept {
        static auto &harmony = Harmony::get();
        return !harmony.execute_command(console_input);
    }

    static void terminate() noexcept {
        message_box("Uncaught exception. This may be a bug.");
        std::abort();
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch(fdwReason) {
        case DLL_PROCESS_ATTACH:
            new Harmony::Harmony();
            break;

        default:
            break;
    }
    return TRUE;
}
