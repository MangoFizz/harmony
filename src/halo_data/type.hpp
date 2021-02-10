// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HALO_DATA_TYPE_HPP
#define HARMONY_HALO_DATA_TYPE_HPP

#include <cstdint> 

namespace Harmony::HaloData {
    union ElementID {
        std::uint16_t index;
        std::uint32_t id;

        ElementID(std::uint32_t id) {
            this->id = id;
        }
    };

    using PlayerID = ElementID;
}

#endif
