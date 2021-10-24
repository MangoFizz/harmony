// SPDX-License-Identifier: GPL-3.0-only

#include <cmath>
#include <ctime>
#include "../halo_data/master_volume.hpp"
#include "../harmony.hpp"
#include "exception.hpp"
#include "handler.hpp"
#include "container.hpp"

namespace Harmony::Optic {
    Animation *Container::get_animation(std::string name) noexcept {
        for(auto &anim : this->animations) {
            if(anim.get_name() == name) {
                return &anim;
            }
        }
        return nullptr;
    }

    void Container::create_animation(std::string name, long duration) {
        if(this->get_animation(name)) {
            throw Exception("Animation '" + name + "' already exists!");
        }
        this->animations.emplace_back(name, duration);
    }

    void Container::remove_animation(std::string name) {
        auto it = this->animations.begin();
        while(it != this->animations.end()) {
            if(it->get_name() == name) {
                this->animations.erase(it);
                return;
            }
            it++;
        }
        throw Exception("Animation '" + name + "' does not exists!");
    }

    Sound *Container::get_sound(std::string name) noexcept {
        for(auto &sound : this->sounds) {
            if(sound.get_name() == name) {
                return &sound;
            }
        }
        return nullptr;
    }

    void Container::create_sound(std::string name, std::filesystem::path sound_poth) {
        if(this->get_sound(name)) {
            throw Exception("Sound '" + name + "' already exists!");
        }

        try {
            this->sounds.emplace_back(name, sound_poth);
        }
        catch(...) {
            throw;
        }
    }

    void Container::remove_sound(std::string name) {
        auto it = this->sounds.begin();
        while(it != this->sounds.end()) {
            if(it->get_name() == name) {
                this->sounds.erase(it);
                return;
            }
            it++;
        }
        throw Exception("Sound '" + name + "' does not exists!");
    }

    Sprite *Container::get_sprite(std::string name) noexcept {
        for(auto &sprite : this->sprites) {
            if(sprite.get_name() == name) {
                return &sprite;
            }
        }
        return nullptr;
    }

    void Container::create_sprite(std::string name, std::string texture, int width, int height) {
        if(this->get_sprite(name)) {
            throw Exception("Sprite '" + name + "' already exists!");
        }

        try {
            this->sprites.emplace_back(name, texture, width, height);
        }
        catch(...) {
            throw;
        }
    }

    void Container::remove_sprite(std::string name) {
        auto it = this->sprites.begin();
        while(it != this->sprites.end()) {
            if(it->get_name() == name) {
                this->sprites.erase(it);
                return;
            }
            it++;
        }
        throw Exception("Sprite '" + name + "' does not exists!");
    }

    void Container::load_sprites(LPDIRECT3DDEVICE9 device) noexcept {
        for(auto &sprite : this->sprites) {
            sprite.load(device);
        }
    }

    void Container::release_sprites() noexcept {
        for(auto &sprite : this->sprites) {
            sprite.unload();
        }
    }

    RenderQueue *Container::get_render_queue(std::string name) noexcept {
        for(auto &queue : this->render_queues) {
            if(queue.get_name() == name) {
                return &queue;
            }
        }
        return nullptr;
    }

    void Container::create_render_queue(std::string name, Sprite::State initial_render_state, float rotation, std::size_t maximum_renders, long render_duration, bool temporal) {
        if(this->get_render_queue(name)) {
            throw Exception("Render queue '" + name + "' already exists!");
        }
        this->render_queues.emplace_back(name, initial_render_state, rotation, maximum_renders, render_duration, temporal);
    }

    void Container::remove_queue(std::string name) {
        auto it = this->render_queues.begin();
        while(it != this->render_queues.end()) {
            if(it->get_name() == name) {
                this->render_queues.erase(it);
                return;
            }
            it++;
        }
        throw Exception("Render queue '" + name + "' does not exists!");
    }

    void Container::render_sprite(std::string sprite_name, std::string render_queue) {
        auto *queue = this->get_render_queue(render_queue);
        auto *sprite = this->get_sprite(sprite_name);

        if(sprite) {
            if(queue) {
                queue->enqueue_sprite(sprite);
            }
            else {
                throw Exception("queue '" + render_queue + "' does not exists!");
            }
        }
        else {
            throw Exception("Sprite '" + sprite_name + "' does not exists!");
        }
    }

    void Container::render_sprite(std::string sprite_name, Sprite::State initial_state, long duration, Animation fade_in, Animation fade_out) {
        auto *sprite = this->get_sprite(sprite_name);
        if(!sprite) {
            throw Exception("Sprite '" + sprite_name + "' does not exists!");
        }

        srand(time(0));
        auto tmp_name = "tmp" + std::to_string(rand());
        auto &tmp_queue = this->render_queues.emplace_back(tmp_name, initial_state, 0, 0, duration, true);
        tmp_queue.set_fade_in_anim(fade_in);
        tmp_queue.set_fade_out_anim(fade_out);
        tmp_queue.enqueue_sprite(sprite);
    }

    AudioEngine *Container::get_audio_queue(std::string name) noexcept {
        for(auto &queue_ptr : this->playback_queues) {
            auto *queue = queue_ptr.get();
            if(queue->get_name() == name) {
                return queue;
            }
        }
        return nullptr;
    }

    void Container::create_audio_queue(std::string name) {
        if(this->get_audio_queue(name)) {
            throw Exception("Audio playback queue '" + name + "' already exists!");
        }
        
        auto *queue = this->playback_queues.emplace_back(std::make_unique<AudioEngine>(name)).get();
        queue->init();
        queue->setGlobalVolume(static_cast<float>(HaloData::get_master_volume()) / 10);
    }

    void Container::remove_audio_queue(std::string name) {
        auto it = this->playback_queues.begin();
        while(it != this->playback_queues.end()) {
            if(it->get()->get_name() == name) {
                this->playback_queues.erase(it);
                return;
            }
            it++;
        }
        throw Exception("Audio playback queue '" + name + "' does not exists!");
    }

    Container::~Container() {
        this->release_sprites();
    }
}