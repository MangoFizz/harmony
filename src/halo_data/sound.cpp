// SPDX-License-Identifier: GPL-3.0-only

#include "sound.hpp"

namespace Harmony::HaloData {
    extern "C" void play_sound_asm(TagID sound);

    void play_sound(TagID sound) noexcept {
        play_sound_asm(sound);
    }
}
