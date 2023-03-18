// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__FONT_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__FONT_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct FontCharacterIndex {
		Index character_index;
	};
	static_assert(sizeof(FontCharacterIndex) == 2);

	struct FontCharacterTables {
		TagReflexive<FontCharacterIndex> character_table;
	};
	static_assert(sizeof(FontCharacterTables) == 12);

	struct FontCharacter {
		std::uint16_t character;
		std::int16_t character_width;
		std::int16_t bitmap_width;
		std::int16_t bitmap_height;
		std::int16_t bitmap_origin_x;
		std::int16_t bitmap_origin_y;
		std::uint16_t hardware_character_index;
		PADDING(2);
		std::int32_t pixels_offset;
	};
	static_assert(sizeof(FontCharacter) == 20);

	struct Font {
		std::int32_t flags;
		std::int16_t ascending_height;
		std::int16_t descending_height;
		std::int16_t leading_height;
		std::int16_t leading_width;
		PADDING(36);
		TagReflexive<FontCharacterTables> character_tables;
		TagDependency bold;
		TagDependency italic;
		TagDependency condense;
		TagDependency underline;
		TagReflexive<FontCharacter> characters;
		TagDataOffset pixels;
	};
	static_assert(sizeof(Font) == 156);

}

#endif

