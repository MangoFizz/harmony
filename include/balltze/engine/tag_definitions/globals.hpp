// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__GLOBALS_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__GLOBALS_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class MultiplayerInformationSound : std::uint16_t {
		PLAY_BALL = 0,
		GAME_OVER,
		ONE_MINUTE_TO_WIN,
		_30_SECONDS_TO_WIN,
		RED_TEAM_MINUTE_TO_WIN,
		RED_TEAM_30_TO_WIN,
		BLUE_TEAM_MINUTE_TO_WIN,
		BLUE_TEAM_30_TO_WIN,
		BLUE_TEAM_HAS_THE_FLAG,
		BLUE_TEAM_FLAG_RETURNED,
		BLUE_TEAM_SCORE,
		RED_TEAM_HAS_THE_FLAG,
		RED_TEAM_FLAG_RETURNED,
		RED_TEAM_SCORE,
		DOUBLE_KILL,
		TRIPLE_KILL,
		KILLTACULAR,
		RUNNING_RIOT,
		KILLING_SPREE,
		ODDBALL,
		RACE,
		SLAYER,
		CAPTURE_THE_FLAG,
		WARTHOG,
		GHOST,
		SCORPION,
		COUNTDOWN_TIMER,
		TELEPORTER_ACTIVATE,
		FLAG_FAILURE,
		COUNTDOWN_FOR_RESPAWN,
		HILL_MOVE,
		PLAYER_RESPAWN,
		TEAM_KING_OF_THE_HILL,
		TEAM_ODDBALL,
		TEAM_RACE,
		TEAM_SLAYER,
		KING_OF_THE_HILL,
		BLUE_TEAM_CTF,
		RED_TEAM_CTF,
		HILL_CONTESTED,
		HILL_CONTROLLED,
		HILL_OCCUPIED,
		COUNTDOWN_TIMER_END,
		TING,
	};

	struct GlobalsRasterizerDataFlags {
		std::uint16_t tint_edge_density : 1;
	};
	static_assert(sizeof(GlobalsRasterizerDataFlags) == sizeof(std::uint16_t));

	struct GlobalsBreakableSurfaceParticleEffectFlags {
		std::uint32_t interpolate_color_in_hsv : 1;
		std::uint32_t more_colors : 1;
	};
	static_assert(sizeof(GlobalsBreakableSurfaceParticleEffectFlags) == sizeof(std::uint32_t));

	struct GlobalsSound {
		TagDependency sound;
	};
	static_assert(sizeof(GlobalsSound) == 16);

	struct GlobalsCamera {
		TagDependency default_unit_camera_track;
	};
	static_assert(sizeof(GlobalsCamera) == 16);

	struct GlobalsLookFunction {
		float scale;
	};
	static_assert(sizeof(GlobalsLookFunction) == 4);

	struct GlobalsPlayerControl {
		float magnetism_friction;
		float magnetism_adhesion;
		float inconsequential_target_scale;
		PADDING(52);
		float look_acceleration_time;
		float look_acceleration_scale;
		float look_peg_threshold;
		float look_default_pitch_rate;
		float look_default_yaw_rate;
		float look_autolevelling_scale;
		PADDING(20);
		std::int16_t minimum_weapon_swap_ticks;
		std::int16_t minimum_autolevelling_ticks;
		Angle minimum_angle_for_vehicle_flipping;
		TagReflexive<GlobalsLookFunction> look_function;
	};
	static_assert(sizeof(GlobalsPlayerControl) == 128);

	struct GlobalsDifficulty {
		float easy_enemy_damage;
		float normal_enemy_damage;
		float hard_enemy_damage;
		float imposs_enemy_damage;
		float easy_enemy_vitality;
		float normal_enemy_vitality;
		float hard_enemy_vitality;
		float imposs_enemy_vitality;
		float easy_enemy_shield;
		float normal_enemy_shield;
		float hard_enemy_shield;
		float imposs_enemy_shield;
		float easy_enemy_recharge;
		float normal_enemy_recharge;
		float hard_enemy_recharge;
		float imposs_enemy_recharge;
		float easy_friend_damage;
		float normal_friend_damage;
		float hard_friend_damage;
		float imposs_friend_damage;
		float easy_friend_vitality;
		float normal_friend_vitality;
		float hard_friend_vitality;
		float imposs_friend_vitality;
		float easy_friend_shield;
		float normal_friend_shield;
		float hard_friend_shield;
		float imposs_friend_shield;
		float easy_friend_recharge;
		float normal_friend_recharge;
		float hard_friend_recharge;
		float imposs_friend_recharge;
		float easy_infection_forms;
		float normal_infection_forms;
		float hard_infection_forms;
		float imposs_infection_forms;
		PADDING(16);
		float easy_rate_of_fire;
		float normal_rate_of_fire;
		float hard_rate_of_fire;
		float imposs_rate_of_fire;
		float easy_projectile_error;
		float normal_projectile_error;
		float hard_projectile_error;
		float imposs_projectile_error;
		float easy_burst_error;
		float normal_burst_error;
		float hard_burst_error;
		float imposs_burst_error;
		float easy_new_target_delay;
		float normal_new_target_delay;
		float hard_new_target_delay;
		float imposs_new_target_delay;
		float easy_burst_separation;
		float normal_burst_separation;
		float hard_burst_separation;
		float imposs_burst_separation;
		float easy_target_tracking;
		float normal_target_tracking;
		float hard_target_tracking;
		float imposs_target_tracking;
		float easy_target_leading;
		float normal_target_leading;
		float hard_target_leading;
		float imposs_target_leading;
		float easy_overcharge_chance;
		float normal_overcharge_chance;
		float hard_overcharge_chance;
		float imposs_overcharge_chance;
		float easy_special_fire_delay;
		float normal_special_fire_delay;
		float hard_special_fire_delay;
		float imposs_special_fire_delay;
		float easy_guidance_vs_player;
		float normal_guidance_vs_player;
		float hard_guidance_vs_player;
		float imposs_guidance_vs_player;
		float easy_melee_delay_base;
		float normal_melee_delay_base;
		float hard_melee_delay_base;
		float imposs_melee_delay_base;
		float easy_melee_delay_scale;
		float normal_melee_delay_scale;
		float hard_melee_delay_scale;
		float imposs_melee_delay_scale;
		PADDING(16);
		float easy_grenade_chance_scale;
		float normal_grenade_chance_scale;
		float hard_grenade_chance_scale;
		float imposs_grenade_chance_scale;
		float easy_grenade_timer_scale;
		float normal_grenade_timer_scale;
		float hard_grenade_timer_scale;
		float imposs_grenade_timer_scale;
		PADDING(16);
		PADDING(16);
		PADDING(16);
		float easy_major_upgrade;
		float normal_major_upgrade;
		float hard_major_upgrade;
		float imposs_major_upgrade;
		float easy_major_upgrade_1;
		float normal_major_upgrade_1;
		float hard_major_upgrade_1;
		float imposs_major_upgrade_1;
		float easy_major_upgrade_2;
		float normal_major_upgrade_2;
		float hard_major_upgrade_2;
		float imposs_major_upgrade_2;
		PADDING(16);
		PADDING(16);
		PADDING(16);
		PADDING(16);
		PADDING(84);
	};
	static_assert(sizeof(GlobalsDifficulty) == 644);

	struct GlobalsGrenade {
		std::int16_t maximum_count;
		std::int16_t mp_spawn_default;
		TagDependency throwing_effect;
		TagDependency hud_interface;
		TagDependency equipment;
		TagDependency projectile;
	};
	static_assert(sizeof(GlobalsGrenade) == 68);

	struct GlobalsRasterizerData {
		TagDependency distance_attenuation;
		TagDependency vector_normalization;
		TagDependency atmospheric_fog_density;
		TagDependency planar_fog_density;
		TagDependency linear_corner_fade;
		TagDependency active_camouflage_distortion;
		TagDependency glow;
		PADDING(60);
		TagDependency default_2d;
		TagDependency default_3d;
		TagDependency default_cube_map;
		TagDependency test_0;
		TagDependency test_1;
		TagDependency test_2;
		TagDependency test_3;
		TagDependency video_scanline_map;
		TagDependency video_noise_map;
		PADDING(52);
		GlobalsRasterizerDataFlags flags;
		PADDING(2);
		float refraction_amount;
		float distance_falloff;
		ColorRGB tint_color;
		float hyper_stealth_refraction;
		float hyper_stealth_distance_falloff;
		ColorRGB hyper_stealth_tint_color;
		TagDependency distance_attenuation_2d;
	};
	static_assert(sizeof(GlobalsRasterizerData) == 428);

	struct GlobalsInterfaceBitmaps {
		TagDependency font_system;
		TagDependency font_terminal;
		TagDependency screen_color_table;
		TagDependency hud_color_table;
		TagDependency editor_color_table;
		TagDependency dialog_color_table;
		TagDependency hud_globals;
		TagDependency motion_sensor_sweep_bitmap;
		TagDependency motion_sensor_sweep_bitmap_mask;
		TagDependency multiplayer_hud_bitmap;
		TagDependency localization;
		TagDependency hud_digits_definition;
		TagDependency motion_sensor_blip_bitmap;
		TagDependency interface_goo_map1;
		TagDependency interface_goo_map2;
		TagDependency interface_goo_map3;
		PADDING(48);
	};
	static_assert(sizeof(GlobalsInterfaceBitmaps) == 304);

	struct GlobalsWeapon {
		TagDependency weapon;
	};
	static_assert(sizeof(GlobalsWeapon) == 16);

	struct GlobalsCheatPowerup {
		TagDependency powerup;
	};
	static_assert(sizeof(GlobalsCheatPowerup) == 16);

	struct GlobalsVehicle {
		TagDependency vehicle;
	};
	static_assert(sizeof(GlobalsVehicle) == 16);

	struct GlobalsMultiplayerInformation {
		TagDependency flag;
		TagDependency unit;
		TagReflexive<GlobalsVehicle> vehicles;
		TagDependency hill_shader;
		TagDependency flag_shader;
		TagDependency ball;
		TagReflexive<GlobalsSound> sounds;
		PADDING(56);
	};
	static_assert(sizeof(GlobalsMultiplayerInformation) == 160);

	struct GlobalsPlayerInformation {
		TagDependency unit;
		PADDING(28);
		float walking_speed;
		float double_speed_multiplier;
		float run_forward;
		float run_backward;
		float run_sideways;
		float run_acceleration;
		float sneak_forward;
		float sneak_backward;
		float sneak_sideways;
		float sneak_acceleration;
		float airborne_acceleration;
		float speed_multiplier;
		PADDING(12);
		Point3D grenade_origin;
		PADDING(12);
		float stun_movement_penalty;
		float stun_turning_penalty;
		float stun_jumping_penalty;
		float minimum_stun_time;
		float maximum_stun_time;
		PADDING(8);
		float first_person_idle_time[2];
		float first_person_skip_fraction;
		PADDING(16);
		TagDependency coop_respawn_effect;
		PADDING(44);
	};
	static_assert(sizeof(GlobalsPlayerInformation) == 244);

	struct GlobalsFirstPersonInterface {
		TagDependency first_person_hands;
		TagDependency base_bitmap;
		TagDependency shield_meter;
		Point2DInt shield_meter_origin;
		TagDependency body_meter;
		Point2DInt body_meter_origin;
		TagDependency night_vision_on_effect;
		TagDependency night_vision_off_effect;
		PADDING(88);
	};
	static_assert(sizeof(GlobalsFirstPersonInterface) == 192);

	struct GlobalsFallingDamage {
		PADDING(8);
		float harmful_falling_distance[2];
		TagDependency falling_damage;
		PADDING(8);
		float maximum_falling_distance;
		TagDependency distance_damage;
		TagDependency vehicle_environment_collision_damage;
		TagDependency vehicle_killed_unit_damage;
		TagDependency vehicle_collision_damage;
		TagDependency flaming_death_damage;
		PADDING(16);
		float maximum_falling_velocity;
		float harmful_falling_velocity[2];
	};
	static_assert(sizeof(GlobalsFallingDamage) == 152);

	struct GlobalsBreakableSurfaceParticleEffect {
		TagDependency particle_type;
		GlobalsBreakableSurfaceParticleEffectFlags flags;
		float density;
		float velocity_scale[2];
		PADDING(4);
		float angular_velocity[2];
		PADDING(8);
		float radius[2];
		PADDING(8);
		ColorARGB tint_lower_bound;
		ColorARGB tint_upper_bound;
		PADDING(28);
	};
	static_assert(sizeof(GlobalsBreakableSurfaceParticleEffect) == 128);

	struct GlobalsMaterial {
		PADDING(100);
		PADDING(48);
		float ground_friction_scale;
		float ground_friction_normal_k1_scale;
		float ground_friction_normal_k0_scale;
		float ground_depth_scale;
		float ground_damp_fraction_scale;
		PADDING(76);
		PADDING(480);
		float maximum_vitality;
		PADDING(8);
		PADDING(4);
		TagDependency effect;
		TagDependency sound;
		PADDING(24);
		TagReflexive<GlobalsBreakableSurfaceParticleEffect> particle_effects;
		PADDING(60);
		TagDependency melee_hit_sound;
	};
	static_assert(sizeof(GlobalsMaterial) == 884);

	struct GlobalsPlaylistMember {
		TagString map_name;
		TagString game_variant;
		std::int32_t minimum_experience;
		std::int32_t maximum_experience;
		std::int32_t minimum_player_count;
		std::int32_t maximum_player_count;
		std::int32_t rating;
		PADDING(64);
	};
	static_assert(sizeof(GlobalsPlaylistMember) == 148);

	struct Globals {
		PADDING(248);
		TagReflexive<GlobalsSound> sounds;
		TagReflexive<GlobalsCamera> camera;
		TagReflexive<GlobalsPlayerControl> player_control;
		TagReflexive<GlobalsDifficulty> difficulty;
		TagReflexive<GlobalsGrenade> grenades;
		TagReflexive<GlobalsRasterizerData> rasterizer_data;
		TagReflexive<GlobalsInterfaceBitmaps> interface_bitmaps;
		TagReflexive<GlobalsWeapon> weapon_list;
		TagReflexive<GlobalsCheatPowerup> cheat_powerups;
		TagReflexive<GlobalsMultiplayerInformation> multiplayer_information;
		TagReflexive<GlobalsPlayerInformation> player_information;
		TagReflexive<GlobalsFirstPersonInterface> first_person_interface;
		TagReflexive<GlobalsFallingDamage> falling_damage;
		TagReflexive<GlobalsMaterial> materials;
		TagReflexive<GlobalsPlaylistMember> playlist_members;
	};
	static_assert(sizeof(Globals) == 428);

}

#endif

