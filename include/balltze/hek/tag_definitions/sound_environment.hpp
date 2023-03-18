// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__SOUND_ENVIRONMENT_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__SOUND_ENVIRONMENT_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct SoundEnvironment {
		Memory::BigEndian<std::int32_t> unknown;
		Memory::BigEndian<std::int16_t> priority;
		PADDING(2);
		Fraction room_intensity;
		Fraction room_intensity_hf;
		Memory::BigEndian<float> room_rolloff;
		Memory::BigEndian<float> decay_time;
		Memory::BigEndian<float> decay_hf_ratio;
		Fraction reflections_intensity;
		Memory::BigEndian<float> reflections_delay;
		Fraction reverb_intensity;
		Memory::BigEndian<float> reverb_delay;
		Memory::BigEndian<float> diffusion;
		Memory::BigEndian<float> density;
		Memory::BigEndian<float> hf_reference;
		PADDING(16);
	};
	static_assert(sizeof(SoundEnvironment) == 72);

}

#endif

