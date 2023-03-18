// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__STRING_LIST_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__STRING_LIST_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct StringListString {
		TagDataOffset string;
	};
	static_assert(sizeof(StringListString) == 20);

	struct StringList {
		TagReflexive<StringListString> strings;
	};
	static_assert(sizeof(StringList) == 12);

}

#endif

