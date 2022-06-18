// SPDX-License-Identifier: GPL-3.0-only

#include <fstream>
#include <filesystem>
#include "../memory/hook.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "client_player_update_log.hpp"

namespace Harmony::Debug {
    static bool enabled = false;
    static std::ofstream client_player_update_log;

    extern "C" {
        char client_player_update_history_entry_buffer[256];
        std::int32_t client_player_update_history_entry_level;
        void client_player_update_history_entry_write_fn_override();
        const void *client_player_update_history_entry_write_fn = nullptr;

        void write_client_player_update_log_entry() noexcept {
            if(!client_player_update_log.is_open()) {
                return;
            }

            std::string log_level_prefix = "[Level " + std::to_string(client_player_update_history_entry_level) + "] ";
            std::string log_entry = client_player_update_history_entry_buffer;

            if(log_entry.back() == '\n') {
                log_entry.pop_back();
            }

            client_player_update_log << log_level_prefix << log_entry << std::endl;
            client_player_update_log.flush();
        }
    }

    static void open_log_file() noexcept {
        constexpr const char *log_file = "client_player_update.log";
        static auto data_directory = Harmony::get().get_data_directory_path();
        static auto debug_directory = data_directory / "debug";

        // Create debug directory if does not exists
        std::filesystem::create_directories(debug_directory);

        client_player_update_log.open(debug_directory / log_file, std::ios::out | std::ios::trunc);
    }

    void enable_client_player_update_log(bool setting) noexcept {
        if(setting != enabled) {
            enabled = setting;

            if(enabled) {
                open_log_file();
            }
            else {
                client_player_update_log.close();
            }
        }
    }

    void set_up_client_player_update_log() noexcept {
        static auto &harmony = Harmony::get();
        static auto &entry_write_sig = harmony.get_signature("client_player_update_history_entry_write_function");
        static Memory::FunctionOverride entry_write_hook;

        entry_write_hook.initialize(entry_write_sig.get_data(), reinterpret_cast<void *>(client_player_update_history_entry_write_fn_override), &client_player_update_history_entry_write_fn);
        entry_write_hook.hook();
    }
}
