// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__GLOBALS_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__GLOBALS_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
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
		Memory::BigEndian<float> scale;
	};
	static_assert(sizeof(GlobalsLookFunction) == 4);

	struct GlobalsPlayerControl {
		Memory::BigEndian<float> magnetism_friction;
		Memory::BigEndian<float> magnetism_adhesion;
		Memory::BigEndian<float> inconsequential_target_scale;
		PADDING(52);
		Memory::BigEndian<float> look_acceleration_time;
		Memory::BigEndian<float> look_acceleration_scale;
		Memory::BigEndian<float> look_peg_threshold;
		Memory::BigEndian<float> look_default_pitch_rate;
		Memory::BigEndian<float> look_default_yaw_rate;
		Memory::BigEndian<float> look_autolevelling_scale;
		PADDING(20);
		Memory::BigEndian<std::int16_t> minimum_weapon_swap_ticks;
		Memory::BigEndian<std::int16_t> minimum_autolevelling_ticks;
		Angle minimum_angle_for_vehicle_flipping;
		TagReflexive<GlobalsLookFunction> look_function;
	};
	static_assert(sizeof(GlobalsPlayerControl) == 128);

	struct GlobalsDifficulty {
		Memory::BigEndian<float> easy_enemy_damage;
		Memory::BigEndian<float> normal_enemy_damage;
		Memory::BigEndian<float> hard_enemy_damage;
		Memory::BigEndian<float> imposs_enemy_damage;
		Memory::BigEndian<float> easy_enemy_vitality;
		Memory::BigEndian<float> normal_enemy_vitality;
		Memory::BigEndian<float> hard_enemy_vitality;
		Memory::BigEndian<float> imposs_enemy_vitality;
		Memory::BigEndian<float> easy_enemy_shield;
		Memory::BigEndian<float> normal_enemy_shield;
		Memory::BigEndian<float> hard_enemy_shield;
		Memory::BigEndian<float> imposs_enemy_shield;
		Memory::BigEndian<float> easy_enemy_recharge;
		Memory::BigEndian<float> normal_enemy_recharge;
		Memory::BigEndian<float> hard_enemy_recharge;
		Memory::BigEndian<float> imposs_enemy_recharge;
		Memory::BigEndian<float> easy_friend_damage;
		Memory::BigEndian<float> normal_friend_damage;
		Memory::BigEndian<float> hard_friend_damage;
		Memory::BigEndian<float> imposs_friend_damage;
		Memory::BigEndian<float> easy_friend_vitality;
		Memory::BigEndian<float> normal_friend_vitality;
		Memory::BigEndian<float> hard_friend_vitality;
		Memory::BigEndian<float> imposs_friend_vitality;
		Memory::BigEndian<float> easy_friend_shield;
		Memory::BigEndian<float> normal_friend_shield;
		Memory::BigEndian<float> hard_friend_shield;
		Memory::BigEndian<float> imposs_friend_shield;
		Memory::BigEndian<float> easy_friend_recharge;
		Memory::BigEndian<float> normal_friend_recharge;
		Memory::BigEndian<float> hard_friend_recharge;
		Memory::BigEndian<float> imposs_friend_recharge;
		Memory::BigEndian<float> easy_infection_forms;
		Memory::BigEndian<float> normal_infection_forms;
		Memory::BigEndian<float> hard_infection_forms;
		Memory::BigEndian<float> imposs_infection_forms;
		PADDING(16);
		Memory::BigEndian<float> easy_rate_of_fire;
		Memory::BigEndian<float> normal_rate_of_fire;
		Memory::BigEndian<float> hard_rate_of_fire;
		Memory::BigEndian<float> imposs_rate_of_fire;
		Memory::BigEndian<float> easy_projectile_error;
		Memory::BigEndian<float> normal_projectile_error;
		Memory::BigEndian<float> hard_projectile_error;
		Memory::BigEndian<float> imposs_projectile_error;
		Memory::BigEndian<float> easy_burst_error;
		Memory::BigEndian<float> normal_burst_error;
		Memory::BigEndian<float> hard_burst_error;
		Memory::BigEndian<float> imposs_burst_error;
		Memory::BigEndian<float> easy_new_target_delay;
		Memory::BigEndian<float> normal_new_target_delay;
		Memory::BigEndian<float> hard_new_target_delay;
		Memory::BigEndian<float> imposs_new_target_delay;
		Memory::BigEndian<float> easy_burst_separation;
		Memory::BigEndian<float> normal_burst_separation;
		Memory::BigEndian<float> hard_burst_separation;
		Memory::BigEndian<float> imposs_burst_separation;
		Memory::BigEndian<float> easy_target_tracking;
		Memory::BigEndian<float> normal_target_tracking;
		Memory::BigEndian<float> hard_target_tracking;
		Memory::BigEndian<float> imposs_target_tracking;
		Memory::BigEndian<float> easy_target_leading;
		Memory::BigEndian<float> normal_target_leading;
		Memory::BigEndian<float> hard_target_leading;
		Memory::BigEndian<float> imposs_target_leading;
		Memory::BigEndian<float> easy_overcharge_chance;
		Memory::BigEndian<float> normal_overcharge_chance;
		Memory::BigEndian<float> hard_overcharge_chance;
		Memory::BigEndian<float> imposs_overcharge_chance;
		Memory::BigEndian<float> easy_special_fire_delay;
		Memory::BigEndian<float> normal_special_fire_delay;
		Memory::BigEndian<float> hard_special_fire_delay;
		Memory::BigEndian<float> imposs_special_fire_delay;
		Memory::BigEndian<float> easy_guidance_vs_player;
		Memory::BigEndian<float> normal_guidance_vs_player;
		Memory::BigEndian<float> hard_guidance_vs_player;
		Memory::BigEndian<float> imposs_guidance_vs_player;
		Memory::BigEndian<float> easy_melee_delay_base;
		Memory::BigEndian<float> normal_melee_delay_base;
		Memory::BigEndian<float> hard_melee_delay_base;
		Memory::BigEndian<float> imposs_melee_delay_base;
		Memory::BigEndian<float> easy_melee_delay_scale;
		Memory::BigEndian<float> normal_melee_delay_scale;
		Memory::BigEndian<float> hard_melee_delay_scale;
		Memory::BigEndian<float> imposs_melee_delay_scale;
		PADDING(16);
		Memory::BigEndian<float> easy_grenade_chance_scale;
		Memory::BigEndian<float> normal_grenade_chance_scale;
		Memory::BigEndian<float> hard_grenade_chance_scale;
		Memory::BigEndian<float> imposs_grenade_chance_scale;
		Memory::BigEndian<float> easy_grenade_timer_scale;
		Memory::BigEndian<float> normal_grenade_timer_scale;
		Memory::BigEndian<float> hard_grenade_timer_scale;
		Memory::BigEndian<float> imposs_grenade_timer_scale;
		PADDING(16);
		PADDING(16);
		PADDING(16);
		Memory::BigEndian<float> easy_major_upgrade;
		Memory::BigEndian<float> normal_major_upgrade;
		Memory::BigEndian<float> hard_major_upgrade;
		Memory::BigEndian<float> imposs_major_upgrade;
		Memory::BigEndian<float> easy_major_upgrade_1;
		Memory::BigEndian<float> normal_major_upgrade_1;
		Memory::BigEndian<float> hard_major_upgrade_1;
		Memory::BigEndian<float> imposs_major_upgrade_1;
		Memory::BigEndian<float> easy_major_upgrade_2;
		Memory::BigEndian<float> normal_major_upgrade_2;
		Memory::BigEndian<float> hard_major_upgrade_2;
		Memory::BigEndian<float> imposs_major_upgrade_2;
		PADDING(16);
		PADDING(16);
		PADDING(16);
		PADDING(16);
		PADDING(84);
	};
	static_assert(sizeof(GlobalsDifficulty) == 644);

	struct GlobalsGrenade {
		Memory::BigEndian<std::int16_t> maximum_count;
		Memory::BigEndian<std::int16_t> mp_spawn_default;
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
		Memory::BigEndian<GlobalsRasterizerDataFlags> flags;
		PADDING(2);
		Memory::BigEndian<float> refraction_amount;
		Memory::BigEndian<float> distance_falloff;
		ColorRGB tint_color;
		Memory::BigEndian<float> hyper_stealth_refraction;
		Memory::BigEndian<float> hyper_stealth_distance_falloff;
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
		Memory::BigEndian<float> walking_speed;
		Memory::BigEndian<float> double_speed_multiplier;
		Memory::BigEndian<float> run_forward;
		Memory::BigEndian<float> run_backward;
		Memory::BigEndian<float> run_sideways;
		Memory::BigEndian<float> run_acceleration;
		Memory::BigEndian<float> sneak_forward;
		Memory::BigEndian<float> sneak_backward;
		Memory::BigEndian<float> sneak_sideways;
		Memory::BigEndian<float> sneak_acceleration;
		Memory::BigEndian<float> airborne_acceleration;
		Memory::BigEndian<float> speed_multiplier;
		PADDING(12);
		Point3D grenade_origin;
		PADDING(12);
		Memory::BigEndian<float> stun_movement_penalty;
		Memory::BigEndian<float> stun_turning_penalty;
		Memory::BigEndian<float> stun_jumping_penalty;
		Memory::BigEndian<float> minimum_stun_time;
		Memory::BigEndian<float> maximum_stun_time;
		PADDING(8);
		Memory::BigEndian<float> first_person_idle_time[2];
		Memory::BigEndian<float> first_person_skip_fraction;
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
		Memory::BigEndian<float> harmful_falling_distance[2];
		TagDependency falling_damage;
		PADDING(8);
		Memory::BigEndian<float> maximum_falling_distance;
		TagDependency distance_damage;
		TagDependency vehicle_environment_collision_damage;
		TagDependency vehicle_killed_unit_damage;
		TagDependency vehicle_collision_damage;
		TagDependency flaming_death_damage;
		PADDING(16);
		Memory::BigEndian<float> maximum_falling_velocity;
		Memory::BigEndian<float> harmful_falling_velocity[2];
	};
	static_assert(sizeof(GlobalsFallingDamage) == 152);

	struct GlobalsBreakableSurfaceParticleEffect {
		TagDependency particle_type;
		Memory::BigEndian<GlobalsBreakableSurfaceParticleEffectFlags> flags;
		Memory::BigEndian<float> density;
		Memory::BigEndian<float> velocity_scale[2];
		PADDING(4);
		Memory::BigEndian<float> angular_velocity[2];
		PADDING(8);
		Memory::BigEndian<float> radius[2];
		PADDING(8);
		ColorARGB tint_lower_bound;
		ColorARGB tint_upper_bound;
		PADDING(28);
	};
	static_assert(sizeof(GlobalsBreakableSurfaceParticleEffect) == 128);

	struct GlobalsMaterial {
		PADDING(100);
		PADDING(48);
		Memory::BigEndian<float> ground_friction_scale;
		Memory::BigEndian<float> ground_friction_normal_k1_scale;
		Memory::BigEndian<float> ground_friction_normal_k0_scale;
		Memory::BigEndian<float> ground_depth_scale;
		Memory::BigEndian<float> ground_damp_fraction_scale;
		PADDING(76);
		PADDING(480);
		Memory::BigEndian<float> maximum_vitality;
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
		Memory::BigEndian<std::int32_t> minimum_experience;
		Memory::BigEndian<std::int32_t> maximum_experience;
		Memory::BigEndian<std::int32_t> minimum_player_count;
		Memory::BigEndian<std::int32_t> maximum_player_count;
		Memory::BigEndian<std::int32_t> rating;
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

