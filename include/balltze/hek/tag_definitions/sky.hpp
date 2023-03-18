// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__SKY_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__SKY_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct SkyLightFlags {
		std::uint32_t affects_exteriors : 1;
		std::uint32_t affects_interiors : 1;
	};
	static_assert(sizeof(SkyLightFlags) == sizeof(std::uint32_t));

	struct SkyFunction {
		PADDING(4);
		TagString function_name;
	};
	static_assert(sizeof(SkyFunction) == 36);

	struct SkyAnimation {
		Memory::BigEndian<std::int16_t> animation_index;
		PADDING(2);
		Memory::BigEndian<float> period;
		PADDING(28);
	};
	static_assert(sizeof(SkyAnimation) == 36);

	struct SkyLight {
		TagDependency lens_flare;
		TagString lens_flare_marker_name;
		PADDING(28);
		Memory::BigEndian<SkyLightFlags> flags;
		ColorRGB color;
		Memory::BigEndian<float> power;
		Memory::BigEndian<float> test_distance;
		PADDING(4);
		Euler2D direction;
		Memory::BigEndian<float> diameter;
	};
	static_assert(sizeof(SkyLight) == 116);

	struct Sky {
		TagDependency model;
		TagDependency animation_graph;
		PADDING(24);
		ColorRGB indoor_ambient_radiosity_color;
		Memory::BigEndian<float> indoor_ambient_radiosity_power;
		ColorRGB outdoor_ambient_radiosity_color;
		Memory::BigEndian<float> outdoor_ambient_radiosity_power;
		ColorRGB outdoor_fog_color;
		PADDING(8);
		Fraction outdoor_fog_maximum_density;
		Memory::BigEndian<float> outdoor_fog_start_distance;
		Memory::BigEndian<float> outdoor_fog_opaque_distance;
		ColorRGB indoor_fog_color;
		PADDING(8);
		Fraction indoor_fog_maximum_density;
		Memory::BigEndian<float> indoor_fog_start_distance;
		Memory::BigEndian<float> indoor_fog_opaque_distance;
		TagDependency indoor_fog_screen;
		PADDING(4);
		TagReflexive<SkyFunction> shader_functions;
		TagReflexive<SkyAnimation> animations;
		TagReflexive<SkyLight> lights;
	};
	static_assert(sizeof(Sky) == 208);

}

#endif

