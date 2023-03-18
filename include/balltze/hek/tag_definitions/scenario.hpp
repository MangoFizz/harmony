// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__SCENARIO_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__SCENARIO_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "actor.hpp"
#include "object.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class ScenarioType : std::uint16_t {
		SINGLEPLAYER = 0,
		MULTIPLAYER,
		USER_INTERFACE,
	};

	enum class ScenarioSpawnType : std::uint16_t {
		NONE = 0,
		CTF,
		SLAYER,
		ODDBALL,
		KING_OF_THE_HILL,
		RACE,
		TERMINATOR,
		STUB,
		IGNORED1,
		IGNORED2,
		IGNORED3,
		IGNORED4,
		ALL_GAMES,
		ALL_EXCEPT_CTF,
		ALL_EXCEPT_RACE_AND_CTF,
	};

	enum class ScenarioNetgameFlagType : std::uint16_t {
		CTF_FLAG = 0,
		CTF_VEHICLE,
		ODDBALL_BALL_SPAWN,
		RACE_TRACK,
		RACE_VEHICLE,
		VEGAS_BANK,
		TELEPORT_FROM,
		TELEPORT_TO,
		HILL_FLAG,
	};

	enum class ScenarioReturnState : std::uint16_t {
		NONE = 0,
		SLEEPING,
		ALERT,
		MOVING_REPEAT_SAME_POSITION,
		MOVING_LOOP,
		MOVING_LOOP_BACK_AND_FORTH,
		MOVING_LOOP_RANDOMLY,
		MOVING_RANDOMLY,
		GUARDING,
		GUARDING_AT_GUARD_POSITION,
		SEARCHING,
		FLEEING,
	};

	enum class ScenarioUniqueLeaderType : std::uint16_t {
		NORMAL = 0,
		NONE,
		RANDOM,
		SGT_JOHNSON,
		SGT_LEHTO,
	};

	enum class ScenarioMajorUpgrade : std::uint16_t {
		NORMAL = 0,
		FEW,
		MANY,
		NONE,
		ALL,
	};

	enum class ScenarioChangeAttackingDefendingStateWhen : std::uint16_t {
		NEVER = 0,
		_75_STRENGTH,
		_50_STRENGTH,
		_25_STRENGTH,
		ANYBODY_DEAD,
		_25_DEAD,
		_50_DEAD,
		_75_DEAD,
		ALL_BUT_ONE_DEAD,
		ALL_DEAD,
	};

	enum class ScenarioGroupIndex : std::uint16_t {
		A = 0,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
	};

	enum class ScenarioTeamIndex : std::uint16_t {
		DEFAULT_BY_UNIT = 0,
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

	enum class ScenarioSearchBehavior : std::uint16_t {
		NORMAL = 0,
		NEVER,
		TENACIOUS,
	};

	enum class ScenarioAtomType : std::uint16_t {
		PAUSE = 0,
		GO_TO,
		GO_TO_AND_FACE,
		MOVE_IN_DIRECTION,
		LOOK,
		ANIMATION_MODE,
		CROUCH,
		SHOOT,
		GRENADE,
		VEHICLE,
		RUNNING_JUMP,
		TARGETED_JUMP,
		SCRIPT,
		ANIMATE,
		RECORDING,
		ACTION,
		VOCALIZE,
		TARGETING,
		INITIATIVE,
		WAIT,
		LOOP,
		DIE,
		MOVE_IMMEDIATE,
		LOOK_RANDOM,
		LOOK_PLAYER,
		LOOK_OBJECT,
		SET_RADIUS,
		TELEPORT,
	};

	enum class ScenarioSelectionType : std::uint16_t {
		FRIENDLY_ACTOR = 0,
		DISEMBODIED,
		IN_PLAYER_S_VEHICLE,
		NOT_IN_A_VEHICLE,
		PREFER_SERGEANT,
		ANY_ACTOR,
		RADIO_UNIT,
		RADIO_SERGEANT,
	};

	enum class ScenarioAddressee : std::uint16_t {
		NONE = 0,
		PLAYER,
		PARTICIPANT,
	};

	enum class ScenarioScriptType : std::uint16_t {
		STARTUP = 0,
		DORMANT,
		CONTINUOUS,
		STATIC,
		STUB,
	};

	enum class ScenarioScriptValueType : std::uint16_t {
		UNPARSED = 0,
		SPECIAL_FORM,
		FUNCTION_NAME,
		PASSTHROUGH_VALUE,
		VOID_VALUE,
		BOOLEAN,
		REAL,
		SHORT,
		LONG,
		STRING,
		SCRIPT,
		TRIGGER_VOLUME,
		CUTSCENE_FLAG,
		CUTSCENE_CAMERA_POINT,
		CUTSCENE_TITLE,
		CUTSCENE_RECORDING,
		DEVICE_GROUP,
		AI,
		AI_COMMAND_LIST,
		STARTING_PROFILE,
		CONVERSATION,
		NAVPOINT,
		HUD_MESSAGE,
		OBJECT_LIST,
		SOUND,
		EFFECT,
		DAMAGE,
		LOOPING_SOUND,
		ANIMATION_GRAPH,
		ACTOR_VARIANT,
		DAMAGE_EFFECT,
		OBJECT_DEFINITION,
		GAME_DIFFICULTY,
		TEAM,
		AI_DEFAULT_STATE,
		ACTOR_TYPE,
		HUD_CORNER,
		OBJECT,
		UNIT,
		VEHICLE,
		WEAPON,
		DEVICE,
		SCENERY,
		OBJECT_NAME,
		UNIT_NAME,
		VEHICLE_NAME,
		WEAPON_NAME,
		DEVICE_NAME,
		SCENERY_NAME,
	};

	enum class ScenarioTextStyle : std::uint16_t {
		PLAIN = 0,
		BOLD,
		ITALIC,
		CONDENSE,
		UNDERLINE,
	};

	enum class ScenarioJustification : std::uint16_t {
		LEFT = 0,
		RIGHT,
		CENTER,
	};

	struct ScenarioTextFlags {
		std::uint32_t wrap_horizontally : 1;
		std::uint32_t wrap_vertically : 1;
		std::uint32_t center_vertically : 1;
		std::uint32_t bottom_justify : 1;
	};
	static_assert(sizeof(ScenarioTextFlags) == sizeof(std::uint32_t));

	struct ScenarioFunctionFlags {
		std::uint32_t scripted : 1;
		std::uint32_t invert : 1;
		std::uint32_t additive : 1;
		std::uint32_t always_active : 1;
	};
	static_assert(sizeof(ScenarioFunctionFlags) == sizeof(std::uint32_t));

	struct ScenarioSpawnNotPlaced {
		std::uint16_t automatically : 1;
		std::uint16_t on_easy : 1;
		std::uint16_t on_normal : 1;
		std::uint16_t on_hard : 1;
		std::uint16_t use_player_appearance : 1;
	};
	static_assert(sizeof(ScenarioSpawnNotPlaced) == sizeof(std::uint16_t));

	struct ScenarioUnitFlags {
		std::uint32_t dead : 1;
	};
	static_assert(sizeof(ScenarioUnitFlags) == sizeof(std::uint32_t));

	struct ScenarioVehicleMultiplayerSpawnFlags {
		std::uint16_t slayer_default : 1;
		std::uint16_t ctf_default : 1;
		std::uint16_t king_default : 1;
		std::uint16_t oddball_default : 1;
		std::uint16_t unused : 1;
		std::uint16_t unused1 : 1;
		std::uint16_t unused2 : 1;
		std::uint16_t unused3 : 1;
		std::uint16_t slayer_allowed : 1;
		std::uint16_t ctf_allowed : 1;
		std::uint16_t king_allowed : 1;
		std::uint16_t oddball_allowed : 1;
		std::uint16_t unused4 : 1;
		std::uint16_t unused5 : 1;
		std::uint16_t unused6 : 1;
		std::uint16_t unused7 : 1;
	};
	static_assert(sizeof(ScenarioVehicleMultiplayerSpawnFlags) == sizeof(std::uint16_t));

	struct ScenarioItemFlags {
		std::uint16_t initially_at_rest : 1;
		std::uint16_t obsolete : 1;
		std::uint16_t does_accelerate : 1;
	};
	static_assert(sizeof(ScenarioItemFlags) == sizeof(std::uint16_t));

	struct ScenarioDeviceGroupFlags {
		std::uint32_t can_change_only_once : 1;
	};
	static_assert(sizeof(ScenarioDeviceGroupFlags) == sizeof(std::uint32_t));

	struct ScenarioDeviceFlags {
		std::uint32_t initially_open : 1;
		std::uint32_t initially_off : 1;
		std::uint32_t can_change_only_once : 1;
		std::uint32_t position_reversed : 1;
		std::uint32_t not_usable_from_any_side : 1;
	};
	static_assert(sizeof(ScenarioDeviceFlags) == sizeof(std::uint32_t));

	struct ScenarioMachineFlags {
		std::uint32_t does_not_operate_automatically : 1;
		std::uint32_t one_sided : 1;
		std::uint32_t never_appears_locked : 1;
		std::uint32_t opened_by_melee_attack : 1;
	};
	static_assert(sizeof(ScenarioMachineFlags) == sizeof(std::uint32_t));

	struct ScenarioControlFlags {
		std::uint32_t usable_from_both_sides : 1;
	};
	static_assert(sizeof(ScenarioControlFlags) == sizeof(std::uint32_t));

	struct ScenarioNetgameEquipmentFlags {
		std::uint32_t levitate : 1;
	};
	static_assert(sizeof(ScenarioNetgameEquipmentFlags) == sizeof(std::uint32_t));

	struct ScenarioStartingEquipmentFlags {
		std::uint32_t no_grenades : 1;
		std::uint32_t plasma_grenades_only : 1;
		std::uint32_t type2_grenades_only : 1;
		std::uint32_t type3_grenades_only : 1;
	};
	static_assert(sizeof(ScenarioStartingEquipmentFlags) == sizeof(std::uint32_t));

	struct ScenarioActorStartingLocationFlags {
		std::uint8_t required : 1;
	};
	static_assert(sizeof(ScenarioActorStartingLocationFlags) == sizeof(std::uint8_t));

	struct ScenarioSquadFlags {
		std::uint32_t unused : 1;
		std::uint32_t never_search : 1;
		std::uint32_t start_timer_immediately : 1;
		std::uint32_t no_timer_delay_forever : 1;
		std::uint32_t magic_sight_after_timer : 1;
		std::uint32_t automatic_migration : 1;
	};
	static_assert(sizeof(ScenarioSquadFlags) == sizeof(std::uint32_t));

	struct ScenarioSquadAttacking {
		std::uint32_t a : 1;
		std::uint32_t b : 1;
		std::uint32_t c : 1;
		std::uint32_t d : 1;
		std::uint32_t e : 1;
		std::uint32_t f : 1;
		std::uint32_t g : 1;
		std::uint32_t h : 1;
		std::uint32_t i : 1;
		std::uint32_t j : 1;
		std::uint32_t k : 1;
		std::uint32_t l : 1;
		std::uint32_t m : 1;
		std::uint32_t n : 1;
		std::uint32_t o : 1;
		std::uint32_t p : 1;
		std::uint32_t q : 1;
		std::uint32_t r : 1;
		std::uint32_t s : 1;
		std::uint32_t t : 1;
		std::uint32_t u : 1;
		std::uint32_t v : 1;
		std::uint32_t w : 1;
		std::uint32_t x : 1;
		std::uint32_t y : 1;
		std::uint32_t z : 1;
	};
	static_assert(sizeof(ScenarioSquadAttacking) == sizeof(std::uint32_t));

	struct ScenarioPlatoonFlags {
		std::uint32_t flee_when_maneuvering : 1;
		std::uint32_t say_advancing_when_maneuver : 1;
		std::uint32_t start_in_defending_state : 1;
	};
	static_assert(sizeof(ScenarioPlatoonFlags) == sizeof(std::uint32_t));

	struct ScenarioEncounterFlags {
		std::uint32_t not_initially_created : 1;
		std::uint32_t respawn_enabled : 1;
		std::uint32_t initially_blind : 1;
		std::uint32_t initially_deaf : 1;
		std::uint32_t initially_braindead : 1;
		std::uint32_t _3d_firing_positions : 1;
		std::uint32_t manual_bsp_index_specified : 1;
	};
	static_assert(sizeof(ScenarioEncounterFlags) == sizeof(std::uint32_t));

	struct ScenarioCommandListFlags {
		std::uint32_t allow_initiative : 1;
		std::uint32_t allow_targeting : 1;
		std::uint32_t disable_looking : 1;
		std::uint32_t disable_communication : 1;
		std::uint32_t disable_falling_damage : 1;
		std::uint32_t manual_bsp_index : 1;
	};
	static_assert(sizeof(ScenarioCommandListFlags) == sizeof(std::uint32_t));

	struct ScenarioAIConversationParticipantFlags {
		std::uint16_t optional : 1;
		std::uint16_t has_alternate : 1;
		std::uint16_t is_alternate : 1;
	};
	static_assert(sizeof(ScenarioAIConversationParticipantFlags) == sizeof(std::uint16_t));

	struct ScenarioAIConversationLineFlags {
		std::uint16_t addressee_look_at_speaker : 1;
		std::uint16_t everyone_look_at_speaker : 1;
		std::uint16_t everyone_look_at_addressee : 1;
		std::uint16_t wait_after_until_told_to_advance : 1;
		std::uint16_t wait_until_speaker_nearby : 1;
		std::uint16_t wait_until_everyone_nearby : 1;
	};
	static_assert(sizeof(ScenarioAIConversationLineFlags) == sizeof(std::uint16_t));

	struct ScenarioAIConversationFlags {
		std::uint16_t stop_if_death : 1;
		std::uint16_t stop_if_damaged : 1;
		std::uint16_t stop_if_visible_enemy : 1;
		std::uint16_t stop_if_alerted_to_enemy : 1;
		std::uint16_t player_must_be_visible : 1;
		std::uint16_t stop_other_actions : 1;
		std::uint16_t keep_trying_to_play : 1;
		std::uint16_t player_must_be_looking : 1;
	};
	static_assert(sizeof(ScenarioAIConversationFlags) == sizeof(std::uint16_t));

	struct ScenarioFlags {
		std::uint16_t cortana_hack : 1;
		std::uint16_t use_demo_ui : 1;
		std::uint16_t color_correction_ntsc_to_srgb : 1;
		std::uint16_t do_not_apply_bungie_campaign_tag_patches : 1;
	};
	static_assert(sizeof(ScenarioFlags) == sizeof(std::uint16_t));

	struct ScenarioScriptNodeFlags {
		std::uint16_t is_primitive : 1;
		std::uint16_t is_script_call : 1;
		std::uint16_t is_global : 1;
		std::uint16_t is_garbage_collectable : 1;
		std::uint16_t is_local_variable : 1;
	};
	static_assert(sizeof(ScenarioScriptNodeFlags) == sizeof(std::uint16_t));

	struct ScenarioSky {
		TagDependency sky;
	};
	static_assert(sizeof(ScenarioSky) == 16);

	struct ScenarioChildScenario {
		TagDependency child_scenario;
		PADDING(16);
	};
	static_assert(sizeof(ScenarioChildScenario) == 32);

	struct ScenarioFunction {
		Memory::BigEndian<ScenarioFunctionFlags> flags;
		TagString name;
		Memory::BigEndian<float> period;
		Index scale_period_by;
		Memory::BigEndian<WaveFunction> function;
		Index scale_function_by;
		Memory::BigEndian<WaveFunction> wobble_function;
		Memory::BigEndian<float> wobble_period;
		Memory::BigEndian<float> wobble_magnitude;
		Fraction square_wave_threshold;
		Memory::BigEndian<std::int16_t> step_count;
		Memory::BigEndian<FunctionType> map_to;
		Memory::BigEndian<std::int16_t> sawtooth_count;
		PADDING(2);
		Index scale_result_by;
		Memory::BigEndian<FunctionBoundsMode> bounds_mode;
		Memory::BigEndian<float> bounds[2];
		PADDING(4);
		PADDING(2);
		Index turn_off_with;
		PADDING(16);
		PADDING(16);
	};
	static_assert(sizeof(ScenarioFunction) == 120);

	struct ScenarioEditorComment {
		Point3D position;
		PADDING(16);
		TagDataOffset comment;
	};
	static_assert(sizeof(ScenarioEditorComment) == 48);

	struct ScenarioScavengerHuntObjects {
		TagString name;
		Index object_name_index;
		PADDING(2);
	};
	static_assert(sizeof(ScenarioScavengerHuntObjects) == 36);

	struct ScenarioObjectName {
		TagString name;
		Memory::BigEndian<ObjectType> object_type;
		Index object_index;
	};
	static_assert(sizeof(ScenarioObjectName) == 36);

	struct ScenarioScenery {
		Index type;
		Index name;
		Memory::BigEndian<ScenarioSpawnNotPlaced> not_placed;
		Memory::BigEndian<std::int16_t> desired_permutation;
		Point3D position;
		Euler3D rotation;
		Memory::BigEndian<std::uint16_t> bsp_indices;
		PADDING(2);
		Memory::BigEndian<std::int8_t> appearance_player_index;
		PADDING(3);
		PADDING(16);
		PADDING(8);
		PADDING(8);
	};
	static_assert(sizeof(ScenarioScenery) == 72);

	struct ScenarioSceneryPalette {
		TagDependency name;
		PADDING(32);
	};
	static_assert(sizeof(ScenarioSceneryPalette) == 48);

	struct ScenarioBiped {
		Index type;
		Index name;
		Memory::BigEndian<ScenarioSpawnNotPlaced> not_placed;
		Memory::BigEndian<std::int16_t> desired_permutation;
		Point3D position;
		Euler3D rotation;
		PADDING(4);
		Memory::BigEndian<std::int8_t> appearance_player_index;
		PADDING(3);
		PADDING(16);
		PADDING(8);
		PADDING(8);
		Memory::BigEndian<float> body_vitality_modifier;
		Memory::BigEndian<ScenarioUnitFlags> flags;
		PADDING(8);
		PADDING(32);
	};
	static_assert(sizeof(ScenarioBiped) == 120);

	struct ScenarioBipedPalette {
		TagDependency name;
		PADDING(32);
	};
	static_assert(sizeof(ScenarioBipedPalette) == 48);

	struct ScenarioVehicle {
		Index type;
		Index name;
		Memory::BigEndian<ScenarioSpawnNotPlaced> not_placed;
		Memory::BigEndian<std::int16_t> desired_permutation;
		Point3D position;
		Euler3D rotation;
		PADDING(4);
		Memory::BigEndian<std::int8_t> appearance_player_index;
		PADDING(3);
		PADDING(16);
		PADDING(8);
		PADDING(8);
		Memory::BigEndian<float> body_vitality;
		Memory::BigEndian<ScenarioUnitFlags> flags;
		PADDING(8);
		Memory::BigEndian<std::int8_t> multiplayer_team_index;
		PADDING(1);
		Memory::BigEndian<ScenarioVehicleMultiplayerSpawnFlags> multiplayer_spawn_flags;
		PADDING(28);
	};
	static_assert(sizeof(ScenarioVehicle) == 120);

	struct ScenarioVehiclePalette {
		TagDependency name;
		PADDING(32);
	};
	static_assert(sizeof(ScenarioVehiclePalette) == 48);

	struct ScenarioEquipment {
		Index type;
		Index name;
		Memory::BigEndian<ScenarioSpawnNotPlaced> not_placed;
		Memory::BigEndian<std::int16_t> desired_permutation;
		Point3D position;
		Euler3D rotation;
		PADDING(2);
		Memory::BigEndian<ScenarioItemFlags> misc_flags;
		Memory::BigEndian<std::int8_t> appearance_player_index;
		PADDING(3);
	};
	static_assert(sizeof(ScenarioEquipment) == 40);

	struct ScenarioEquipmentPalette {
		TagDependency name;
		PADDING(32);
	};
	static_assert(sizeof(ScenarioEquipmentPalette) == 48);

	struct ScenarioWeapon {
		Index type;
		Index name;
		Memory::BigEndian<ScenarioSpawnNotPlaced> not_placed;
		Memory::BigEndian<std::int16_t> desired_permutation;
		Point3D position;
		Euler3D rotation;
		PADDING(4);
		Memory::BigEndian<std::int8_t> appearance_player_index;
		PADDING(3);
		PADDING(16);
		PADDING(8);
		PADDING(8);
		Memory::BigEndian<std::int16_t> rounds_reserved;
		Memory::BigEndian<std::int16_t> rounds_loaded;
		Memory::BigEndian<ScenarioItemFlags> flags;
		PADDING(2);
		PADDING(12);
	};
	static_assert(sizeof(ScenarioWeapon) == 92);

	struct ScenarioWeaponPalette {
		TagDependency name;
		PADDING(32);
	};
	static_assert(sizeof(ScenarioWeaponPalette) == 48);

	struct ScenarioDeviceGroup {
		TagString name;
		Memory::BigEndian<float> initial_value;
		Memory::BigEndian<ScenarioDeviceGroupFlags> flags;
		PADDING(12);
	};
	static_assert(sizeof(ScenarioDeviceGroup) == 52);

	struct ScenarioMachine {
		Index type;
		Index name;
		Memory::BigEndian<ScenarioSpawnNotPlaced> not_placed;
		Memory::BigEndian<std::int16_t> desired_permutation;
		Point3D position;
		Euler3D rotation;
		PADDING(4);
		Memory::BigEndian<std::int8_t> appearance_player_index;
		PADDING(3);
		Index power_group;
		Index position_group;
		Memory::BigEndian<ScenarioDeviceFlags> device_flags;
		Memory::BigEndian<ScenarioMachineFlags> machine_flags;
		PADDING(12);
	};
	static_assert(sizeof(ScenarioMachine) == 64);

	struct ScenarioMachinePalette {
		TagDependency name;
		PADDING(32);
	};
	static_assert(sizeof(ScenarioMachinePalette) == 48);

	struct ScenarioControl {
		Index type;
		Index name;
		Memory::BigEndian<ScenarioSpawnNotPlaced> not_placed;
		Memory::BigEndian<std::int16_t> desired_permutation;
		Point3D position;
		Euler3D rotation;
		PADDING(4);
		Memory::BigEndian<std::int8_t> appearance_player_index;
		PADDING(3);
		Index power_group;
		Index position_group;
		Memory::BigEndian<ScenarioDeviceFlags> device_flags;
		Memory::BigEndian<ScenarioControlFlags> control_flags;
		Memory::BigEndian<std::int16_t> custom_control_name;
		PADDING(2);
		PADDING(8);
	};
	static_assert(sizeof(ScenarioControl) == 64);

	struct ScenarioControlPalette {
		TagDependency name;
		PADDING(32);
	};
	static_assert(sizeof(ScenarioControlPalette) == 48);

	struct ScenarioLightFixture {
		Index type;
		Index name;
		Memory::BigEndian<ScenarioSpawnNotPlaced> not_placed;
		Memory::BigEndian<std::int16_t> desired_permutation;
		Point3D position;
		Euler3D rotation;
		Memory::BigEndian<std::uint16_t> bsp_indices;
		PADDING(2);
		Memory::BigEndian<std::int8_t> appearance_player_index;
		PADDING(3);
		Index power_group;
		Index position_group;
		Memory::BigEndian<ScenarioDeviceFlags> device_flags;
		ColorRGB color;
		Memory::BigEndian<float> intensity;
		Angle falloff_angle;
		Angle cutoff_angle;
		PADDING(16);
	};
	static_assert(sizeof(ScenarioLightFixture) == 88);

	struct ScenarioLightFixturePalette {
		TagDependency name;
		PADDING(32);
	};
	static_assert(sizeof(ScenarioLightFixturePalette) == 48);

	struct ScenarioSoundScenery {
		Index type;
		Index name;
		Memory::BigEndian<ScenarioSpawnNotPlaced> not_placed;
		Memory::BigEndian<std::int16_t> desired_permutation;
		Point3D position;
		Euler3D rotation;
		PADDING(4);
		Memory::BigEndian<std::int8_t> appearance_player_index;
		PADDING(3);
	};
	static_assert(sizeof(ScenarioSoundScenery) == 40);

	struct ScenarioSoundSceneryPalette {
		TagDependency name;
		PADDING(32);
	};
	static_assert(sizeof(ScenarioSoundSceneryPalette) == 48);

	struct ScenarioPlayerStartingProfile {
		TagString name;
		Fraction starting_health_modifier;
		Fraction starting_shield_modifier;
		TagDependency primary_weapon;
		Memory::BigEndian<std::int16_t> primary_rounds_loaded;
		Memory::BigEndian<std::int16_t> primary_rounds_reserved;
		TagDependency secondary_weapon;
		Memory::BigEndian<std::int16_t> secondary_rounds_loaded;
		Memory::BigEndian<std::int16_t> secondary_rounds_reserved;
		Memory::BigEndian<std::int8_t> starting_fragmentation_grenade_count;
		Memory::BigEndian<std::int8_t> starting_plasma_grenade_count;
		Memory::BigEndian<std::int8_t> starting_grenade_type2_count;
		Memory::BigEndian<std::int8_t> starting_grenade_type3_count;
		PADDING(20);
	};
	static_assert(sizeof(ScenarioPlayerStartingProfile) == 104);

	struct ScenarioPlayerStartingLocation {
		Point3D position;
		Angle facing;
		Index team_index;
		Index bsp_index;
		Memory::BigEndian<ScenarioSpawnType> type_0;
		Memory::BigEndian<ScenarioSpawnType> type_1;
		Memory::BigEndian<ScenarioSpawnType> type_2;
		Memory::BigEndian<ScenarioSpawnType> type_3;
		PADDING(24);
	};
	static_assert(sizeof(ScenarioPlayerStartingLocation) == 52);

	struct ScenarioTriggerVolume {
		Memory::BigEndian<std::uint16_t> unknown;
		PADDING(2);
		TagString name;
		Memory::BigEndian<float> parameters[3];
		Vector3D rotation_vector_a;
		Vector3D rotation_vector_b;
		Point3D starting_corner;
		Point3D ending_corner_offset;
	};
	static_assert(sizeof(ScenarioTriggerVolume) == 96);

	struct ScenarioRecordedAnimation {
		TagString name;
		Memory::BigEndian<std::int8_t> version;
		Memory::BigEndian<std::int8_t> raw_animation_data;
		Memory::BigEndian<std::int8_t> unit_control_data_version;
		PADDING(1);
		Memory::BigEndian<std::int16_t> length_of_animation;
		PADDING(2);
		PADDING(4);
		TagDataOffset recorded_animation_event_stream;
	};
	static_assert(sizeof(ScenarioRecordedAnimation) == 64);

	struct ScenarioNetgameFlags {
		Point3D position;
		Angle facing;
		Memory::BigEndian<ScenarioNetgameFlagType> type;
		Index usage_id;
		TagDependency weapon_group;
		PADDING(112);
	};
	static_assert(sizeof(ScenarioNetgameFlags) == 148);

	struct ScenarioNetgameEquipment {
		Memory::BigEndian<ScenarioNetgameEquipmentFlags> flags;
		Memory::BigEndian<ScenarioSpawnType> type_0;
		Memory::BigEndian<ScenarioSpawnType> type_1;
		Memory::BigEndian<ScenarioSpawnType> type_2;
		Memory::BigEndian<ScenarioSpawnType> type_3;
		Index team_index;
		Memory::BigEndian<std::int16_t> spawn_time;
		Memory::BigEndian<std::uint32_t> unknown_ffffffff;
		PADDING(44);
		Point3D position;
		Angle facing;
		TagDependency item_collection;
		PADDING(48);
	};
	static_assert(sizeof(ScenarioNetgameEquipment) == 144);

	struct ScenarioStartingEquipment {
		Memory::BigEndian<ScenarioStartingEquipmentFlags> flags;
		Memory::BigEndian<ScenarioSpawnType> type_0;
		Memory::BigEndian<ScenarioSpawnType> type_1;
		Memory::BigEndian<ScenarioSpawnType> type_2;
		Memory::BigEndian<ScenarioSpawnType> type_3;
		PADDING(48);
		TagDependency item_collection_1;
		TagDependency item_collection_2;
		TagDependency item_collection_3;
		TagDependency item_collection_4;
		TagDependency item_collection_5;
		TagDependency item_collection_6;
		PADDING(48);
	};
	static_assert(sizeof(ScenarioStartingEquipment) == 204);

	struct ScenarioBSPSwitchTriggerVolume {
		Index trigger_volume;
		Index source;
		Index destination;
		Memory::BigEndian<std::uint16_t> unknown;
	};
	static_assert(sizeof(ScenarioBSPSwitchTriggerVolume) == 8);

	struct ScenarioDecal {
		Index decal_type;
		Memory::BigEndian<std::int8_t> yaw;
		Memory::BigEndian<std::int8_t> pitch;
		Point3D position;
	};
	static_assert(sizeof(ScenarioDecal) == 16);

	struct ScenarioDecalPalette {
		TagDependency reference;
	};
	static_assert(sizeof(ScenarioDecalPalette) == 16);

	struct ScenarioDetailObjectCollectionPalette {
		TagDependency reference;
		PADDING(32);
	};
	static_assert(sizeof(ScenarioDetailObjectCollectionPalette) == 48);

	struct ScenarioActorPalette {
		TagDependency reference;
	};
	static_assert(sizeof(ScenarioActorPalette) == 16);

	struct ScenarioMovePosition {
		Point3D position;
		Angle facing;
		Memory::BigEndian<float> weight;
		Memory::BigEndian<float> time[2];
		Index animation;
		Memory::BigEndian<std::int8_t> sequence_id;
		PADDING(1);
		PADDING(8);
		Index cluster_index;
		PADDING(34);
		Memory::BigEndian<std::uint32_t> surface_index;
	};
	static_assert(sizeof(ScenarioMovePosition) == 80);

	struct ScenarioActorStartingLocation {
		Point3D position;
		Angle facing;
		Index cluster_index;
		Memory::BigEndian<std::int8_t> sequence_id;
		Memory::BigEndian<ScenarioActorStartingLocationFlags> flags;
		Memory::BigEndian<ScenarioReturnState> return_state;
		Memory::BigEndian<ScenarioReturnState> initial_state;
		Index actor_type;
		Index command_list;
	};
	static_assert(sizeof(ScenarioActorStartingLocation) == 28);

	struct ScenarioSquad {
		TagString name;
		Index actor_type;
		Index platoon;
		Memory::BigEndian<ScenarioReturnState> initial_state;
		Memory::BigEndian<ScenarioReturnState> return_state;
		Memory::BigEndian<ScenarioSquadFlags> flags;
		Memory::BigEndian<ScenarioUniqueLeaderType> unique_leader_type;
		PADDING(2);
		PADDING(28);
		PADDING(2);
		Index maneuver_to_squad;
		Memory::BigEndian<float> squad_delay_time;
		Memory::BigEndian<ScenarioSquadAttacking> attacking;
		Memory::BigEndian<ScenarioSquadAttacking> attacking_search;
		Memory::BigEndian<ScenarioSquadAttacking> attacking_guard;
		Memory::BigEndian<ScenarioSquadAttacking> defending;
		Memory::BigEndian<ScenarioSquadAttacking> defending_search;
		Memory::BigEndian<ScenarioSquadAttacking> defending_guard;
		Memory::BigEndian<ScenarioSquadAttacking> pursuing;
		PADDING(4);
		PADDING(8);
		Memory::BigEndian<std::int16_t> normal_diff_count;
		Memory::BigEndian<std::int16_t> insane_diff_count;
		Memory::BigEndian<ScenarioMajorUpgrade> major_upgrade;
		PADDING(2);
		Memory::BigEndian<std::int16_t> respawn_min_actors;
		Memory::BigEndian<std::int16_t> respawn_max_actors;
		Memory::BigEndian<std::int16_t> respawn_total;
		PADDING(2);
		Memory::BigEndian<float> respawn_delay[2];
		PADDING(48);
		TagReflexive<ScenarioMovePosition> move_positions;
		TagReflexive<ScenarioActorStartingLocation> starting_locations;
		PADDING(12);
	};
	static_assert(sizeof(ScenarioSquad) == 232);

	struct ScenarioPlatoon {
		TagString name;
		Memory::BigEndian<ScenarioPlatoonFlags> flags;
		PADDING(12);
		Memory::BigEndian<ScenarioChangeAttackingDefendingStateWhen> change_attacking_defending_state_when;
		Index happens_to;
		PADDING(4);
		PADDING(4);
		Memory::BigEndian<ScenarioChangeAttackingDefendingStateWhen> maneuver_when;
		Index happens_to_1;
		PADDING(4);
		PADDING(4);
		PADDING(64);
		PADDING(36);
	};
	static_assert(sizeof(ScenarioPlatoon) == 172);

	struct ScenarioFiringPosition {
		Point3D position;
		Memory::BigEndian<ScenarioGroupIndex> group_index;
		Index cluster_index;
		PADDING(4);
		Memory::BigEndian<std::uint32_t> surface_index;
	};
	static_assert(sizeof(ScenarioFiringPosition) == 24);

	struct ScenarioEncounter {
		TagString name;
		Memory::BigEndian<ScenarioEncounterFlags> flags;
		Memory::BigEndian<ScenarioTeamIndex> team_index;
		Memory::BigEndian<std::int16_t> one;
		Memory::BigEndian<ScenarioSearchBehavior> search_behavior;
		Index manual_bsp_index;
		Memory::BigEndian<float> respawn_delay[2];
		PADDING(74);
		Index precomputed_bsp_index;
		TagReflexive<ScenarioSquad> squads;
		TagReflexive<ScenarioPlatoon> platoons;
		TagReflexive<ScenarioFiringPosition> firing_positions;
		TagReflexive<ScenarioPlayerStartingLocation> player_starting_locations;
	};
	static_assert(sizeof(ScenarioEncounter) == 176);

	struct ScenarioCommand {
		Memory::BigEndian<ScenarioAtomType> atom_type;
		Memory::BigEndian<std::int16_t> atom_modifier;
		Memory::BigEndian<float> parameter1;
		Memory::BigEndian<float> parameter2;
		Index point_1;
		Index point_2;
		Index animation;
		Index script;
		Index recording;
		Index command;
		Index object_name;
		PADDING(6);
	};
	static_assert(sizeof(ScenarioCommand) == 32);

	struct ScenarioCommandPoint {
		Point3D position;
		Memory::BigEndian<std::uint32_t> surface_index;
		PADDING(4);
	};
	static_assert(sizeof(ScenarioCommandPoint) == 20);

	struct ScenarioCommandList {
		TagString name;
		Memory::BigEndian<ScenarioCommandListFlags> flags;
		PADDING(8);
		Index manual_bsp_index;
		Index precomputed_bsp_index;
		TagReflexive<ScenarioCommand> commands;
		TagReflexive<ScenarioCommandPoint> points;
		PADDING(24);
	};
	static_assert(sizeof(ScenarioCommandList) == 96);

	struct ScenarioAIAnimationReference {
		TagString animation_name;
		TagDependency animation_graph;
		PADDING(12);
	};
	static_assert(sizeof(ScenarioAIAnimationReference) == 60);

	struct ScenarioAIScriptReference {
		TagString script_name;
		PADDING(8);
	};
	static_assert(sizeof(ScenarioAIScriptReference) == 40);

	struct ScenarioAIRecordingReference {
		TagString recording_name;
		PADDING(8);
	};
	static_assert(sizeof(ScenarioAIRecordingReference) == 40);

	struct ScenarioAIConversationParticipant {
		PADDING(2);
		Memory::BigEndian<ScenarioAIConversationParticipantFlags> flags;
		Memory::BigEndian<ScenarioSelectionType> selection_type;
		Memory::BigEndian<ActorType> actor_type;
		Index use_this_object;
		Index set_new_name;
		PADDING(12);
		Memory::BigEndian<std::uint16_t> variant_numbers[6];
		TagString encounter_name;
		Memory::BigEndian<std::uint32_t> encounter_index;
		PADDING(12);
	};
	static_assert(sizeof(ScenarioAIConversationParticipant) == 84);

	struct ScenarioAIConversationLine {
		Memory::BigEndian<ScenarioAIConversationLineFlags> flags;
		Index participant;
		Memory::BigEndian<ScenarioAddressee> addressee;
		Index addressee_participant;
		PADDING(4);
		Memory::BigEndian<float> line_delay_time;
		PADDING(12);
		TagDependency variant_1;
		TagDependency variant_2;
		TagDependency variant_3;
		TagDependency variant_4;
		TagDependency variant_5;
		TagDependency variant_6;
	};
	static_assert(sizeof(ScenarioAIConversationLine) == 124);

	struct ScenarioAIConversation {
		TagString name;
		Memory::BigEndian<ScenarioAIConversationFlags> flags;
		PADDING(2);
		Memory::BigEndian<float> trigger_distance;
		Memory::BigEndian<float> run_to_player_dist;
		PADDING(36);
		TagReflexive<ScenarioAIConversationParticipant> participants;
		TagReflexive<ScenarioAIConversationLine> lines;
		PADDING(12);
	};
	static_assert(sizeof(ScenarioAIConversation) == 116);

	struct ScenarioScriptParameter {
		TagString name;
		Memory::BigEndian<ScenarioScriptValueType> return_type;
		PADDING(2);
	};
	static_assert(sizeof(ScenarioScriptParameter) == 36);

	struct ScenarioScript {
		TagString name;
		Memory::BigEndian<ScenarioScriptType> script_type;
		Memory::BigEndian<ScenarioScriptValueType> return_type;
		Memory::BigEndian<std::uint32_t> root_expression_index;
		PADDING(40);
		TagReflexive<ScenarioScriptParameter> parameters;
	};
	static_assert(sizeof(ScenarioScript) == 92);

	struct ScenarioGlobal {
		TagString name;
		Memory::BigEndian<ScenarioScriptValueType> type;
		PADDING(2);
		PADDING(4);
		Memory::BigEndian<std::int32_t> initialization_expression_index;
		PADDING(48);
	};
	static_assert(sizeof(ScenarioGlobal) == 92);

	struct ScenarioReference {
		PADDING(24);
		TagDependency reference;
	};
	static_assert(sizeof(ScenarioReference) == 40);

	struct ScenarioSourceFile {
		TagString name;
		TagDataOffset source;
	};
	static_assert(sizeof(ScenarioSourceFile) == 52);

	struct ScenarioCutsceneFlag {
		Memory::BigEndian<std::uint32_t> unknown;
		TagString name;
		Point3D position;
		Euler2D facing;
		PADDING(36);
	};
	static_assert(sizeof(ScenarioCutsceneFlag) == 92);

	struct ScenarioCutsceneCameraPoint {
		Memory::BigEndian<std::uint32_t> unknown;
		TagString name;
		PADDING(4);
		Point3D position;
		Euler3D orientation;
		Angle field_of_view;
		PADDING(36);
	};
	static_assert(sizeof(ScenarioCutsceneCameraPoint) == 104);

	struct ScenarioCutsceneTitle {
		Memory::BigEndian<std::uint32_t> unknown;
		TagString name;
		PADDING(4);
		Rectangle2D text_bounds;
		Index string_index;
		Memory::BigEndian<ScenarioTextStyle> text_style;
		Memory::BigEndian<ScenarioJustification> justification;
		PADDING(2);
		Memory::BigEndian<ScenarioTextFlags> text_flags;
		ColorARGBInt text_color;
		ColorARGBInt shadow_color;
		Memory::BigEndian<float> fade_in_time;
		Memory::BigEndian<float> up_time;
		Memory::BigEndian<float> fade_out_time;
		PADDING(16);
	};
	static_assert(sizeof(ScenarioCutsceneTitle) == 96);

	struct ScenarioBSP {
		Memory::BigEndian<std::uint32_t> bsp_start;
		Memory::BigEndian<std::uint32_t> bsp_size;
		Memory::BigEndian<std::uint32_t> bsp_address;
		PADDING(4);
		TagDependency structure_bsp;
	};
	static_assert(sizeof(ScenarioBSP) == 32);

	struct ScenarioScriptNode {
		Memory::BigEndian<std::uint16_t> salt;
		Memory::BigEndian<std::uint16_t> index_union;
		Memory::BigEndian<ScenarioScriptValueType> type;
		Memory::BigEndian<ScenarioScriptNodeFlags> flags;
		Memory::BigEndian<std::uint32_t> next_node;
		Memory::BigEndian<std::uint32_t> string_offset;
		ScenarioScriptNodeValue data;
	};
	static_assert(sizeof(ScenarioScriptNode) == 20);

	struct ScenarioScriptNodeTable {
		TagString name;
		Memory::BigEndian<std::uint16_t> maximum_count;
		Memory::BigEndian<std::uint16_t> element_size;
		Memory::BigEndian<std::uint8_t> one;
		PADDING(3);
		Memory::BigEndian<std::uint32_t> data;
		PADDING(2);
		Memory::BigEndian<std::uint16_t> size;
		Memory::BigEndian<std::uint16_t> count;
		Memory::BigEndian<std::uint16_t> next_id;
		Memory::BigEndian<std::uint32_t> first_element_ptr;
	};
	static_assert(sizeof(ScenarioScriptNodeTable) == 56);

	struct Scenario {
		TagDependency dont_use;
		TagDependency wont_use;
		TagDependency cant_use;
		TagReflexive<ScenarioSky> skies;
		Memory::BigEndian<ScenarioType> type;
		Memory::BigEndian<ScenarioFlags> flags;
		TagReflexive<ScenarioChildScenario> child_scenarios;
		Memory::BigEndian<float> local_north;
		PADDING(20);
		PADDING(136);
		TagReflexive<PredictedResource> predicted_resources;
		TagReflexive<ScenarioFunction> functions;
		TagDataOffset editor_scenario_data;
		TagReflexive<ScenarioEditorComment> comments;
		TagReflexive<ScenarioScavengerHuntObjects> scavenger_hunt_objects;
		PADDING(212);
		TagReflexive<ScenarioObjectName> object_names;
		TagReflexive<ScenarioScenery> scenery;
		TagReflexive<ScenarioSceneryPalette> scenery_palette;
		TagReflexive<ScenarioBiped> bipeds;
		TagReflexive<ScenarioBipedPalette> biped_palette;
		TagReflexive<ScenarioVehicle> vehicles;
		TagReflexive<ScenarioVehiclePalette> vehicle_palette;
		TagReflexive<ScenarioEquipment> equipment;
		TagReflexive<ScenarioEquipmentPalette> equipment_palette;
		TagReflexive<ScenarioWeapon> weapons;
		TagReflexive<ScenarioWeaponPalette> weapon_palette;
		TagReflexive<ScenarioDeviceGroup> device_groups;
		TagReflexive<ScenarioMachine> machines;
		TagReflexive<ScenarioMachinePalette> machine_palette;
		TagReflexive<ScenarioControl> controls;
		TagReflexive<ScenarioControlPalette> control_palette;
		TagReflexive<ScenarioLightFixture> light_fixtures;
		TagReflexive<ScenarioLightFixturePalette> light_fixture_palette;
		TagReflexive<ScenarioSoundScenery> sound_scenery;
		TagReflexive<ScenarioSoundSceneryPalette> sound_scenery_palette;
		PADDING(84);
		TagReflexive<ScenarioPlayerStartingProfile> player_starting_profile;
		TagReflexive<ScenarioPlayerStartingLocation> player_starting_locations;
		TagReflexive<ScenarioTriggerVolume> trigger_volumes;
		TagReflexive<ScenarioRecordedAnimation> recorded_animations;
		TagReflexive<ScenarioNetgameFlags> netgame_flags;
		TagReflexive<ScenarioNetgameEquipment> netgame_equipment;
		TagReflexive<ScenarioStartingEquipment> starting_equipment;
		TagReflexive<ScenarioBSPSwitchTriggerVolume> bsp_switch_trigger_volumes;
		TagReflexive<ScenarioDecal> decals;
		TagReflexive<ScenarioDecalPalette> decal_palette;
		TagReflexive<ScenarioDetailObjectCollectionPalette> detail_object_collection_palette;
		PADDING(84);
		TagReflexive<ScenarioActorPalette> actor_palette;
		TagReflexive<ScenarioEncounter> encounters;
		TagReflexive<ScenarioCommandList> command_lists;
		TagReflexive<ScenarioAIAnimationReference> ai_animation_references;
		TagReflexive<ScenarioAIScriptReference> ai_script_references;
		TagReflexive<ScenarioAIRecordingReference> ai_recording_references;
		TagReflexive<ScenarioAIConversation> ai_conversations;
		TagDataOffset script_syntax_data;
		TagDataOffset script_string_data;
		TagReflexive<ScenarioScript> scripts;
		TagReflexive<ScenarioGlobal> globals;
		TagReflexive<ScenarioReference> references;
		TagReflexive<ScenarioSourceFile> source_files;
		PADDING(24);
		TagReflexive<ScenarioCutsceneFlag> cutscene_flags;
		TagReflexive<ScenarioCutsceneCameraPoint> cutscene_camera_points;
		TagReflexive<ScenarioCutsceneTitle> cutscene_titles;
		PADDING(108);
		TagDependency custom_object_names;
		TagDependency ingame_help_text;
		TagDependency hud_messages;
		TagReflexive<ScenarioBSP> structure_bsps;
	};
	static_assert(sizeof(Scenario) == 1456);

}

#endif

