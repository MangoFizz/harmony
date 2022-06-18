// SPDX-License-Identifier: GPL-3.0-only

#include "../../../messaging/console_output.hpp"
#include "../../../debug/client_player_update_log.hpp"
#include "../../command.hpp"

namespace Harmony {
    bool client_player_update_log_command(int argc, const char **argv) {
        static bool setting = false;
        if(argc) {
            setting = STR_TO_BOOL(argv[0]);
            Debug::enable_client_player_update_log(setting);
        }
        console_output(BOOL_TO_STR(setting));
        return true;
    }
}
