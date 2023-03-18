// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__UNICODE_STRING_LIST_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__UNICODE_STRING_LIST_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct UnicodeStringListString {
		TagDataOffset string;
	};
	static_assert(sizeof(UnicodeStringListString) == 20);

	struct UnicodeStringList {
		TagReflexive<UnicodeStringListString> strings;
	};
	static_assert(sizeof(UnicodeStringList) == 12);

}

#endif

