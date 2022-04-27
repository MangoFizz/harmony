// SPDX-License-Identifier: GPL-3.0-only

#include "exception.hpp"
#include "sound.hpp"

namespace Harmony::Optic {
    Sound::Sound(std::filesystem::path path) {
        this->path = path;

        if(!std::filesystem::exists(path)) {
            throw Exception("File '" + path.string() + "' does not exists!");
        }
        this->load(path.string().c_str());
    }

    Sound::~Sound() noexcept {
        this->mSoloud = nullptr;
    }

	void AudioEngine::enqueue(Sound *sound) noexcept {
        this->queue.push(sound);
    }
}
