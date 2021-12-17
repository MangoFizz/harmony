// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HALO_DATA_MASTER_VOLUME_HPP
#define HARMONY_HALO_DATA_MASTER_VOLUME_HPP

#include <cstdint>

namespace Harmony::HaloData {
    /**
     * Get the master volume
     */
    std::uint8_t get_master_volume() noexcept;
}

#endif
