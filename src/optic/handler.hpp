// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_OPTIC_HANDLER_HPP
#define HARMONY_OPTIC_HANDLER_HPP

#include <string>
#include <vector>
#include <map>
#include <d3dx9.h>
#include "sprite.hpp"
#include "animation.hpp"
#include "render.hpp"

namespace Harmony::Optic {
    class Handler {
    public:
        /**
         * Get optic groups
         * @return  A read-only reference to the groups array
         */
        std::map<std::string, RenderGroup> &get_render_groups() noexcept;

        /**
         * Get a render queue
         * @param name  Name/ID of the group
         * @return      Pointer to the group if exists, nullptr if not
         */
        RenderGroup *get_render_group(const char *name) noexcept;

        /**
         * Add a new render group
         * @param name              Name/ID of the group
         * @param position          Position of the group
         * @param opacity           Opacity of the elements
         * @param rotation          Rotation angle of the queue
         * @param align             Align of the queue
         * @param render_duration   Duration of the medals in milliseconds
         * @return                  True on success, false if the group already exists
         */
        RenderGroup &add_render_group(const char *name, Math::Point2D position, std::uint8_t opacity, Math::Angle rotation, RenderGroup::Align align, long render_duration) noexcept;

        /**
         * Remove an existing optic group
         * @param name  Name of the group
         */
        void remove_render_group(std::string name) noexcept;

        /**
         * Render a sprite
         * @param sprite        Sprite to render
         * @param group_name    Render group when the sprite will be rendered
         */
        void render_sprite(Sprite *sprite, const char *group_name) noexcept;

        /**
         * Render a sprite
         * @param sprite    Sprite to render
         * @param position  Position of the render
         * @param rotation  Render rotation in degrees
         * @param fade_in   Fade-in animation
         * @param fade_out  Fade-out animation
         */
        void render_sprite(Sprite *sprite, Math::Point2D position, std::uint8_t opacity, Math::Angle rotation, RenderGroup::Align align, long duration, Animation fade_in, Animation fade_out) noexcept;

        /**
         * Default constructor
         */
        Handler() noexcept;

        /**
         * Default destructor
         */
        ~Handler() noexcept;

        /**
         * D3D9 end scene callback
         */
        static void on_d3d9_end_scene(LPDIRECT3DDEVICE9 device) noexcept;

    private:
        /** Render group */
        std::map<std::string, RenderGroup> groups;
    };
}

#endif
