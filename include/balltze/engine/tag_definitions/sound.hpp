// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__SOUND_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__SOUND_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class SoundFormat : std::uint16_t {
		_16_BIT_PCM = 0,
		XBOX_ADPCM,
		IMA_ADPCM,
		OGG_VORBIS,
	};

	enum class SoundClass : std::uint16_t {
		PROJECTILE_IMPACT = 0,
		PROJECTILE_DETONATION,
		UNUSED,
		UNUSED1,
		WEAPON_FIRE,
		WEAPON_READY,
		WEAPON_RELOAD,
		WEAPON_EMPTY,
		WEAPON_CHARGE,
		WEAPON_OVERHEAT,
		WEAPON_IDLE,
		UNUSED2,
		UNUSED3,
		OBJECT_IMPACTS,
		PARTICLE_IMPACTS,
		SLOW_PARTICLE_IMPACTS,
		UNUSED4,
		UNUSED5,
		UNIT_FOOTSTEPS,
		UNIT_DIALOG,
		UNUSED6,
		UNUSED7,
		VEHICLE_COLLISION,
		VEHICLE_ENGINE,
		UNUSED8,
		UNUSED9,
		DEVICE_DOOR,
		DEVICE_FORCE_FIELD,
		DEVICE_MACHINERY,
		DEVICE_NATURE,
		DEVICE_COMPUTERS,
		UNUSED10,
		MUSIC,
		AMBIENT_NATURE,
		AMBIENT_MACHINERY,
		AMBIENT_COMPUTERS,
		UNUSED11,
		UNUSED12,
		UNUSED13,
		FIRST_PERSON_DAMAGE,
		UNUSED14,
		UNUSED15,
		UNUSED16,
		UNUSED17,
		SCRIPTED_DIALOG_PLAYER,
		SCRIPTED_EFFECT,
		SCRIPTED_DIALOG_OTHER,
		SCRIPTED_DIALOG_FORCE_UNSPATIALIZED,
		UNUSED18,
		UNUSED19,
		GAME_EVENT,
	};

	enum class SoundSampleRate : std::uint16_t {
		_22050__HZ = 0,
		_44100__HZ,
	};

	enum class SoundChannelCount : std::uint16_t {
		MONO = 0,
		STEREO,
	};

	struct SoundFlags {
		std::uint32_t fit_to_adpcm_blocksize : 1;
		std::uint32_t split_long_sound_into_permutations : 1;
		std::uint32_t thirsty_grunt : 1;
	};
	static_assert(sizeof(SoundFlags) == sizeof(std::uint32_t));

	struct SoundPermutation {
		TagString name;
		Fraction skip_fraction;
		Fraction gain;
		SoundFormat format;
		Index next_permutation_index;
		std::uint32_t samples_pointer;
		PADDING(4);
		TagHandle tag_id_0;
		std::uint32_t buffer_size;
		TagHandle tag_id_1;
		TagDataOffset samples;
		TagDataOffset mouth_data;
		TagDataOffset subtitle_data;
	};
	static_assert(sizeof(SoundPermutation) == 124);

	struct SoundPitchRange {
		TagString name;
		float natural_pitch;
		float bend_bounds[2];
		std::uint16_t actual_permutation_count;
		PADDING(2);
		float playback_rate;
		std::uint32_t unknown_ffffffff_0;
		std::uint32_t unknown_ffffffff_1;
		TagReflexive<SoundPermutation> permutations;
	};
	static_assert(sizeof(SoundPitchRange) == 72);

	struct Sound {
		SoundFlags flags;
		SoundClass sound_class;
		SoundSampleRate sample_rate;
		float minimum_distance;
		float maximum_distance;
		Fraction skip_fraction;
		float random_pitch_bounds[2];
		Angle inner_cone_angle;
		Angle outer_cone_angle;
		Fraction outer_cone_gain;
		float random_gain_modifier;
		float maximum_bend_per_second;
		PADDING(12);
		float zero_skip_fraction_modifier;
		float zero_gain_modifier;
		float zero_pitch_modifier;
		PADDING(12);
		float one_skip_fraction_modifier;
		float one_gain_modifier;
		float one_pitch_modifier;
		PADDING(12);
		SoundChannelCount channel_count;
		SoundFormat format;
		TagDependency promotion_sound;
		std::uint16_t promotion_count;
		PADDING(2);
		std::uint32_t longest_permutation_length;
		PADDING(8);
		std::uint32_t unknown_ffffffff_0;
		std::uint32_t unknown_ffffffff_1;
		TagReflexive<SoundPitchRange> pitch_ranges;
	};
	static_assert(sizeof(Sound) == 164);

}

#endif

