// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__ANTENNA_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__ANTENNA_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct AntennaVertex {
		Fraction spring_strength_coefficient;
		PADDING(24);
		Euler2D angles;
		float length;
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
		float falloff_pixels;
		float cutoff_pixels;
		float length;
		PADDING(36);
		TagReflexive<AntennaVertex> vertices;
	};
	static_assert(sizeof(Antenna) == 208);

}

#endif

