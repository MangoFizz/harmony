// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__ITEM_COLLECTION_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__ITEM_COLLECTION_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct ItemCollectionPermutation {
		PADDING(32);
		float weight;
		TagDependency item;
		PADDING(32);
	};
	static_assert(sizeof(ItemCollectionPermutation) == 84);

	struct ItemCollection {
		TagReflexive<ItemCollectionPermutation> permutations;
		std::int16_t default_spawn_time;
		PADDING(2);
		PADDING(76);
	};
	static_assert(sizeof(ItemCollection) == 92);

}

#endif

