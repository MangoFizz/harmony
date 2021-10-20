// SPDX-License-Identifier: GPL-3.0-only

#include "resolution.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"

namespace Harmony::HaloData {
    Resolution &get_resolution() noexcept {
        static auto &resolution_sig = Harmony::get().get_signature("resolution");
        static Resolution *resolution = *reinterpret_cast<Resolution **>(resolution_sig.get_data());
        return *resolution;
    }
}
