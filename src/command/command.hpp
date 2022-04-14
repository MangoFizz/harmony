// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_COMMAND_HPP
#define HARMONY_COMMAND_HPP

#include <string>
#include <vector>

namespace Harmony {
    /** 
     * Split arguments from a console command
     * @param command   Console command input
     * @return          Splitted arguments
     */
    std::vector<std::string> split_arguments(std::string command) noexcept;
}

#endif

