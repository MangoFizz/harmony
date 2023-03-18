// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__DEVICE_MACHINE_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__DEVICE_MACHINE_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "device.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class MachineType : std::uint16_t {
		DOOR = 0,
		PLATFORM,
		GEAR,
	};

	enum class MachineCollisionResponse : std::uint16_t {
		PAUSE_UNTIL_CRUSHED = 0,
		REVERSE_DIRECTIONS,
	};

	struct MachineFlags {
		std::uint16_t pathfinding_obstacle : 1;
		std::uint16_t but_not_when_open : 1;
		std::uint16_t elevator : 1;
	};
	static_assert(sizeof(MachineFlags) == sizeof(std::uint16_t));

	struct DeviceMachine : public Device {
		Memory::BigEndian<MachineType> machine_type;
		Memory::BigEndian<MachineFlags> machine_flags;
		Memory::BigEndian<float> door_open_time;
		PADDING(80);
		Memory::BigEndian<MachineCollisionResponse> collision_response;
		Index elevator_node;
		PADDING(52);
		Memory::BigEndian<std::uint32_t> door_open_time_ticks;
	};
	static_assert(sizeof(DeviceMachine) == 804);

}

#endif

