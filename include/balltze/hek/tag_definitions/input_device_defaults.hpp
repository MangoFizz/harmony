// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__INPUT_DEVICE_DEFAULTS_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__INPUT_DEVICE_DEFAULTS_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class InputDeviceDefaultsDeviceType : std::uint16_t {
		MOUSE_AND_KEYBOARD = 0,
		JOYSTICKS_GAMEPADS_ETC,
		FULL_PROFILE_DEFINITION,
	};

	struct InputDeviceDefaultsFlags {
		std::uint16_t unused : 1;
	};
	static_assert(sizeof(InputDeviceDefaultsFlags) == sizeof(std::uint16_t));

	struct InputDeviceDefaults {
		Memory::BigEndian<InputDeviceDefaultsDeviceType> device_type;
		Memory::BigEndian<InputDeviceDefaultsFlags> flags;
		TagDataOffset device_id;
		TagDataOffset profile;
	};
	static_assert(sizeof(InputDeviceDefaults) == 44);

}

#endif

