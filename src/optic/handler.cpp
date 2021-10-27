// SPDX-License-Identifier: GPL-3.0-only

#include "../events/d3d9_end_scene.hpp"
#include "../events/d3d9_reset.hpp"
#include "../events/tick.hpp"
#include "../messaging/exception.hpp"
#include "../harmony.hpp"
#include "exception.hpp"
#include "handler.hpp"

namespace Harmony::Optic {
    static Handler *handler = nullptr;

    Container *Handler::get_optic(std::string name) noexcept {
        for(auto &optic : this->optics) {
            if(optic.first == name) {
                return optic.second.get();
            }
        }
        return nullptr;
    }

    Container *Handler::create_optic(std::string name) {
        if(this->get_optic(name)) {
            throw Exception("Optic container '" + name + "' already exists!");
        }
        this->optics[name] = std::make_unique<Container>();
        return this->optics[name].get();
    }

    void Handler::remove_optic(std::string name) {
        if(this->optics.find(name) == this->optics.end()) {
            throw Exception("Optic container '" + name + "' does not exists!");
        }
        this->optics.erase(name);
    }

    Handler::Handler() {
        if(handler) {
            throw ExceptionBox("Multiple Optic handler instances!");
        }
        handler = this;

        // Register end scene event
        add_d3d9_end_scene_event(on_d3d9_end_scene, EVENT_PRIORITY_BEFORE);
        add_d3d9_reset_event(on_d3d9_reset, EVENT_PRIORITY_BEFORE);
        add_tick_event(on_tick);
    }

    Handler::~Handler() noexcept {
        // Remove handler events
        remove_d3d9_end_scene_event(Handler::on_d3d9_end_scene);
        remove_d3d9_reset_event(on_d3d9_reset);
        remove_tick_event(on_tick);

        this->optics.clear();

        handler = nullptr;
    }

    void Handler::on_tick() noexcept {
        for(auto &optic : handler->optics) {
            auto &container = *optic.second;

            auto &audio_engines = container.audio_engines;
            auto it = audio_engines.begin();
            while(it != audio_engines.end()) {
                auto *instance = it->get();
                if(instance->getActiveVoiceCount() == 0 && !instance->queue.empty()) {
                    instance->play(*instance->queue.front());
                    instance->queue.pop();
                }
                it++;
            }
        }
    }

    void Handler::on_d3d9_end_scene(LPDIRECT3DDEVICE9 device) noexcept {
        for(auto &optic : handler->optics) {
            auto &container = *optic.second;

            // Load sprites
            if(!container.sprites_loaded) {
                for(auto &sprite : container.sprites) {
                    sprite.load(device);
                }
                container.sprites_loaded = true;
            }

            // Handle render queues
            auto &queues = container.render_queues;
            auto queue = queues.begin();
            while(queue != queues.end()) {
                auto &renders = queue->renders;
                auto &sprites_queue = queue->sprites_queue;
                auto max_renders = queue->max_renders;

                // Remove if is a temporal queue
                if(queue->temporal() && sprites_queue.empty() && renders.empty()) {
                    queue = queues.erase(queue);
                    continue;
                }

                // Get queue animations
                auto fade_in_anim = queue->get_fade_in_anim();
                auto fade_out_anim = queue->get_fade_out_anim();
                auto &slide_anim = queue->get_slide_anim();

                // Render sprite from queue
                if(!slide_anim.is_playing()) {
                    if(!sprites_queue.empty() && (max_renders == 0 || renders.size() < max_renders)) {
                        auto &render = queue->render_sprite_from_queue();

                        // Play fade-in animation in the new render
                        render.play_animation(fade_in_anim);

                        // Play slide animation
                        if(renders.size() > 1) {
                            slide_anim.play();
                        }
                    }
                }

                // Remove expired renders
                if(!renders.empty() && renders.front().get_timelife() > queue->get_render_duration()) {
                    renders.pop_front();
                }

                for(std::size_t i = 0; i < renders.size(); i++) {
                    auto &render = renders[i];
                    auto *sprite = render.get_sprite();
                    auto &render_state = render.get_state();
                    auto &active_animations = render.get_active_animations();
                    Sprite::State current_render_state = render.get_state();

                    // Apply slide animation
                    if(slide_anim.is_playing() && i != renders.size() - 1) {
                        slide_anim.apply_transform(current_render_state);

                        if(slide_anim.get_time_left() == 0) {
                            slide_anim.apply_transform(render_state);
                        }
                    }

                    // Apply render active animations
                    for(std::size_t i = 0; i < active_animations.size(); i++) {
                        auto &anim = active_animations[i];
                        anim.apply_transform(current_render_state);
                        
                        if(anim.get_time_left() == 0) {
                            anim.apply_transform(render_state);
                            active_animations.erase(active_animations.begin() + i);
                        }
                    }

                    // Play fade out animation
                    if(queue->get_render_duration() - render.get_timelife() < fade_out_anim.get_duration()) {
                        if(std::find(active_animations.begin(), active_animations.end(), fade_out_anim) == active_animations.end()) {
                            render.play_animation(fade_out_anim);
                        }
                    }

                    // Draw it!
                    sprite->draw(current_render_state);
                }
                
                // Stop slide animation
                if(slide_anim.get_time_left() == 0) {
                    slide_anim.stop();
                }

                // bump up iterator
                queue++;
            }
        }
    }

    void Handler::on_d3d9_reset(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS *) noexcept {
        for(auto &optic : handler->optics) {
            auto &container = *optic.second;
            for(auto &sprite : container.sprites) {
                sprite.unload();
            }
            container.sprites_loaded = false;
        }
    }
}