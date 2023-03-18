// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__SHADER_TRANSPARENT_CHICAGO_EXTENDED_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__SHADER_TRANSPARENT_CHICAGO_EXTENDED_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "shader_transparent_generic.hpp"
#include "shader.hpp"
#include "shader_transparent_chicago.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct ShaderTransparentChicagoExtended : public Shader {
		Memory::BigEndian<std::uint8_t> numeric_counter_limit;
		Memory::BigEndian<ShaderTransparentGenericFlags> shader_transparent_chicago_extended_flags;
		Memory::BigEndian<ShaderFirstMapType> first_map_type;
		Memory::BigEndian<FramebufferBlendFunction> framebuffer_blend_function;
		Memory::BigEndian<FramebufferFadeMode> framebuffer_fade_mode;
		Memory::BigEndian<FunctionOut> framebuffer_fade_source;
		PADDING(2);
		Memory::BigEndian<float> lens_flare_spacing;
		TagDependency lens_flare;
		TagReflexive<ShaderTransparentExtraLayer> extra_layers;
		TagReflexive<ShaderTransparentChicagoMap> maps_4_stage;
		TagReflexive<ShaderTransparentChicagoMap> maps_2_stage;
		Memory::BigEndian<ShaderTransparentChicagoExtraFlags> extra_flags;
		PADDING(8);
	};
	static_assert(sizeof(ShaderTransparentChicagoExtended) == 120);

}

#endif

