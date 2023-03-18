// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__MATERIAL_EFFECTS_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__MATERIAL_EFFECTS_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct MaterialEffectsMaterialEffectMaterial {
		TagDependency effect;
		TagDependency sound;
		PADDING(16);
	};
	static_assert(sizeof(MaterialEffectsMaterialEffectMaterial) == 48);

	struct MaterialEffectsMaterialEffect {
		TagReflexive<MaterialEffectsMaterialEffectMaterial> materials;
		PADDING(16);
	};
	static_assert(sizeof(MaterialEffectsMaterialEffect) == 28);

	struct MaterialEffects {
		TagReflexive<MaterialEffectsMaterialEffect> effects;
		PADDING(128);
	};
	static_assert(sizeof(MaterialEffects) == 140);

}

#endif

