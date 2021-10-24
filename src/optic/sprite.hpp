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

        /**
         * @todo Move this to Render
         */
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
         * Get sprite name
         */
        std::string get_name() const noexcept;

        /**
         * Set sprite name
         * @param name  New name for sprite
         */
        void set_name(std::string name) noexcept;

        /**
         * Get sprite width
         */
        int get_width() const noexcept;

        /**
         * Get sprite height
         */
        int get_height() const noexcept;

        /**
         * Load sprite into device
         * @param device    Direct3D 9 device
         */
        void load(LPDIRECT3DDEVICE9 device);

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
         * @param name      Name of the sprite
         * @param texture   Texture path
         * @param width     Width of the sprite
         * @param height    Height of the sprite
         * @exception       If texture file does not exists
         */
        Sprite(std::string name, std::string texture, int width, int height);

        /**
         * Default constructor
         */
        Sprite() {}

        /**
         * Default destructor for sprite
         */
        ~Sprite() noexcept;

    private:
        /** Sprite name */
        std::string name;

        /** Path of texture sprite */
        std::filesystem::path texture_path;

        /** Sprite width */
        int width = 0;

        /** Sprite height */
        int height = 0;

        /** D3D9 texture of sprite */
        LPDIRECT3DTEXTURE9 texture;

        /** The sprite itself */
        LPD3DXSPRITE sprite;

        /** Is the sprite loaded? */
        bool loaded_flag = false;
    };
}

#endif
