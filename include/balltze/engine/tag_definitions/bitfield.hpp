// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__BITFIELD_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__BITFIELD_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct IsUnusedFlag {
		std::uint32_t unused : 1;
	};
	static_assert(sizeof(IsUnusedFlag) == sizeof(std::uint32_t));

	struct IsUnfilteredFlag {
		std::uint16_t unfiltered : 1;
	};
	static_assert(sizeof(IsUnfilteredFlag) == sizeof(std::uint16_t));

	struct ColorInterpolationFlags {
		std::uint32_t blend_in_hsv : 1;
		std::uint32_t more_colors : 1;
	};
	static_assert(sizeof(ColorInterpolationFlags) == sizeof(std::uint32_t));

}

#endif

