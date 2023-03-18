// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__SHADER_TRANSPARENT_CHICAGO_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__SHADER_TRANSPARENT_CHICAGO_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "shader.hpp"
#include "shader_transparent_generic.hpp"

namespace Balltze::HEK::TagDefinitions { 
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
		Memory::BigEndian<ShaderTransparentChicagoMapFlags> flags;
		PADDING(2);
		PADDING(40);
		Memory::BigEndian<ShaderColorFunctionType> color_function;
		Memory::BigEndian<ShaderColorFunctionType> alpha_function;
		PADDING(36);
		Memory::BigEndian<float> map_u_scale;
		Memory::BigEndian<float> map_v_scale;
		Memory::BigEndian<float> map_u_offset;
		Memory::BigEndian<float> map_v_offset;
		Memory::BigEndian<float> map_rotation;
		Fraction mipmap_bias;
		TagDependency map;
		PADDING(40);
		Memory::BigEndian<FunctionOut> u_animation_source;
		Memory::BigEndian<WaveFunction> u_animation_function;
		Memory::BigEndian<float> u_animation_period;
		Memory::BigEndian<float> u_animation_phase;
		Memory::BigEndian<float> u_animation_scale;
		Memory::BigEndian<FunctionOut> v_animation_source;
		Memory::BigEndian<WaveFunction> v_animation_function;
		Memory::BigEndian<float> v_animation_period;
		Memory::BigEndian<float> v_animation_phase;
		Memory::BigEndian<float> v_animation_scale;
		Memory::BigEndian<FunctionOut> rotation_animation_source;
		Memory::BigEndian<WaveFunction> rotation_animation_function;
		Memory::BigEndian<float> rotation_animation_period;
		Memory::BigEndian<float> rotation_animation_phase;
		Memory::BigEndian<float> rotation_animation_scale;
		Point2D rotation_animation_center;
	};
	static_assert(sizeof(ShaderTransparentChicagoMap) == 220);

	struct ShaderTransparentChicago : public Shader {
		Memory::BigEndian<std::uint8_t> numeric_counter_limit;
		Memory::BigEndian<ShaderTransparentGenericFlags> shader_transparent_chicago_flags;
		Memory::BigEndian<ShaderFirstMapType> first_map_type;
		Memory::BigEndian<FramebufferBlendFunction> framebuffer_blend_function;
		Memory::BigEndian<FramebufferFadeMode> framebuffer_fade_mode;
		Memory::BigEndian<FunctionOut> framebuffer_fade_source;
		PADDING(2);
		Memory::BigEndian<float> lens_flare_spacing;
		TagDependency lens_flare;
		TagReflexive<ShaderTransparentExtraLayer> extra_layers;
		TagReflexive<ShaderTransparentChicagoMap> maps;
		Memory::BigEndian<ShaderTransparentChicagoExtraFlags> extra_flags;
		PADDING(8);
	};
	static_assert(sizeof(ShaderTransparentChicago) == 108);

}

#endif

