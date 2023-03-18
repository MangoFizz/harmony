// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__UNIT_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__UNIT_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "object.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class UnitFunctionIn : std::uint16_t {
		NONE = 0,
		DRIVER_SEAT_POWER,
		GUNNER_SEAT_POWER,
		AIMING_CHANGE,
		MOUTH_APERTURE,
		INTEGRATED_LIGHT_POWER,
		CAN_BLINK,
		SHIELD_SAPPING,
	};

	enum class UnitDefaultTeam : std::uint16_t {
		NONE = 0,
		PLAYER,
		HUMAN,
		COVENANT,
		FLOOD,
		SENTINEL,
		UNUSED6,
		UNUSED7,
		UNUSED8,
		UNUSED9,
	};

	enum class UnitMotionSensorBlipSize : std::uint16_t {
		MEDIUM = 0,
		SMALL,
		LARGE,
	};

	enum class MetagameType : std::uint16_t {
		BRUTE = 0,
		GRUNT,
		JACKAL,
		SKIRMISHER,
		MARINE,
		SPARTAN,
		BUGGER,
		HUNTER,
		FLOOD_INFECTION,
		FLOOD_CARRIER,
		FLOOD_COMBAT,
		FLOOD_PURE,
		SENTINEL,
		ELITE,
		ENGINEER,
		MULE,
		TURRET,
		MONGOOSE,
		WARTHOG,
		SCORPION,
		HORNET,
		PELICAN,
		REVENANT,
		SERAPH,
		SHADE,
		WATCHTOWER,
		GHOST,
		CHOPPER,
		MAULER,
		WRAITH,
		BANSHEE,
		PHANTOM,
		SCARAB,
		GUNTOWER,
		TUNING_FORK,
		BROADSWORD,
		MAMMOTH,
		LICH,
		MANTIS,
		WASP,
		PHAETON,
		BISHOP,
		KNIGHT,
		PAWN,
	};

	enum class MetagameClass : std::uint16_t {
		INFANTRY = 0,
		LEADER,
		HERO,
		SPECIALIST,
		LIGHT_VEHICLE,
		HEAVY_VEHICLE,
		GIANT_VEHICLE,
		STANDARD_VEHICLE,
	};

	struct UnitFlags {
		std::uint32_t circular_aiming : 1;
		std::uint32_t destroyed_after_dying : 1;
		std::uint32_t half_speed_interpolation : 1;
		std::uint32_t fires_from_camera : 1;
		std::uint32_t entrance_inside_bounding_sphere : 1;
		std::uint32_t unused : 1;
		std::uint32_t causes_passenger_dialogue : 1;
		std::uint32_t resists_pings : 1;
		std::uint32_t melee_attack_is_fatal : 1;
		std::uint32_t dont_reface_during_pings : 1;
		std::uint32_t has_no_aiming : 1;
		std::uint32_t simple_creature : 1;
		std::uint32_t impact_melee_attaches_to_unit : 1;
		std::uint32_t impact_melee_dies_on_shields : 1;
		std::uint32_t cannot_open_doors_automatically : 1;
		std::uint32_t melee_attackers_cannot_attach : 1;
		std::uint32_t not_instantly_killed_by_melee : 1;
		std::uint32_t shield_sapping : 1;
		std::uint32_t runs_around_flaming : 1;
		std::uint32_t inconsequential : 1;
		std::uint32_t special_cinematic_unit : 1;
		std::uint32_t ignored_by_autoaiming : 1;
		std::uint32_t shields_fry_infection_forms : 1;
		std::uint32_t integrated_light_cntrls_weapon : 1;
		std::uint32_t integrated_light_lasts_forever : 1;
	};
	static_assert(sizeof(UnitFlags) == sizeof(std::uint32_t));

	struct UnitSeatFlags {
		std::uint32_t invisible : 1;
		std::uint32_t locked : 1;
		std::uint32_t driver : 1;
		std::uint32_t gunner : 1;
		std::uint32_t third_person_camera : 1;
		std::uint32_t allows_weapons : 1;
		std::uint32_t third_person_on_enter : 1;
		std::uint32_t first_person_camera_slaved_to_gun : 1;
		std::uint32_t allow_vehicle_communication_animations : 1;
		std::uint32_t not_valid_without_driver : 1;
		std::uint32_t allow_ai_noncombatants : 1;
	};
	static_assert(sizeof(UnitSeatFlags) == sizeof(std::uint32_t));

	struct UnitPoweredSeat {
		PADDING(4);
		Memory::BigEndian<float> driver_powerup_time;
		Memory::BigEndian<float> driver_powerdown_time;
		PADDING(56);
	};
	static_assert(sizeof(UnitPoweredSeat) == 68);

	struct UnitCameraTrack {
		TagDependency track;
		PADDING(12);
	};
	static_assert(sizeof(UnitCameraTrack) == 28);

	struct UnitUnitHudInterface {
		TagDependency hud;
		PADDING(32);
	};
	static_assert(sizeof(UnitUnitHudInterface) == 48);

	struct UnitSeat {
		Memory::BigEndian<UnitSeatFlags> flags;
		TagString label;
		TagString marker_name;
		PADDING(32);
		Vector3D acceleration_scale;
		PADDING(12);
		Memory::BigEndian<float> yaw_rate;
		Memory::BigEndian<float> pitch_rate;
		TagString camera_marker_name;
		TagString camera_submerged_marker_name;
		Angle pitch_auto_level;
		Angle pitch_range[2];
		TagReflexive<UnitCameraTrack> camera_tracks;
		TagReflexive<UnitUnitHudInterface> unit_hud_interface;
		PADDING(4);
		Index hud_text_message_index;
		PADDING(2);
		Angle yaw_minimum;
		Angle yaw_maximum;
		TagDependency built_in_gunner;
		PADDING(20);
	};
	static_assert(sizeof(UnitSeat) == 284);

	struct UnitWeapon {
		TagDependency weapon;
		PADDING(20);
	};
	static_assert(sizeof(UnitWeapon) == 36);

	struct UnitDialogueVariant {
		Memory::BigEndian<std::int16_t> variant_number;
		PADDING(2);
		PADDING(4);
		TagDependency dialogue;
	};
	static_assert(sizeof(UnitDialogueVariant) == 24);

	struct Unit : public Object {
		Memory::BigEndian<UnitFlags> unit_flags;
		Memory::BigEndian<UnitDefaultTeam> default_team;
		Memory::BigEndian<ObjectNoise> constant_sound_volume;
		Memory::BigEndian<float> rider_damage_fraction;
		TagDependency integrated_light_toggle;
		Memory::BigEndian<UnitFunctionIn> unit_a_in;
		Memory::BigEndian<UnitFunctionIn> unit_b_in;
		Memory::BigEndian<UnitFunctionIn> unit_c_in;
		Memory::BigEndian<UnitFunctionIn> unit_d_in;
		Angle camera_field_of_view;
		Memory::BigEndian<float> camera_stiffness;
		TagString camera_marker_name;
		TagString camera_submerged_marker_name;
		Angle pitch_auto_level;
		Angle pitch_range[2];
		TagReflexive<UnitCameraTrack> camera_tracks;
		Point3D seat_acceleration_scale;
		PADDING(12);
		Memory::BigEndian<float> soft_ping_threshold;
		Memory::BigEndian<float> soft_ping_interrupt_time;
		Memory::BigEndian<float> hard_ping_threshold;
		Memory::BigEndian<float> hard_ping_interrupt_time;
		Memory::BigEndian<float> hard_death_threshold;
		Memory::BigEndian<float> feign_death_threshold;
		Memory::BigEndian<float> feign_death_time;
		Memory::BigEndian<float> distance_of_evade_anim;
		Memory::BigEndian<float> distance_of_dive_anim;
		PADDING(4);
		Memory::BigEndian<float> stunned_movement_threshold;
		Memory::BigEndian<float> feign_death_chance;
		Memory::BigEndian<float> feign_repeat_chance;
		TagDependency spawned_actor;
		Memory::BigEndian<std::int16_t> spawned_actor_count[2];
		Memory::BigEndian<float> spawned_velocity;
		Angle aiming_velocity_maximum;
		Angle aiming_acceleration_maximum;
		Fraction casual_aiming_modifier;
		Angle looking_velocity_maximum;
		Angle looking_acceleration_maximum;
		PADDING(8);
		Memory::BigEndian<float> ai_vehicle_radius;
		Memory::BigEndian<float> ai_danger_radius;
		TagDependency melee_damage;
		Memory::BigEndian<UnitMotionSensorBlipSize> motion_sensor_blip_size;
		PADDING(2);
		Memory::BigEndian<MetagameType> metagame_type;
		Memory::BigEndian<MetagameClass> metagame_class;
		PADDING(8);
		TagReflexive<UnitUnitHudInterface> new_hud_interfaces;
		TagReflexive<UnitDialogueVariant> dialogue_variants;
		Memory::BigEndian<float> grenade_velocity;
		Memory::BigEndian<GrenadeType> grenade_type;
		Memory::BigEndian<std::int16_t> grenade_count;
		Memory::BigEndian<std::int16_t> soft_ping_interrupt_ticks;
		Memory::BigEndian<std::int16_t> hard_ping_interrupt_ticks;
		TagReflexive<UnitPoweredSeat> powered_seats;
		TagReflexive<UnitWeapon> weapons;
		TagReflexive<UnitSeat> seats;
	};
	static_assert(sizeof(Unit) == 752);

}

#endif

