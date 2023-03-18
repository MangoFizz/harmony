// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__VIRTUAL_KEYBOARD_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__VIRTUAL_KEYBOARD_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class VirtualKeyboardKeyboardKey : std::uint16_t {
		_1 = 0,
		_2,
		_3,
		_4,
		_5,
		_6,
		_7,
		_8,
		_9,
		_0,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		DONE,
		SHIFT,
		CAPS_LOCK,
		SYMBOLS,
		BACKSPACE,
		LEFT,
		RIGHT,
		SPACE,
	};

	struct VirtualKeyboardVirtualKey {
		Memory::BigEndian<VirtualKeyboardKeyboardKey> keyboard_key;
		Memory::BigEndian<std::int16_t> lowercase_character;
		Memory::BigEndian<std::int16_t> shift_character;
		Memory::BigEndian<std::int16_t> caps_character;
		Memory::BigEndian<std::int16_t> symbols_character;
		Memory::BigEndian<std::int16_t> shift_caps_character;
		Memory::BigEndian<std::int16_t> shift_symbols_character;
		Memory::BigEndian<std::int16_t> caps_symbols_character;
		TagDependency unselected_background_bitmap;
		TagDependency selected_background_bitmap;
		TagDependency active_background_bitmap;
		TagDependency sticky_background_bitmap;
	};
	static_assert(sizeof(VirtualKeyboardVirtualKey) == 80);

	struct VirtualKeyboard {
		TagDependency display_font;
		TagDependency background_bitmap;
		TagDependency special_key_labels_string_list;
		TagReflexive<VirtualKeyboardVirtualKey> virtual_keys;
	};
	static_assert(sizeof(VirtualKeyboard) == 60);

}

#endif

