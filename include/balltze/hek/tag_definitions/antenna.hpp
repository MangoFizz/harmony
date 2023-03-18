// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__ANTENNA_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__ANTENNA_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct AntennaVertex {
		Fraction spring_strength_coefficient;
		PADDING(24);
		Euler2D angles;
		Memory::BigEndian<float> length;
		Index sequence_index;
		PADDING(2);
		ColorARGB color;
		ColorARGB lod_color;
		PADDING(40);
		Point3D offset;
	};
	static_assert(sizeof(AntennaVertex) == 128);

	struct Antenna {
		TagString attachment_marker_name;
		TagDependency bitmaps;
		TagDependency physics;
		PADDING(80);
		Fraction spring_strength_coefficient;
		Memory::BigEndian<float> falloff_pixels;
		Memory::BigEndian<float> cutoff_pixels;
		Memory::BigEndian<float> length;
		PADDING(36);
		TagReflexive<AntennaVertex> vertices;
	};
	static_assert(sizeof(Antenna) == 208);

}

#endif

