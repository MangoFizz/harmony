// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY__COMMAND__COMMANDS__CLIENT_HPP
#define HARMONY__COMMAND__COMMANDS__CLIENT_HPP

#include <vector>

namespace Harmony {
    class Command;

    /**
     * get client commands
     * @return  Vector with all client commands
     */
    std::vector<Command> get_client_commands() noexcept;
}

#endif
