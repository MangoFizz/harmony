// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_OPTIC_SPRITE_HPP
#define HARMONY_OPTIC_SPRITE_HPP

#include <filesystem>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include "../math/color.hpp"
#include "../math/geometry.hpp"
#include "sound.hpp"

namespace Harmony::Optic {

    class Sprite {
    public:
        struct Scale {
            float x;
            float y;
        };

        struct State {
            Math::Point2D position;
            Scale scale;
            Math::ColorARGB color;
            float rotation;

            State() {
                position = {0.0f, 0.0f};
                scale = {1.0f, 1.0f};
                color = {255, 255, 255, 255};
                rotation = 0;
            }
        };

        /**
         * Get sprite width
         */
        int get_width() const noexcept;

        /**
         * Get sprite height
         */
        int get_height() const noexcept;

        /**
         * Get sprite sound
         */
        Sound *get_sound() const noexcept;

        /**
         * Set sprite sound
         * @param sound     The sound itself
         */
        void set_sound(Sound &sound) noexcept;

        /**
         * Set sprite sound
         * @param sound     Pointer to sound
         */
        void set_sound(Sound *sound) noexcept;

        /**
         * Load sprite into device
         * @param device    Direct3D 9 device
         */
        void load(LPDIRECT3DDEVICE9 device) noexcept;

        /**
         * Release sprite
         */
        void unload() noexcept;

        /**
         * Draw sprite
         * @param sprite_state  State of sprite
         */
        void draw(State const &sprite_state) const noexcept;

        /**
         * Default constructor for sprite
         * @param texture   Path of the texture
         * @param size      Texture dimentions
         */
        Sprite(const char *texture, int width, int height) noexcept;

        /**
         * Default constructor
         */
        Sprite() {}

        /**
         * Default destructor for sprite
         */
        ~Sprite() noexcept;

    private:
        /** Path of texture sprite */
        std::filesystem::path texture_path;

        /** Sprite width */
        int width = 0;

        /** Sprite height */
        int height = 0;

        /** Sprite sound */
        Sound *sound = nullptr;

        /** D3D9 texture of sprite */
        LPDIRECT3DTEXTURE9 texture;

        /** The sprite itself */
        LPD3DXSPRITE sprite;

        /** Is the sprite loaded? */
        bool loaded = false;
    };
}

#endif
