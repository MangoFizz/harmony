// SPDX-License-Identifier: GPL-3.0-only

#include "../../../messaging/console_output.hpp"
#include "../../../memory/signature.hpp"
#include "../../../harmony.hpp"
#include "../../command.hpp"

namespace Harmony {
    bool signature_address_command(int argc, const char **argv) {
        if(argc) {
            std::string signature_name = argv[0];
            auto &harmony = Harmony::get();
            if(harmony.signature_exists(signature_name)) {
                auto &sig = harmony.get_signature(signature_name);
                console_output("%s -> 0x%p", signature_name.c_str(), sig.get_data());
            }
            else {
                console_error("signature %s does not exists!", signature_name.c_str());
            }
        }
        return true;
    }
}
