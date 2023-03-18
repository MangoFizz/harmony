// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__SHADER_TRANSPARENT_CHICAGO_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__SHADER_TRANSPARENT_CHICAGO_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "shader.hpp"
#include "shader_transparent_generic.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct ShaderTransparentChicagoMapFlags {
		std::uint16_t unfiltered : 1;
		std::uint16_t alpha_replicate : 1;
		std::uint16_t u_clamped : 1;
		std::uint16_t v_clamped : 1;
	};
	static_assert(sizeof(ShaderTransparentChicagoMapFlags) == sizeof(std::uint16_t));

	struct ShaderTransparentChicagoExtraFlags {
		std::uint32_t dont_fade_active_camouflage : 1;
		std::uint32_t numeric_countdown_timer : 1;
		std::uint32_t custom_edition_blending : 1;
	};
	static_assert(sizeof(ShaderTransparentChicagoExtraFlags) == sizeof(std::uint32_t));

	struct ShaderTransparentChicagoMap {
		ShaderTransparentChicagoMapFlags flags;
		PADDING(2);
		PADDING(40);
		ShaderColorFunctionType color_function;
		ShaderColorFunctionType alpha_function;
		PADDING(36);
		float map_u_scale;
		float map_v_scale;
		float map_u_offset;
		float map_v_offset;
		float map_rotation;
		Fraction mipmap_bias;
		TagDependency map;
		PADDING(40);
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
	static_assert(sizeof(ShaderTransparentChicagoMap) == 220);

	struct ShaderTransparentChicago : public Shader {
		std::uint8_t numeric_counter_limit;
		ShaderTransparentGenericFlags shader_transparent_chicago_flags;
		ShaderFirstMapType first_map_type;
		FramebufferBlendFunction framebuffer_blend_function;
		FramebufferFadeMode framebuffer_fade_mode;
		FunctionOut framebuffer_fade_source;
		PADDING(2);
		float lens_flare_spacing;
		TagDependency lens_flare;
		TagReflexive<ShaderTransparentExtraLayer> extra_layers;
		TagReflexive<ShaderTransparentChicagoMap> maps;
		ShaderTransparentChicagoExtraFlags extra_flags;
		PADDING(8);
	};
	static_assert(sizeof(ShaderTransparentChicago) == 108);

}

#endif

