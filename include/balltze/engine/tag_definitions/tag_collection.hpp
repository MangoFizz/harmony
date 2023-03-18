// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__TAG_COLLECTION_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__TAG_COLLECTION_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct TagCollectionTag {
		TagDependency reference;
	};
	static_assert(sizeof(TagCollectionTag) == 16);

	struct TagCollection {
		TagReflexive<TagCollectionTag> tags;
	};
	static_assert(sizeof(TagCollection) == 12);

}

#endif

