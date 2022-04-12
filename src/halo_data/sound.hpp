// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HALO_DATA_SOUND_HPP
#define HARMONY_HALO_DATA_SOUND_HPP

#include "tag.hpp"

namespace Harmony::HaloData {
    /**
     * Play a sound
     * @param sound     Tag ID of the sound
     */
    void play_sound(TagID sound) noexcept;
}

#endif
