// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__SHADER_MODEL_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__SHADER_MODEL_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "shader.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class ShaderModelDetailMask : std::uint16_t {
		NONE = 0,
		REFLECTION_MASK_INVERSE,
		REFLECTION_MASK,
		SELF_ILLUMINATION_MASK_INVERSE,
		SELF_ILLUMINATION_MASK,
		CHANGE_COLOR_MASK_INVERSE,
		CHANGE_COLOR_MASK,
		AUXILIARY_MASK_INVERSE,
		AUXILIARY_MASK,
	};

	struct ShaderModelFlags {
		std::uint16_t detail_after_reflection : 1;
		std::uint16_t two_sided : 1;
		std::uint16_t not_alpha_tested : 1;
		std::uint16_t alpha_blended_decal : 1;
		std::uint16_t true_atmospheric_fog : 1;
		std::uint16_t disable_two_sided_culling : 1;
		std::uint16_t use_xbox_multipurpose_channel_order : 1;
	};
	static_assert(sizeof(ShaderModelFlags) == sizeof(std::uint16_t));

	struct ShaderModelMoreFlags {
		std::uint16_t no_random_phase : 1;
	};
	static_assert(sizeof(ShaderModelMoreFlags) == sizeof(std::uint16_t));

	struct ShaderModel : public Shader {
		ShaderModelFlags shader_model_flags;
		PADDING(2);
		PADDING(12);
		Fraction translucency;
		PADDING(16);
		FunctionNameNullable change_color_source;
		PADDING(2);
		PADDING(28);
		ShaderModelMoreFlags shader_model_more_flags;
		PADDING(2);
		FunctionNameNullable color_source;
		WaveFunction animation_function;
		float animation_period;
		ColorRGB animation_color_lower_bound;
		ColorRGB animation_color_upper_bound;
		PADDING(12);
		float map_u_scale;
		float map_v_scale;
		TagDependency base_map;
		PADDING(8);
		TagDependency multipurpose_map;
		PADDING(8);
		ShaderDetailFunction detail_function;
		ShaderModelDetailMask detail_mask;
		float detail_map_scale;
		TagDependency detail_map;
		float detail_map_v_scale;
		PADDING(12);
		FunctionOut u_animation_source;
		WaveFunction u_animation_function;
		float u_animation_period;
		float u_animation_phase;
		float u_animation_scale;
		FunctionOut v_animation_source;
		WaveFunction v_animation_function;
		float v_animation_period;
		float v_animation_phase;
		float v_animation_scale;
		FunctionOut rotation_animation_source;
		WaveFunction rotation_animation_function;
		float rotation_animation_period;
		float rotation_animation_phase;
		float rotation_animation_scale;
		Point2D rotation_animation_center;
		PADDING(8);
		float reflection_falloff_distance;
		float reflection_cutoff_distance;
		Fraction perpendicular_brightness;
		ColorRGB perpendicular_tint_color;
		Fraction parallel_brightness;
		ColorRGB parallel_tint_color;
		TagDependency reflection_cube_map;
		PADDING(16);
		float unknown;
		PADDING(16);
		PADDING(32);
	};
	static_assert(sizeof(ShaderModel) == 440);

}

#endif

