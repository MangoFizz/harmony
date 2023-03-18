// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__SOUND_ENVIRONMENT_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__SOUND_ENVIRONMENT_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct SoundEnvironment {
		std::int32_t unknown;
		std::int16_t priority;
		PADDING(2);
		Fraction room_intensity;
		Fraction room_intensity_hf;
		float room_rolloff;
		float decay_time;
		float decay_hf_ratio;
		Fraction reflections_intensity;
		float reflections_delay;
		Fraction reverb_intensity;
		float reverb_delay;
		float diffusion;
		float density;
		float hf_reference;
		PADDING(16);
	};
	static_assert(sizeof(SoundEnvironment) == 72);

}

#endif

