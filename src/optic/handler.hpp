// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_OPTIC_HANDLER_HPP
#define HARMONY_OPTIC_HANDLER_HPP

#include <string>
#include <map>
#include <d3dx9.h>
#include "animation.hpp"
#include "store.hpp"
#include "sprite.hpp"
#include "render.hpp"

namespace Harmony::Optic {
    class Handler {
    public:
        /**
         * Get a render queue
         * @param name  Name of the group
         * @return      Pointer to the group if exists, nullptr if not
         */
        Store *get_optic(std::string name) noexcept;

        /**
         * Create container for optic
         * @param name  Name for the container
         * @exception   If optic container already exists
         */
        Store *create_optic(std::string name);

        /**
         * Remove optic container
         * @param name  Name of the container
         * @exception   If the optic container does not exists
         */
        void remove_optic(std::string name);

        /**
         * Default constructor
         */
        Handler();

        /**
         * Default destructor
         */
        ~Handler() noexcept;

        /**
         * D3D9 callbacks
         */
        static void on_d3d9_end_scene(LPDIRECT3DDEVICE9 device) noexcept;
        static void on_d3d9_reset(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS *) noexcept;
        static void on_tick() noexcept;

    private:
        /** Render group */
        std::map<std::string, std::unique_ptr<Store>> optics;
    };
}

#endif
