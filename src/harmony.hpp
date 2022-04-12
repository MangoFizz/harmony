// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HPP
#define HARMONY_HPP

#include <vector>
#include <memory>

namespace Harmony {
    class Signature;

    namespace Lua {
        class Library;
    }

    namespace Optic {
        class Handler;
    }

    namespace Menu {
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
         * Look for a signature
         * @param name  Name of signature
         * @return      True if signature exists, false if not
         */
        bool signature_exists(const char *name) noexcept;

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
        Menu::WidescreenOverride &get_widescreen_override_handle() noexcept;

        /**
         * Constructor for everything
         */
        Harmony();

        /**
         * Get current Harmony instance
         * @return  Reference to Harmony instance
         */
        static Harmony &get();

    private:
        /** Harmony signatures */
        std::vector<Signature> signatures;

        /** Lua handler */
        std::unique_ptr<Lua::Library> lua_handler;

        /** Optic Handler */
        std::unique_ptr<Optic::Handler> optic_handler;

        /** Widescreen override */
        std::unique_ptr<Menu::WidescreenOverride> widescreen_fix_override;

        /** Instance pointer */
        static Harmony *instance;
    };
}

#endif
