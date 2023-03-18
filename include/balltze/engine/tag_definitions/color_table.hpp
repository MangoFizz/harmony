// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__COLOR_TABLE_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__COLOR_TABLE_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct ColorTableColor {
		TagString name;
		ColorARGB color;
	};
	static_assert(sizeof(ColorTableColor) == 48);

	struct ColorTable {
		TagReflexive<ColorTableColor> colors;
	};
	static_assert(sizeof(ColorTable) == 12);

}

#endif

