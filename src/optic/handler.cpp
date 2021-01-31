// SPDX-License-Identifier: GPL-3.0-only

#include <cmath>
#include "../events/d3d9_end_scene.hpp"
#include "../events/d3d9_reset.hpp"
#include "../events/tick.hpp"
#include "../events/multiplayer_sound.hpp"
#include "../messaging/console_output.hpp"
#include "../messaging/message_box.hpp"
#include "../harmony.hpp"
#include "handler.hpp"

namespace Harmony::Optic {
    static Handler *handler = nullptr;
    static void on_d3d9_end_scene(LPDIRECT3DDEVICE9 device) noexcept;

    std::map<std::string, RenderGroup> &Handler::get_render_groups() noexcept {
        return this->groups;
    }

    RenderGroup *Handler::get_render_group(const char *name) noexcept {
        if(this->groups.find(name) != this->groups.end()) {
            return &this->groups[name];
        }
        return nullptr;
    }

    RenderGroup &Handler::add_render_group(const char *name, Math::Point2D position, std::uint8_t opacity, Math::Angle rotation, RenderGroup::Align align, long render_duration) noexcept {
        if(this->groups.find(name) == this->groups.end()) {
            this->groups[name] = RenderGroup(position, opacity, rotation, align, render_duration);
            return this->groups[name];
        }
        message_box("Optic handler: Group %s already exists!", name);
        std::terminate();
    }

    void Handler::remove_render_group(std::string name) noexcept {
        this->groups.erase(name);
    }

    void Handler::render_sprite(Sprite *sprite, const char *group_name) noexcept {
        if(this->groups.find(group_name) != this->groups.end()) {
            this->groups[group_name].enqueue_sprite(sprite);
        }
    }

    void Handler::render_sprite(Sprite *sprite, Math::Point2D position, std::uint8_t opacity, Math::Angle rotation, RenderGroup::Align align, long duration, Animation fade_in, Animation fade_out) noexcept {
        auto tmp_name = "tmp" + std::to_string(rand());
        this->groups[tmp_name] = RenderGroup(position, opacity, rotation, align, duration, 0, true);
        auto &tmp_group = this->groups[tmp_name];
        tmp_group.set_fade_in_anim(fade_in);
        tmp_group.set_fade_out_anim(fade_out);
        tmp_group.enqueue_sprite(sprite);
    }

    Handler::Handler() noexcept {
        if(handler) {
            message_box("Error!\n\nMultiple Optic handler instances.");
            std::terminate();
        }

        handler = this;

        // Register end scene event
        add_d3d9_end_scene_event(on_d3d9_end_scene, EVENT_PRIORITY_BEFORE);
    }

    Handler::~Handler() noexcept {
        // Remove handler events
        remove_d3d9_end_scene_event(on_d3d9_end_scene);

        this->groups.clear();

        handler = nullptr;
    }

    static void on_d3d9_end_scene(LPDIRECT3DDEVICE9 device) noexcept {
        auto &groups = handler->get_render_groups();
        auto it = groups.begin();
        while(it != groups.end()) {
            auto group_name = it->first;
            auto &group = it->second;
            auto &renders = group.get_renders();
            auto &queue = group.get_sprites_queue();
            auto max_renders = group.get_maximum_renders();

            // Remove if is a temporal group
            if(group.single_render() && queue.empty() && renders.empty()) {
                it = groups.erase(it);
                continue;
            }

            // Get group animations
            auto fade_in_anim = group.get_fade_in_anim();
            auto fade_out_anim = group.get_fade_out_anim();
            auto &slide_anim = group.get_slide_anim();

            // Render sprite from queue
            if(!slide_anim.is_playing()) {
                if(!queue.empty() && (max_renders == 0 || renders.size() < max_renders)) {
                    auto &render = group.render_sprite_from_queue();

                    // Play fade-in animation in the new render
                    render.play_animation(fade_in_anim);

                    // Play slide animation
                    if(renders.size() > 1) {
                        slide_anim.play();
                    }
                }
            }

            // Remove expired renders
            if(!renders.empty() && renders.front().get_timelife() > group.get_render_duration()) {
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
                if(group.get_render_duration() - render.get_timelife() < fade_out_anim.get_duration()) {
                    if(std::find(active_animations.begin(), active_animations.end(), fade_out_anim) == active_animations.end()) {
                        render.play_animation(fade_out_anim);
                    }
                }

                // Draw it!
                sprite->load(device);
                sprite->draw(current_render_state.position, current_render_state.color);
            }
            
            // Stop slide animation
            if(slide_anim.get_time_left() == 0) {
                slide_anim.stop();
            }

            // bump up iterator
            it++;
        }
    }
}