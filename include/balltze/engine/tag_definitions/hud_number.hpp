// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__HUD_NUMBER_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__HUD_NUMBER_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct HudNumber {
		TagDependency digits_bitmap;
		std::int8_t bitmap_digit_width;
		std::int8_t screen_digit_width;
		std::int8_t x_offset;
		std::int8_t y_offset;
		std::int8_t decimal_point_width;
		std::int8_t colon_width;
		PADDING(2);
		PADDING(76);
	};
	static_assert(sizeof(HudNumber) == 100);

}

#endif

