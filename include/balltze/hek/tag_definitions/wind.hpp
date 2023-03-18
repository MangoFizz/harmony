// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__WIND_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__WIND_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct Wind {
		Memory::BigEndian<float> velocity[2];
		Euler2D variation_area;
		Memory::BigEndian<float> local_variation_weight;
		Memory::BigEndian<float> local_variation_rate;
		Memory::BigEndian<float> damping;
		PADDING(36);
	};
	static_assert(sizeof(Wind) == 64);

}

#endif

