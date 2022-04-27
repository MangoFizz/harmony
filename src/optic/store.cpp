// SPDX-License-Identifier: GPL-3.0-only

#include <cmath>
#include <ctime>
#include "../halo_data/master_volume.hpp"
#include "../harmony.hpp"
#include "exception.hpp"
#include "handler.hpp"
#include "store.hpp"

namespace Harmony::Optic {
    Animation *Store::get_animation(ResourceHandle handle) noexcept {
        if(handle < animations.size()) {
            return &animations[handle];
        }
        return nullptr;
    }

    Store::ResourceHandle Store::create_animation(long duration) {
        animations.emplace_back(duration);
        return animations.size() - 1;
    }

    void Store::remove_animation(ResourceHandle handle) {
        if(handle < animations.size()) {
            animations.erase(animations.begin() + handle);
        }
        throw Exception("invalid animation handle");
    }

    Sound *Store::get_sound(ResourceHandle handle) noexcept {
        if(handle < sounds.size()) {
            return sounds[handle].get();
        }
        return nullptr;
    }

    Store::ResourceHandle Store::create_sound(std::filesystem::path sound_path) {
        try {
            sounds.emplace_back(std::make_unique<Sound>(sound_path));
        }
        catch(...) {
            throw;
        }
        return sounds.size() - 1;
    }

    void Store::remove_sound(ResourceHandle handle) {
        if(handle < sounds.size()) {
            sounds.erase(sounds.begin() + handle);
        }
        throw Exception("invalid sound handle");
    }

    Sprite *Store::get_sprite(ResourceHandle handle) noexcept {
        if(handle < sprites.size()) {
            return &sprites[handle];
        }
        return nullptr;
    }

    Store::ResourceHandle Store::create_sprite(std::string texture, int width, int height) {
        try {
            sprites.emplace_back(texture, width, height);
        }
        catch(...) {
            throw;
        }
        return sprites.size() - 1;
    }

    Store::ResourceHandle Store::create_sprite(std::string texture, std::size_t sheet_rows, std::size_t sheet_columns, std::size_t sheet_frames, std::size_t frames_per_second, int frame_width, int frame_height) {
        try {
            sprites.emplace_back(texture, sheet_rows, sheet_columns, sheet_frames, frames_per_second, frame_width, frame_height);
        }
        catch(...) {
            throw;
        }
        return sprites.size() - 1;
    }

    void Store::remove_sprite(ResourceHandle handle) {
        if(handle < sprites.size()) {
            sprites.erase(sprites.begin() + handle);
        }
        throw Exception("invalid sprite handle");
    }

    void Store::load_sprites(LPDIRECT3DDEVICE9 device) noexcept {
        for(auto &sprite : this->sprites) {
            sprite.load(device);
        }
    }

    void Store::release_sprites() noexcept {
        for(auto &sprite : this->sprites) {
            sprite.unload();
        }
    }

    RenderQueue *Store::get_render_queue(ResourceHandle handle) noexcept {
        if(handle < render_queues.size()) {
            return &render_queues[handle];
        }
        return nullptr;
    }

    Store::ResourceHandle Store::create_render_queue(Sprite::State initial_render_state, float rotation, std::size_t maximum_renders, long render_duration, bool temporal) {
        this->render_queues.emplace_back(initial_render_state, rotation, maximum_renders, render_duration, temporal);
        return render_queues.size() - 1;
    }

    void Store::remove_queue(ResourceHandle handle) {
        if(handle < render_queues.size()) {
            render_queues.erase(render_queues.begin() + handle);
        }
        throw Exception("invalid render queue handle");
    }

    void Store::render_sprite(ResourceHandle sprite_handle, ResourceHandle render_queue) {
        auto *queue = get_render_queue(render_queue);
        auto *sprite = get_sprite(sprite_handle);

        if(sprite) {
            if(queue) {
                queue->enqueue_sprite(sprite);
            }
            else {
                throw Exception("invalid render queue handle");
            }
        }
        else {
            throw Exception("invalid sprite handle");
        }
    }

    void Store::render_sprite(ResourceHandle sprite_handle, Sprite::State initial_state, long duration, Animation fade_in, Animation fade_out) {
        auto *sprite = get_sprite(sprite_handle);
        if(!sprite) {
            throw Exception("invalid sprite handle");
        }

        auto &tmp_queue = render_queues.emplace_back(initial_state, 0, 0, duration, true);
        tmp_queue.set_fade_in_anim(fade_in);
        tmp_queue.set_fade_out_anim(fade_out);
        tmp_queue.enqueue_sprite(sprite);
    }

    AudioEngine *Store::get_audio_engine(ResourceHandle handle) noexcept {
        if(handle < audio_engines.size()) {
            return audio_engines[handle].get();
        }
        return nullptr;
    }

    Store::ResourceHandle Store::create_audio_engine() {
        auto &instance = audio_engines.emplace_back(std::make_unique<AudioEngine>());
        instance->init();
        instance->setGlobalVolume(static_cast<float>(HaloData::get_master_volume()) / 10);

        return audio_engines.size() - 1;
    }

    void Store::remove_audio_engine(ResourceHandle handle) {
        if(handle < audio_engines.size()) {
            audio_engines.erase(audio_engines.begin() + handle);
        }
        throw Exception("invalid audio engine handle");
    }

    void Store::play_sound(ResourceHandle sound_handle, ResourceHandle engine_handle, bool no_enqueue) {
        auto *instance = this->get_audio_engine(engine_handle);
        auto *sound = this->get_sound(sound_handle);

        if(sound) {
            if(instance) {
                if(no_enqueue) {
                    instance->play(*sound);
                }
                else {
                    instance->enqueue(sound);
                }
            }
            else {
                throw Exception("invalid audio engine handle");
            }
        }
        else {
            throw Exception("invalid sound handle");
        }
    }

    Store::~Store() {
        this->release_sprites();
    }
}