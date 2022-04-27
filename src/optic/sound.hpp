// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_OPTIC_SOUND_HPP
#define HARMONY_OPTIC_SOUND_HPP

#include <string>
#include <queue>
#include <filesystem>
#include <soloud.h>
#include <soloud_wav.h>

namespace Harmony::Optic {
	class Sound : public SoLoud::Wav {
	public:
		/**
		 * Constructor for sound
         * @param path		Path to sound file
         * @exception		If sound file does not exists
		 */
		Sound(std::filesystem::path path);

		/**
		 * Deleted copy constructor
		 * Copying a sound makes it sound weird and glitchy
		 */
		Sound(const Sound &) = delete;

		/**
		 * Destructor for sound
		 */
		~Sound() noexcept;

	private:
		/** Sound path */
		std::filesystem::path path;
	};

	class AudioEngine : public SoLoud::Soloud {
	friend class Handler;
	public:
		/**
		 * Enqueue a sound
         * @param sound		Pointer to sound
		 */
		void enqueue(Sound *sound) noexcept;

		/**
		 * Constructor for audio engine instance
		 */
		AudioEngine() = default;

	private:
		/** Playback queue */
		std::queue<Sound *> queue;
	};
}

#endif
