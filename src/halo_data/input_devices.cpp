// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "input_devices.hpp"

namespace Harmony::HaloData {
    InputGlobals &InputGlobals::get() {
        static auto &input_globals_sig = Harmony::get().get_signature("input_globals");
        static InputGlobals *input_globals = *reinterpret_cast<InputGlobals **>(input_globals_sig.get_data());
        return *input_globals;
    }
}