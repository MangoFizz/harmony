// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__SHADER_TRANSPARENT_METER_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__SHADER_TRANSPARENT_METER_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "shader.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct ShaderTransparentMeterFlags {
		std::uint16_t decal : 1;
		std::uint16_t two_sided : 1;
		std::uint16_t flash_color_is_negative : 1;
		std::uint16_t tint_mode_2 : 1;
		std::uint16_t unfiltered : 1;
	};
	static_assert(sizeof(ShaderTransparentMeterFlags) == sizeof(std::uint16_t));

	struct ShaderTransparentMeter : public Shader {
		Memory::BigEndian<ShaderTransparentMeterFlags> meter_flags;
		PADDING(2);
		PADDING(32);
		TagDependency map;
		PADDING(32);
		ColorRGB gradient_min_color;
		ColorRGB gradient_max_color;
		ColorRGB background_color;
		ColorRGB flash_color;
		ColorRGB meter_tint_color;
		Fraction meter_transparency;
		Fraction background_transparency;
		PADDING(24);
		Memory::BigEndian<FunctionOut> meter_brightness_source;
		Memory::BigEndian<FunctionOut> flash_brightness_source;
		Memory::BigEndian<FunctionOut> value_source;
		Memory::BigEndian<FunctionOut> gradient_source;
		Memory::BigEndian<FunctionOut> flash_extension_source;
		PADDING(2);
		PADDING(32);
	};
	static_assert(sizeof(ShaderTransparentMeter) == 260);

}

#endif

