// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__DEVICE_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__DEVICE_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "object.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class DeviceIn : std::uint16_t {
		NONE = 0,
		POWER,
		CHANGE_IN_POWER,
		POSITION,
		CHANGE_IN_POSITION,
		LOCKED,
		DELAY,
	};

	struct DeviceFlags {
		std::uint32_t position_loops : 1;
		std::uint32_t position_not_interpolated : 1;
	};
	static_assert(sizeof(DeviceFlags) == sizeof(std::uint32_t));

	struct Device : public Object {
		DeviceFlags device_flags;
		float power_transition_time;
		float power_acceleration_time;
		float position_transition_time;
		float position_acceleration_time;
		float depowered_position_transition_time;
		float depowered_position_acceleration_time;
		DeviceIn device_a_in;
		DeviceIn device_b_in;
		DeviceIn device_c_in;
		DeviceIn device_d_in;
		TagDependency open;
		TagDependency close;
		TagDependency opened;
		TagDependency closed;
		TagDependency depowered;
		TagDependency repowered;
		float delay_time;
		PADDING(8);
		TagDependency delay_effect;
		float automatic_activation_radius;
		PADDING(84);
		float inverse_power_acceleration_time;
		float inverse_power_transition_time;
		float inverse_depowered_position_acceleration_time;
		float inverse_depowered_position_transition_time;
		float inverse_position_acceleration_time;
		float inverse_position_transition_time;
		float delay_time_ticks;
	};
	static_assert(sizeof(Device) == 656);

}

#endif

