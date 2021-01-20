// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HPP
#define HARMONY_HPP

#include <vector>
#include <memory>

struct lua_State;

namespace Harmony {
    class Signature;

    namespace Optic {
        class Handler;
    }

    namespace Lua {
        class Script;
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
         * Get optic handler
         */
        Optic::Handler &get_optic_handler() noexcept;

        /**
         * Get Lua scripts
         */
        std::vector<Lua::Script> &get_lua_scripts() noexcept;

        /**
         * Get script by name
         * @param name  Name of the script
         * @return      Reference to script
         */
        Lua::Script *get_lua_script(const char *name) noexcept;

        /**
         * Get script from state
         * @param state     Lua state
         * @return          Reference to script
         */
        Lua::Script *get_lua_script(lua_State *state) noexcept;

        /**
         * Constructor for everything
         */
        Harmony();

    private:
        /** Harmony signatures */
        std::vector<Signature> signatures;

        /** Optic Handler */
        std::unique_ptr<Optic::Handler> optic;

        /** Harmony Lua scripts */
        std::vector<Lua::Script> scripts;
    };

    /**
     * Get current Harmony instance
     * @return  Reference to Harmony instance
     */
    Harmony &get_harmony();
}

#endif
