// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_MATH_COLOR_HPP
#define HARMONY_MATH_COLOR_HPP

#include <cstdint>

namespace Harmony::Math {
    struct ColorARGB {
        std::uint8_t a, r, g, b;
        
        friend bool operator==(const ColorARGB &color_a, const ColorARGB &color_b) {
            return color_a.a == color_b.a && color_a.r == color_b.r && color_a.g == color_b.g && color_a.b == color_b.b;
        }

        friend bool operator!=(const ColorARGB &color_a, const ColorARGB &color_b) {
            return !(color_a == color_b);
        }
    };
}

#endif
