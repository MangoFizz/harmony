// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__SHADER_TRANSPARENT_WATER_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__SHADER_TRANSPARENT_WATER_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "shader.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct ShaderTransparentWaterFlags {
		std::uint16_t base_map_alpha_modulates_reflection : 1;
		std::uint16_t base_map_color_modulates_background : 1;
		std::uint16_t atmospheric_fog : 1;
		std::uint16_t draw_before_fog : 1;
	};
	static_assert(sizeof(ShaderTransparentWaterFlags) == sizeof(std::uint16_t));

	struct ShaderTransparentWaterRipple {
		PADDING(2);
		PADDING(2);
		Fraction contribution_factor;
		PADDING(32);
		Angle animation_angle;
		float animation_velocity;
		Vector2D map_offset;
		std::uint16_t map_repeats;
		Index map_index;
		PADDING(16);
	};
	static_assert(sizeof(ShaderTransparentWaterRipple) == 76);

	struct ShaderTransparentWater : public Shader {
		ShaderTransparentWaterFlags water_flags;
		PADDING(2);
		PADDING(32);
		TagDependency base_map;
		PADDING(16);
		Fraction view_perpendicular_brightness;
		ColorRGB view_perpendicular_tint_color;
		Fraction view_parallel_brightness;
		ColorRGB view_parallel_tint_color;
		PADDING(16);
		TagDependency reflection_map;
		PADDING(16);
		Angle ripple_animation_angle;
		float ripple_animation_velocity;
		float ripple_scale;
		TagDependency ripple_maps;
		std::uint16_t ripple_mipmap_levels;
		PADDING(2);
		Fraction ripple_mipmap_fade_factor;
		float ripple_mipmap_detail_bias;
		PADDING(64);
		TagReflexive<ShaderTransparentWaterRipple> ripples;
		PADDING(16);
	};
	static_assert(sizeof(ShaderTransparentWater) == 320);

}

#endif

