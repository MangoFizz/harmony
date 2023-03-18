// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__LIGHT_VOLUME_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__LIGHT_VOLUME_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct LightVolumeFlags {
		std::uint16_t interpolate_color_in_hsv : 1;
		std::uint16_t more_colors : 1;
	};
	static_assert(sizeof(LightVolumeFlags) == sizeof(std::uint16_t));

	struct LightVolumeFrame {
		PADDING(16);
		Memory::BigEndian<float> offset_from_marker;
		Memory::BigEndian<float> offset_exponent;
		Memory::BigEndian<float> length;
		PADDING(32);
		Memory::BigEndian<float> radius_hither;
		Memory::BigEndian<float> radius_yon;
		Memory::BigEndian<float> radius_exponent;
		PADDING(32);
		ColorARGB tint_color_hither;
		ColorARGB tint_color_yon;
		Memory::BigEndian<float> tint_color_exponent;
		Memory::BigEndian<float> brightness_exponent;
		PADDING(32);
	};
	static_assert(sizeof(LightVolumeFrame) == 176);

	struct LightVolume {
		TagString attachment_marker;
		PADDING(2);
		Memory::BigEndian<LightVolumeFlags> flags;
		PADDING(16);
		Memory::BigEndian<float> near_fade_distance;
		Memory::BigEndian<float> far_fade_distance;
		Fraction perpendicular_brightness_scale;
		Fraction parallel_brightness_scale;
		Memory::BigEndian<FunctionOut> brightness_scale_source;
		PADDING(2);
		PADDING(20);
		TagDependency map;
		Index sequence_index;
		Memory::BigEndian<std::int16_t> count;
		PADDING(72);
		Memory::BigEndian<FunctionOut> frame_animation_source;
		PADDING(2);
		PADDING(36);
		PADDING(64);
		TagReflexive<LightVolumeFrame> frames;
		PADDING(32);
	};
	static_assert(sizeof(LightVolume) == 332);

}

#endif

