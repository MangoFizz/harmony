// SPDX-License-Identifier: GPL-3.0-only

#include "../messaging/message_box.hpp"
#include "render.hpp"

namespace Harmony::Optic {
    void Render::play_animation(Animation anim) noexcept {
        anim.play();
        this->active_animations.push_back(anim);
    }

    void Render::play_animation(Animation anim, Animation::StateTransform transformation, long duration) noexcept {
        anim.set_transform(transformation);
        anim.set_duration(duration);
        anim.play();
        this->active_animations.push_back(anim);
    }

    Sprite *Render::get_sprite() noexcept {
        return this->sprite;
    }

    Sprite::State &Render::get_state() noexcept {
        return this->sprite_state;
    }

    std::vector<Animation> &Render::get_active_animations() noexcept {
        return this->active_animations;
    }

    long Render::get_timelife() const noexcept {
        auto now = std::chrono::steady_clock::now();
        auto timelife = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->timestamp);
        return timelife.count();
    }

    Render::Render(Sprite *sprite, Sprite::State state) noexcept {
        this->sprite = sprite;
        this->sprite_state = state;
        this->timestamp = std::chrono::steady_clock::now();
    }

    Sprite::State RenderGroup::get_sprite_initial_state() noexcept {
        return this->initial_render_state;
    }

    float RenderGroup::get_direction() const noexcept {
        return this->direction;
    }

    std::size_t RenderGroup::get_maximum_renders() const noexcept {
        return this->max_renders;
    }

    long RenderGroup::get_render_duration() const noexcept {
        return this->render_duration;
    }

    void RenderGroup::set_render_duration(long duration) noexcept {
        this->render_duration = duration;
    }

    Animation RenderGroup::get_fade_in_anim() const noexcept {
        return this->fade_in_anim;
    }

    void RenderGroup::set_fade_in_anim(Animation anim) noexcept {
        this->fade_in_anim = anim;
    }

    Animation RenderGroup::get_fade_out_anim() const noexcept {
        return this->fade_out_anim;
    }

    void RenderGroup::set_fade_out_anim(Animation anim) noexcept {
        this->fade_out_anim = anim;
    }

    Animation &RenderGroup::get_slide_anim() noexcept {
        return this->slide_anim;
    }

    void RenderGroup::set_slide_anim(Animation anim) noexcept {
        this->slide_anim = anim;
    }

    std::deque<Render> &RenderGroup::get_renders() noexcept {
        return this->renders;
    }

    std::queue<Sprite *> const &RenderGroup::get_sprites_queue() const noexcept {
        return this->queue;
    }

    void RenderGroup::enqueue_sprite(Sprite *sprite) noexcept {
        this->queue.push(sprite);
    }

    Render &RenderGroup::render_sprite_from_queue() noexcept {
        auto initial_state = this->get_sprite_initial_state();
        auto transform = this->fade_in_anim.get_transform();
        initial_state.position.x -= transform.position.x;
        initial_state.position.y -= transform.position.y;
        initial_state.color.a -= transform.opacity;
        initial_state.rotation -= transform.rotation;

        this->renders.push_back({this->queue.front(), initial_state});
        this->queue.pop();

        return this->renders.back();
    }

    void RenderGroup::pop_render() noexcept {
        this->renders.pop_front();
    }

    bool RenderGroup::single_render() noexcept {
        return this->single_render_group;
    }

    RenderGroup::RenderGroup(Sprite::State initial_render_state, float direction, std::size_t maximum_renders, long render_duration, bool single_render) noexcept {
        this->initial_render_state = initial_render_state;
        this->direction = direction;
        this->max_renders = maximum_renders;
        this->render_duration = render_duration;
        this->single_render_group = single_render;
    }
}
