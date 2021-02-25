// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HALO_DATA_COLOR_HPP
#define HARMONY_HALO_DATA_COLOR_HPP

#include <cstdint>

namespace Harmony::HaloData {
    struct ColorARGB {
        float alpha = 1.0;
        float red = 1.0;
        float green = 1.0;
        float blue = 1.0;
    };
}

#endif
