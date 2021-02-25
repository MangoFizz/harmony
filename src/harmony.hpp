// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HPP
#define HARMONY_HPP

#include <vector>
#include <memory>

struct lua_State;

namespace Harmony {
    class Signature;

    namespace Lua {
        class Library;
    }

    namespace Optic {
        class Handler;
    }

    namespace UserInterface {
        class WidescreenOverride;
    }

    /** Harmony class */
    class Harmony {
    public:
        /** 
         * Get a signature
         * @param name  Name of signature
         * @return      Reference to signature
         */
        Signature &get_signature(const char *name) noexcept;

        /**
         * Get Lua library handler
         */
        Lua::Library &get_lua_library_handler() noexcept;

        /**
         * Get optic handler
         */
        Optic::Handler &get_optic_handler() noexcept;

        /**
         * Get widescreen override handle
         */
        UserInterface::WidescreenOverride &get_widescreen_override_handle() noexcept;

        /**
         * Constructor for everything
         */
        Harmony();

    private:
        /** Harmony signatures */
        std::vector<Signature> signatures;

        /** Lua handler */
        std::unique_ptr<Lua::Library> lua_handler;

        /** Optic Handler */
        std::unique_ptr<Optic::Handler> optic_handler;

        /** Widescreen override */
        std::unique_ptr<UserInterface::WidescreenOverride> widescreen_fix_override;
    };

    /**
     * Get current Harmony instance
     * @return  Reference to Harmony instance
     */
    Harmony &get_harmony();
}

#endif
