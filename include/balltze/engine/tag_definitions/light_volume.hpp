// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__LIGHT_VOLUME_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__LIGHT_VOLUME_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct LightVolumeFlags {
		std::uint16_t interpolate_color_in_hsv : 1;
		std::uint16_t more_colors : 1;
	};
	static_assert(sizeof(LightVolumeFlags) == sizeof(std::uint16_t));

	struct LightVolumeFrame {
		PADDING(16);
		float offset_from_marker;
		float offset_exponent;
		float length;
		PADDING(32);
		float radius_hither;
		float radius_yon;
		float radius_exponent;
		PADDING(32);
		ColorARGB tint_color_hither;
		ColorARGB tint_color_yon;
		float tint_color_exponent;
		float brightness_exponent;
		PADDING(32);
	};
	static_assert(sizeof(LightVolumeFrame) == 176);

	struct LightVolume {
		TagString attachment_marker;
		PADDING(2);
		LightVolumeFlags flags;
		PADDING(16);
		float near_fade_distance;
		float far_fade_distance;
		Fraction perpendicular_brightness_scale;
		Fraction parallel_brightness_scale;
		FunctionOut brightness_scale_source;
		PADDING(2);
		PADDING(20);
		TagDependency map;
		Index sequence_index;
		std::int16_t count;
		PADDING(72);
		FunctionOut frame_animation_source;
		PADDING(2);
		PADDING(36);
		PADDING(64);
		TagReflexive<LightVolumeFrame> frames;
		PADDING(32);
	};
	static_assert(sizeof(LightVolume) == 332);

}

#endif

