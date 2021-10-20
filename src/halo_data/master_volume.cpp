// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "master_volume.hpp"

namespace Harmony::HaloData {
    std::uint8_t get_master_volume() noexcept {
        static auto &master_volume_sig = Harmony::get().get_signature("master_volume");
        static auto *master_volume = *reinterpret_cast<std::uint8_t **>(master_volume_sig.get_data()) + 0xB78;
        return *master_volume;
    }
}
