// SPDX-License-Identifier: GPL-3.0-only

#include <cstdint>
#include "../command.hpp"
#include "client.hpp"

namespace Harmony {
    std::vector<Command> get_client_commands() noexcept {
        std::vector<Command> commands;

        #define ADD_COMMAND(name, category, help, command_fn, ...) { \
            extern bool command_fn(int, const char **); \
            commands.emplace_back(name, category, help, command_fn, __VA_ARGS__); \
        }

        ADD_COMMAND("harmony_player_update_log", "debug", "Set whether or not to log client player updates", client_player_update_log_command, true, 0, 1);
        ADD_COMMAND("harmony_hs_debug", "debug", "Set whether or not to print hs functions calls", hs_debug_command, true, 0, 1);
        ADD_COMMAND("harmony_signature", "debug", "Get address for signature", signature_address_command, false, 1);

        return std::move(commands);
    }
}