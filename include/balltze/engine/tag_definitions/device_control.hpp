// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__DEVICE_CONTROL_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__DEVICE_CONTROL_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "device.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class DeviceType : std::uint16_t {
		TOGGLE_SWITCH = 0,
		ON_BUTTON,
		OFF_BUTTON,
		CALL_BUTTON,
	};

	enum class DeviceTriggersWhen : std::uint16_t {
		TOUCHED_BY_PLAYER = 0,
		DESTROYED,
	};

	struct DeviceControl : public Device {
		DeviceType type;
		DeviceTriggersWhen triggers_when;
		float call_value;
		PADDING(80);
		TagDependency on;
		TagDependency off;
		TagDependency deny;
	};
	static_assert(sizeof(DeviceControl) == 792);

}

#endif

