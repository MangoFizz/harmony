// SPDX-License-Identifier: GPL-3.0-only

#include "exception.hpp"
#include "sound.hpp"

namespace Harmony::Optic {
    std::string Sound::get_name() const noexcept {
        return this->name;
    }

    void Sound::set_name(std::string name) noexcept {
        this->name = name;
    }

    Sound::Sound(std::string name, std::filesystem::path path) {
        this->name = name;
        this->path = path;

        if(!std::filesystem::exists(path)) {
            throw Exception("File for sound '" + name + "' does not exists!");
        }
        this->load(path.string().c_str());
    }

    Sound::~Sound() noexcept {
        this->mSoloud = nullptr;
    }

    std::string AudioEngine::get_name() const noexcept {
        return this->name;
    }

    void AudioEngine::set_name(std::string name) noexcept {
        this->name = name;
    }

	void AudioEngine::enqueue(Sound *sound) noexcept {
        this->queue.push(sound);
    }

    AudioEngine::AudioEngine(std::string name) noexcept {
        this->name = name;
    }
}
