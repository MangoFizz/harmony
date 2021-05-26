// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_LUA_OPTIC_STORE_HPP
#define HARMONY_LUA_OPTIC_STORE_HPP

#include <string>
#include <vector>
#include <map>
#include "../optic/animation.hpp"
#include "../optic/render.hpp"
#include "../optic/sprite.hpp"

namespace Harmony::Lua {    
    class OpticStore {
    public:
        /**
         * Get an animation
         * @return  Pointer to animation, null if animation does not exist
         */
        Optic::Animation *get_animation(std::string name) noexcept;
        
        /**
         * Register animation
         * @param name  Name or ID of animation
         * @param anim  The animation itself
         */
        void add_animation(std::string name, Optic::Animation anim) noexcept;

        /**
         * Remove an animation
         * @param name  Name or ID of animation
         */
        void remove_animation(std::string name) noexcept;

        /**
         * Get a sprite
         * @return  Pointer to sprite, null if does not exist
         */
        Optic::Sprite *get_sprite(std::string name) noexcept;

        /**
         * Add a sprite
         * @param name      Name or ID of the sprite
         * @param sprite    The sprite itself
         */
        void add_sprite(std::string name, Optic::Sprite sprite) noexcept;

        /**
         * Remove a sprite
         */
        void remove_sprite(std::string name) noexcept;

        /**
         * Load sprites into D3D9 device
         * @param device    D3D9 device from Halo CE
         */
        void load_sprites(LPDIRECT3DDEVICE9 device) noexcept;

        /**
         * Release sprites from D3D9 device
         */
        void release_sprites() noexcept;

        /**
         * Get a sound
         * @return  Pointer to sound, null if does not exist
         */
        Optic::Sound *get_sprite_sound(std::string name) noexcept;

        /**
         * Add a sound
         * @param name      Name or ID of the sound
         * @param sprite    The sound itself
         */
        void add_sprite_sound(std::string name, Optic::Sound sound) noexcept;

        /**
         * Remove a sound
         */
        void remove_sprite_sound(std::string name) noexcept;

        /**
         * Create render group
         * @param name
         */
        void register_group(std::string name) noexcept;

        /**
         * Remove group
         * @param name  Name of the group
         */
        void remove_group(std::string name) noexcept;

        /**
         * Remove script optic groups
         */
        void remove_groups() noexcept;

        /**
         * Void constructor
         */
        OpticStore() {}

        /**
         * Destructor
         */
        ~OpticStore() noexcept;

    private:
        /** Animations */
        std::map<std::string, Optic::Animation> animations;

        /** Sprites */
        std::map<std::string, Optic::Sprite> sprites;

        /** Sprite playbacks */
        std::map<std::string, Optic::Sound> sounds;

        /** Groups */
        std::vector<std::string> groups;
    };
}

#endif
