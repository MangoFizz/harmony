// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HALO_DATA_TYPE_HPP
#define HARMONY_HALO_DATA_TYPE_HPP

#include <cstdint> 

namespace Harmony::HaloData {
    union ElementID {
        std::uint32_t whole_id;
        struct {
            std::uint16_t index;
            std::uint16_t id;
        } index;

        ElementID(std::uint32_t id) {
            this->whole_id = id;
        }

        static ElementID null_id() noexcept {
            return { 0xFFFFFFFF };
        }

        bool is_null() const noexcept {
            return *this == null_id();
        }

        bool operator==(const ElementID &other) const noexcept {
            return this->whole_id == other.whole_id;
        }

        bool operator!=(const ElementID &other) const noexcept {
            return this->whole_id != other.whole_id;
        }
    };

    using PlayerID = ElementID;
}

#endif
