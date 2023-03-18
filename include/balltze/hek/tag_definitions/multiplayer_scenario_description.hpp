// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__MULTIPLAYER_SCENARIO_DESCRIPTION_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__MULTIPLAYER_SCENARIO_DESCRIPTION_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct MultiplayerScenarioDescriptionScenarioDescription {
		TagDependency descriptive_bitmap;
		TagDependency displayed_map_name;
		TagString scenario_tag_directory_path;
		PADDING(4);
	};
	static_assert(sizeof(MultiplayerScenarioDescriptionScenarioDescription) == 68);

	struct MultiplayerScenarioDescription {
		TagReflexive<MultiplayerScenarioDescriptionScenarioDescription> multiplayer_scenarios;
	};
	static_assert(sizeof(MultiplayerScenarioDescription) == 12);

}

#endif

