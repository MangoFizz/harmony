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
    static void on_d3d9_reset(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS *) noexcept;

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

    void Handler::remove_render_group(const char *name) noexcept {
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

        // Register events
        add_d3d9_end_scene_event(on_d3d9_end_scene);
        add_d3d9_reset_event(on_d3d9_reset);
    }

    Handler::~Handler() noexcept {
        // Remove handler events
        remove_d3d9_end_scene_event(on_d3d9_end_scene);
        remove_d3d9_reset_event(on_d3d9_reset);

        this->groups.clear();

        handler = nullptr;
    }

    static void on_d3d9_end_scene(LPDIRECT3DDEVICE9 device) noexcept {
        for(auto &elem : handler->get_render_groups()) {
            auto group_name = elem.first;
            auto &group = elem.second;
            auto &renders = group.get_renders();
            auto &queue = group.get_sprites_queue();
            auto maximum_renders = group.get_maximum_renders();

            // Remove if is a temporal group
            if(group.single_render() && queue.empty() && renders.empty()) {
                handler->remove_render_group(group_name.c_str());
                continue;
            }

            // Get group animations
            auto fade_in_anim = group.get_fade_in_anim();
            auto fade_out_anim = group.get_fade_out_anim();
            auto &slide_anim = group.get_slide_anim();

            if(!slide_anim.is_playing()) {
                // Render sprite from queue
                if(!queue.empty() && (maximum_renders == 0 || renders.size() < maximum_renders)) {
                    auto &render = group.render_sprite_from_queue();
                    render.play_animation(fade_in_anim);
                    if(renders.size() > 1) {
                        slide_anim.play();
                    }
                }
            }

            if(!renders.empty() && renders.front().get_timelife() > group.get_render_duration()) {
                //renders.pop_front();
                renders.erase(renders.begin());
            }

            for(std::size_t i = 0; i < renders.size(); i++) {
                auto &render = renders[i];
                auto *sprite = render.get_sprite();
                auto &render_state = render.get_state();
                auto &active_animations = render.get_active_animations();
                Sprite::State current_render_state = render.get_state();

                // Slide animation
                if(slide_anim.is_playing() && i != renders.size() - 1) {
                    slide_anim.apply_transform(current_render_state);

                    if(slide_anim.get_time_left() == 0) {
                        slide_anim.apply_transform(render_state);
                    }
                }

                // Apply active animations
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
            
            if(slide_anim.get_time_left() == 0) {
                slide_anim.stop();
            }
        }
    }

    static void on_d3d9_reset(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS *) noexcept {
        for(auto &element : handler->get_render_groups()) {
            for(auto &render : element.second.get_renders()) {
                auto *sprite = render.get_sprite();
                sprite->unload();
            }
        }
    }

    #ifndef DEBUG
    #define DEBUG
    #endif

    #ifdef DEBUG
    static bool hitmarker_dspatcher(HaloData::MultiplayerSound sound) noexcept {
        if(sound != HaloData::MultiplayerSound::TING) {
            return true;
        }
        
        auto &harmony = get_harmony();
        auto &optic = harmony.get_optic_handler();
        
        static auto hitmarker = Sprite("C:\\Users\\xjerr\\Documents\\My Games\\Halo CE\\chimera\\lua\\data\\global\\optic_test\\images\\default.png", 35, 35);
        static auto sandia = Sprite("C:\\Users\\xjerr\\Documents\\My Games\\Halo CE\\chimera\\lua\\data\\global\\optic_test\\images\\sandia.jpg", 50, 50);  
        
        auto flat = Animation();
        auto fade_in_transform = Animation::StateTransform();
        flat.set_transform(fade_in_transform);
        flat.set_duration(200);
        flat.add_target(Animation::TARGET_POSITION_X, Animation::ease_in());
        
        optic.render_sprite(&sandia, "sandia");
        optic.render_sprite(&hitmarker, {622.5f, 342.5f}, 255, 0, RenderGroup::ALIGN_LEFT, 200, flat, flat);
        return true;
    }

    void set_up_optic_test() noexcept {
        auto &harmony = get_harmony();
        auto &optic = harmony.get_optic_handler();
        auto &sandia_group = optic.add_render_group("sandia", {50.0f, 400.0f}, 255, 0, RenderGroup::ALIGN_LEFT, 5000);

        auto fade_in = Animation();
        auto fade_in_transform = Animation::StateTransform();
        fade_in_transform.opacity = 255;
        fade_in_transform.position.y = -60.0f;
        fade_in.set_transform(fade_in_transform);
        fade_in.set_duration(200);
        fade_in.add_target(Animation::TARGET_POSITION_Y, Animation::ease_in());
        fade_in.add_target(Animation::TARGET_OPACITY, Animation::ease_in());

        auto fade_out = Animation();
        auto fade_out_transform = Animation::StateTransform();
        fade_out_transform.opacity = -255;
        fade_out.set_transform(fade_out_transform);
        fade_out.set_duration(200);
        fade_out.add_target(Animation::TARGET_OPACITY, Animation::ease_in());

        auto slide = Animation();
        auto slide_transform = Animation::StateTransform();
        slide_transform.position.x = 60;
        slide.set_transform(slide_transform);
        slide.set_duration(300);
        slide.add_target(Animation::TARGET_POSITION_X, Animation::ease_in_out());

        sandia_group.set_fade_in_anim(fade_in);
        sandia_group.set_fade_out_anim(fade_out);
        sandia_group.set_slide_anim(slide);

        add_multiplayer_sound_event(hitmarker_dspatcher);
    }
    #endif
}