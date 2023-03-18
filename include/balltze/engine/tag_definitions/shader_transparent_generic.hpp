// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__SHADER_TRANSPARENT_GENERIC_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__SHADER_TRANSPARENT_GENERIC_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "shader.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class ShaderTransparentGenericStageInputColor : std::uint16_t {
		ZERO = 0,
		ONE,
		ONE_HALF,
		NEGATIVE_ONE,
		NEGATIVE_ONE_HALF,
		MAP_COLOR_0,
		MAP_COLOR_1,
		MAP_COLOR_2,
		MAP_COLOR_3,
		VERTEX_COLOR_0_DIFFUSE_LIGHT,
		VERTEX_COLOR_1_FADE_PERPENDICULAR,
		SCRATCH_COLOR_0,
		SCRATCH_COLOR_1,
		CONSTANT_COLOR_0,
		CONSTANT_COLOR_1,
		MAP_ALPHA_0,
		MAP_ALPHA_1,
		MAP_ALPHA_2,
		MAP_ALPHA_3,
		VERTEX_ALPHA_0_FADE_NONE,
		VERTEX_ALPHA_1_FADE_PERPENDICULAR,
		SCRATCH_ALPHA_0,
		SCRATCH_ALPHA_1,
		CONSTANT_ALPHA_0,
		CONSTANT_ALPHA_1,
	};

	enum class ShaderTransparentGenericStageInputAlpha : std::uint16_t {
		ZERO = 0,
		ONE,
		ONE_HALF,
		NEGATIVE_ONE,
		NEGATIVE_ONE_HALF,
		MAP_ALPHA_0,
		MAP_ALPHA_1,
		MAP_ALPHA_2,
		MAP_ALPHA_3,
		VERTEX_ALPHA_0_FADE_NONE,
		VERTEX_ALPHA_1_FADE_PERPENDICULAR,
		SCRATCH_ALPHA_0,
		SCRATCH_ALPHA_1,
		CONSTANT_ALPHA_0,
		CONSTANT_ALPHA_1,
		MAP_BLUE_0,
		MAP_BLUE_1,
		MAP_BLUE_2,
		MAP_BLUE_3,
		VERTEX_BLUE_0_BLUE_LIGHT,
		VERTEX_BLUE_1_FADE_PARALLEL,
		SCRATCH_BLUE_0,
		SCRATCH_BLUE_1,
		CONSTANT_BLUE_0,
		CONSTANT_BLUE_1,
	};

	enum class ShaderTransparentGenericStageInputMappingColor : std::uint16_t {
		CLAMP_X = 0,
		_1_CLAMP_X,
		_2,
		_1_2,
		CLAMP_X_1_2,
		_1_2_CLAMP_X,
		X,
		X_1,
	};

	enum class ShaderTransparentGenericStageOutputFunction : std::uint16_t {
		MULTIPLY = 0,
		DOT_PRODUCT,
	};

	enum class ShaderTransparentGenericStageOutputMapping : std::uint16_t {
		COLOR_IDENTITY = 0,
		COLOR_SCALE_BY_1_2,
		COLOR_SCALE_BY_2,
		COLOR_SCALE_BY_4,
		COLOR_BIAS_BY_1_2,
		COLOR_EXPAND_NORMAL,
	};

	enum class ShaderTransparentGenericStageOutput : std::uint16_t {
		ALPHA_DISCARD = 0,
		ALPHA_SCRATCH_ALPHA_0_FINAL_ALPHA,
		ALPHA_SCRATCH_ALPHA_1,
		ALPHA_VERTEX_ALPHA_0_FOG,
		ALPHA_VERTEX_ALPHA_1,
		ALPHA_MAP_ALPHA_0,
		ALPHA_MAP_ALPHA_1,
		ALPHA_MAP_ALPHA_2,
		ALPHA_MAP_ALPHA_3,
	};

	struct ShaderTransparentGenericMapFlag {
		std::uint16_t unfiltered : 1;
		std::uint16_t u_clamped : 1;
		std::uint16_t v_clamped : 1;
	};
	static_assert(sizeof(ShaderTransparentGenericMapFlag) == sizeof(std::uint16_t));

	struct ShaderTransparentGenericStageFlags {
		std::uint16_t color_mux : 1;
		std::uint16_t alpha_mux : 1;
		std::uint16_t a_out_controls_color0_animation : 1;
	};
	static_assert(sizeof(ShaderTransparentGenericStageFlags) == sizeof(std::uint16_t));

	struct ShaderTransparentGenericFlags {
		std::uint8_t alpha_tested : 1;
		std::uint8_t decal : 1;
		std::uint8_t two_sided : 1;
		std::uint8_t first_map_is_in_screenspace : 1;
		std::uint8_t draw_before_water : 1;
		std::uint8_t ignore_effect : 1;
		std::uint8_t scale_first_map_with_distance : 1;
		std::uint8_t numeric : 1;
	};
	static_assert(sizeof(ShaderTransparentGenericFlags) == sizeof(std::uint8_t));

	struct ShaderTransparentGenericMap {
		ShaderTransparentGenericMapFlag flags;
		PADDING(2);
		float map_u_scale;
		float map_v_scale;
		float map_u_offset;
		float map_v_offset;
		float map_rotation;
		Fraction mapmap_bias;
		TagDependency map;
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
	};
	static_assert(sizeof(ShaderTransparentGenericMap) == 100);

	struct ShaderTransparentGenericStage {
		ShaderTransparentGenericStageFlags flags;
		PADDING(2);
		FunctionNameNullable color0_source;
		WaveFunction color0_animation_function;
		float color0_animation_period;
		ColorARGB color0_animation_lower_bound;
		ColorARGB color0_animation_upper_bound;
		ColorARGB color1;
		ShaderTransparentGenericStageInputColor input_a;
		ShaderTransparentGenericStageInputMappingColor input_a_mapping;
		ShaderTransparentGenericStageInputColor input_b;
		ShaderTransparentGenericStageInputMappingColor input_b_mapping;
		ShaderTransparentGenericStageInputColor input_c;
		ShaderTransparentGenericStageInputMappingColor input_c_mapping;
		ShaderTransparentGenericStageInputColor input_d;
		ShaderTransparentGenericStageInputMappingColor input_d_mapping;
		ShaderTransparentGenericStageOutput output_ab;
		ShaderTransparentGenericStageOutputFunction output_ab_function;
		ShaderTransparentGenericStageOutput output_bc;
		ShaderTransparentGenericStageOutputFunction output_cd_function;
		ShaderTransparentGenericStageOutput output_ab_cd_mux_sum;
		ShaderTransparentGenericStageOutputMapping output_mapping_color;
		ShaderTransparentGenericStageInputAlpha input_a_alpha;
		ShaderTransparentGenericStageInputMappingColor input_a_mapping_alpha;
		ShaderTransparentGenericStageInputAlpha input_b_alpha;
		ShaderTransparentGenericStageInputMappingColor input_b_mapping_alpha;
		ShaderTransparentGenericStageInputAlpha input_c_alpha;
		ShaderTransparentGenericStageInputMappingColor input_c_mapping_alpha;
		ShaderTransparentGenericStageInputAlpha input_d_alpha;
		ShaderTransparentGenericStageInputMappingColor input_d_mapping_alpha;
		ShaderTransparentGenericStageOutput output_ab_alpha;
		ShaderTransparentGenericStageOutput output_cd_alpha;
		ShaderTransparentGenericStageOutput output_ab_cd_mux_sum_alpha;
		ShaderTransparentGenericStageOutputMapping output_mapping_alpha;
	};
	static_assert(sizeof(ShaderTransparentGenericStage) == 112);

	struct ShaderTransparentGeneric : public Shader {
		std::uint8_t numeric_counter_limit;
		ShaderTransparentGenericFlags shader_transparent_generic_flags;
		ShaderFirstMapType first_map_type;
		FramebufferBlendFunction framebuffer_blend_function;
		FramebufferFadeMode framebuffer_fade_mode;
		FunctionOut framebuffer_fade_source;
		PADDING(2);
		float lens_flare_spacing;
		TagDependency lens_flare;
		TagReflexive<ShaderTransparentExtraLayer> extra_layers;
		TagReflexive<ShaderTransparentGenericMap> maps;
		TagReflexive<ShaderTransparentGenericStage> stages;
	};
	static_assert(sizeof(ShaderTransparentGeneric) == 108);

}

#endif

