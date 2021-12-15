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
         * Get sound name
         */
        std::string get_name() const noexcept;

        /**
         * Set sound name
         * @param name  		New name for sound
         */
        void set_name(std::string name) noexcept;

		/**
		 * Constructor for sound
         * @param name		New name for animation
         * @param path		Path to sound file
         * @exception		If sound file does not exists
		 */
		Sound(std::string name, std::filesystem::path path);

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
		/** Name of the sound */
		std::string name;

		/** Sound path */
		std::filesystem::path path;
	};

	class AudioEngine : public SoLoud::Soloud {
	friend class Handler;
	public:
		/**
         * Get audio engine instance name
         */
        std::string get_name() const noexcept;

        /**
         * Set audio engine instance name
         * @param name  		New name for animation
         */
        void set_name(std::string name) noexcept;

		/**
		 * Enqueue a sound
         * @param sound		Pointer to sound
		 */
		void enqueue(Sound *sound) noexcept;

		/**
		 * Constructor for audio engine instance
         * @param name		New name for animation
		 */
		AudioEngine(std::string name) noexcept;

	private:
		/** Name */
		std::string name;

		/** Playback queue */
		std::queue<Sound *> queue;
	};
}

#endif
