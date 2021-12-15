// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_OPTIC_CONTAINER_HPP
#define HARMONY_OPTIC_CONTAINER_HPP

#include <string>
#include <vector>
#include <filesystem>
#include "animation.hpp"
#include "render.hpp"
#include "sprite.hpp"

namespace Harmony::Optic {    
    class Container {
    friend class Handler;
    public:
        /**
         * Get an animation
         * @param name      Name or the animation
         * @return  Pointer to animation, null if animation does not exist
         */
        Animation *get_animation(std::string name) noexcept;
        
        /**
         * Register animation
         * @param name      Name of the animation
         * @param duration  Duration in milliseconds
         * @exception       If animation already exists
         */
        void create_animation(std::string name, long duration);

        /**
         * Remove an animation
         * @param name  Name of the animation
         * @exception   If animation does not exists
         */
        void remove_animation(std::string name);

        /**
         * Get a sound
         * @return  Pointer to sound, null if sound does not exist
         */
        Sound *get_sound(std::string name) noexcept;
        
        /**
         * Register sound
         * @param name              Name of the sound
         * @param sound_path        Path to sound file
         * @exception               If sound already exists
         * @exception               If sound file does not exists
         */
        void create_sound(std::string name, std::filesystem::path sound_path);

        /**
         * Remove a sound
         * @param name  Name of the sound
         * @exception   If sound does not exists
         */
        void remove_sound(std::string name);

        /**
         * Get a sprite
         * @param name      Name or the sprite
         * @return  Pointer to sprite, null if does not exist
         */
        Sprite *get_sprite(std::string name) noexcept;

        /**
         * Add a sprite
         * @param name      Name or the sprite
         * @param texture   Texture path
         * @param width     Width of the sprite
         * @param height    Height of the sprite
         * @exception       If sprite already exists
         * @exception       If texture file does not exists
         */
        void create_sprite(std::string name, std::string texture, int width, int height);

        /**
         * Remove a sprite
         * @param name  Name of the sprite
         * @exception   If sprite does not exists
         */
        void remove_sprite(std::string name);

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
         * Get a render queue
         * @param name      Name or the render queue
         * @return  Pointer to render queue, null if does not exist
         */
        RenderQueue *get_render_queue(std::string name) noexcept;

        /**
         * Create render queue
         * @param name                      Name of the queue
         * @param initial_render_state      Initial state for rendered sprites
         * @param rotation                  Rotation of sprites in degrees
         * @param maximum_renders           Number of simultaneous renderings
         * @param render_duration           Duration of the renders
         * @param temporal                  If true, the queue will be removed after last render timelife ends
         * @exception                       If queue already exists
         */
        void create_render_queue(std::string name, Sprite::State initial_render_state, float rotation, std::size_t maximum_renders, long render_duration, bool temporal = false);

        /**
         * Remove queue
         * @param name  Name of the queue
         * @exception   If queue does not exists
         */
        void remove_queue(std::string name);

        /**
         * Render a sprite
         * @param sprite_name       Name of the sprite to render
         * @param render_queue      Render queue where the sprite will be rendered
         * @exception               If sprite does not exists
         * @exception               If render queue does not exists
         */
        void render_sprite(std::string sprite_name, std::string render_queue);

        /**
         * Render a sprite
         * @param sprite_name   Sprite to render
         * @param position      Position of the render
         * @param rotation      Render rotation in degrees
         * @param fade_in       Fade-in animation
         * @param fade_out      Fade-out animation
         * @exception           If sprite does not exists
         */
        void render_sprite(std::string sprite_name, Sprite::State initial_state, long duration, Animation fade_in, Animation fade_out);

        /**
         * Get audio engine instance
         * @param name  Name of the instance
         * @return      Pointer to audio engine instance, null if does not exist
         */
        AudioEngine *get_audio_engine(std::string name) noexcept;

        /**
         * Create audio engine instance
         * @param name  Name of the instance
         * @exception   If instance already exists
         */
        void create_audio_engine(std::string name);

        /**
         * Remove audio engine instance
         * @param name  Name of the instance
         * @exception   If the instance does not exists
         */
        void remove_audio_engine(std::string name);

        /**
         * Play sound
         * @param sound_name        Name of the sound
         * @param instance_name     Name of playback queue
         * @param no_enqueue        Play sound immediately
         * @exception               If sound does not exists
         * @exception               If playback queue does not exists
         */
        void play_sound(std::string sound_name, std::string instance_name, bool no_enqueue);

        /**
         * Void constructor
         */
        Container() {};

        /**
         * Destructor
         */
        ~Container() noexcept;

    private:
        /** Animations */
        std::vector<Animation> animations;

        /** Sprites */
        std::vector<Sprite> sprites;

        /** Are sprites loaded? */
        bool sprites_loaded = false;

        /** Render queue */
        std::vector<RenderQueue> render_queues;

        /** Sounds */
        std::vector<std::unique_ptr<Sound>> sounds;

        /** Audio engine instances */
        std::vector<std::unique_ptr<AudioEngine>> audio_engines;
    };
}

#endif
