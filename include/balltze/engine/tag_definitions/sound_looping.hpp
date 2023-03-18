// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__SOUND_LOOPING_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__SOUND_LOOPING_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct SoundLoopingTrackFlags {
		std::uint32_t fade_in_at_start : 1;
		std::uint32_t fade_out_at_stop : 1;
		std::uint32_t fade_in_alternate : 1;
	};
	static_assert(sizeof(SoundLoopingTrackFlags) == sizeof(std::uint32_t));

	struct SoundLoopingDetailFlags {
		std::uint32_t dont_play_with_alternate : 1;
		std::uint32_t dont_play_without_alternate : 1;
	};
	static_assert(sizeof(SoundLoopingDetailFlags) == sizeof(std::uint32_t));

	struct SoundLoopingFlags {
		std::uint32_t deafening_to_ais : 1;
		std::uint32_t not_a_loop : 1;
		std::uint32_t stops_music : 1;
		std::uint32_t siege_of_madrigal : 1;
	};
	static_assert(sizeof(SoundLoopingFlags) == sizeof(std::uint32_t));

	struct SoundLoopingTrack {
		SoundLoopingTrackFlags flags;
		Fraction gain;
		float fade_in_duration;
		float fade_out_duration;
		PADDING(32);
		TagDependency start;
		TagDependency loop;
		TagDependency end;
		PADDING(32);
		TagDependency alternate_loop;
		TagDependency alternate_end;
	};
	static_assert(sizeof(SoundLoopingTrack) == 160);

	struct SoundLoopingDetail {
		TagDependency sound;
		float random_period_bounds[2];
		Fraction gain;
		SoundLoopingDetailFlags flags;
		PADDING(48);
		Angle yaw_bounds[2];
		Angle pitch_bounds[2];
		float distance_bounds[2];
	};
	static_assert(sizeof(SoundLoopingDetail) == 104);

	struct SoundLooping {
		SoundLoopingFlags flags;
		float zero_detail_sound_period;
		float zero_detail_unknown_floats[2];
		float one_detail_sound_period;
		float one_detail_unknown_floats[2];
		std::uint32_t unknown_int;
		float maximum_distance;
		PADDING(8);
		TagDependency continuous_damage_effect;
		TagReflexive<SoundLoopingTrack> tracks;
		TagReflexive<SoundLoopingDetail> detail_sounds;
	};
	static_assert(sizeof(SoundLooping) == 84);

}

#endif

