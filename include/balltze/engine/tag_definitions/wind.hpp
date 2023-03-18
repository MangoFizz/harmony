// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__WIND_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__WIND_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct Wind {
		float velocity[2];
		Euler2D variation_area;
		float local_variation_weight;
		float local_variation_rate;
		float damping;
		PADDING(36);
	};
	static_assert(sizeof(Wind) == 64);

}

#endif

