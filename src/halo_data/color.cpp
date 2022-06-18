// SPDX-License-Identifier: GPL-3.0-only

#include <cstring>
#include "console.hpp"

namespace Harmony::HaloData {
    /**
     * Useful for assembly stuff
     */
    extern "C" {
        ColorARGB *get_colorargb_white() {
            static ColorARGB color = {1.0f, 1.0f, 1.0f, 1.0f};
            return &color;
        }
    }
}