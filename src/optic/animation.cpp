// SPDX-License-Identifier: GPL-3.0-only

#include <string>
#include "../messaging/console_output.hpp"
#include "animation.hpp"

namespace Harmony::Optic {
    long Animation::get_duration() const noexcept {
        return this->duration;
    }

    void Animation::set_duration(long new_value) noexcept {
        this->duration = new_value;
    }

    Animation::StateTransform Animation::get_transform() const noexcept {
        return this->render_state_transform;
    }

    void Animation::set_transform(StateTransform new_value) noexcept {
        this->render_state_transform = new_value;
    }

    void Animation::add_target(Target target, Math::QuadraticBezier curve) noexcept {
        if(target == TARGET_INVALID) {
            return;
        }
        this->curves[target] = curve;
    }

    void Animation::play() noexcept {
        if(!this->playing && this->duration > 0) {
            this->start_time = std::chrono::steady_clock::now();
            this->playing = true;
        }
    }

    void Animation::stop() noexcept {
        this->playing = false;
    }

    bool Animation::is_playing() const noexcept {
        return this->playing;
    }

    void Animation::apply_transform(Sprite::State &state) noexcept {
        auto now = std::chrono::steady_clock::now();
        long timelife = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->start_time).count();
        float t = static_cast<float>(timelife) / this->duration;

        // Fool proof
        if(t > 1) {
            t = 1;
        }

        for(auto &elem : this->curves) {
            auto target = elem.first;
            auto &curve = elem.second;

            switch(target) {
                case TARGET_POSITION_X:
                    state.position.x += this->render_state_transform.position.x * curve.get_point(t).y;
                    break;
                case TARGET_POSITION_Y:
                    state.position.y += this->render_state_transform.position.y * curve.get_point(t).y;
                    break;
                case TARGET_OPACITY:
                    state.color.a += this->render_state_transform.opacity * curve.get_point(t).y;
                    break;
                case TARGET_ROTATION:
                    state.rotation += this->render_state_transform.rotation * curve.get_point(t).y;
                    break;
                default:
                    break;
            }
        }
    }

    long Animation::get_time_left() noexcept {
        if(!this->playing) {
            return 0;
        }
        auto now = std::chrono::steady_clock::now();
        auto timelife = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->start_time).count();
        long timeleft = this->duration - timelife;
        if(timeleft < 0) {
            timeleft = 0;
        }
        return timeleft;
    }

    const char *Animation::get_tag() const noexcept {
        return this->tag.c_str();
    }

    void Animation::set_tag(const char *new_tag) noexcept {
        this->tag = new_tag;
    }

    Animation::Animation(StateTransform transformation, long duration) noexcept {
        this->render_state_transform = transformation;
        this->duration = duration;
        this->set_up_default_animation();
    }

    Animation::~Animation() noexcept {
        this->curves.clear();
    }

    void Animation::set_up_default_animation() noexcept {
        for(int target; target < TARGET_INVALID; target++) {
            this->add_target(static_cast<Animation::Target>(target), Animation::flat());
        }
    }

    Math::QuadraticBezier Animation::flat() noexcept {
        return Math::QuadraticBezier({0.0f, 0.0f}, {0.0f, 0.0f});
    }

    Math::QuadraticBezier Animation::linear() noexcept {
        return Math::QuadraticBezier({0.0f, 0.0f}, {1.0f, 1.0f});
    }

    Math::QuadraticBezier Animation::ease_in() noexcept {
        return Math::QuadraticBezier({0.4f, 0.0f}, {1.0f, 1.0f});
    }

    Math::QuadraticBezier Animation::ease_out() noexcept {
        return Math::QuadraticBezier({0.0f, 0.0f}, {0.6f, 1.0f});
    }

    Math::QuadraticBezier Animation::ease_in_out() noexcept {
        return Math::QuadraticBezier({0.4f, 0.0f}, {0.6f, 1.0f});
    }

    Animation::Target Animation::get_target_from_string(const char *target_name) noexcept {
        std::string target_str = target_name;
        if(target_str == "position x") {
            return TARGET_POSITION_X;
        }
        else if(target_str == "position y") {
            return TARGET_POSITION_Y;
        }
        else if(target_str == "rotation") {
            return TARGET_ROTATION;
        }
        else if(target_str == "opacity") {
            return TARGET_OPACITY;
        }
        else {
            return TARGET_INVALID;
        }
    }
}
