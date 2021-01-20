// SPDX-License-Identifier: GPL-3.0-only

#ifndef CHIMERA_SIGNATURE_HPP
#define CHIMERA_SIGNATURE_HPP

#include <windows.h>
#include <string>
#include <vector>
#include <cstddef>

namespace Harmony {
    class Signature {
    private:
        /** Signature name */
        std::string name;

        /** Pointer to the signature data */
        std::byte *data;

        /** Original signature data */
        std::vector<std::byte> original_data;
    public:
        /**
         * Get the signature name
         */
        const char *get_name() const noexcept;

        /**
         * Get the signature data
         */
        std::byte *get_data() const noexcept;

        /**
         * Restore the signature original data
         */
        void restore() noexcept;

        /**
         * Constructor for Signature
         * @param name      Name for signature
         * @param signature Signature bytes
         * @param lenght    Number of bytes
         */
        Signature(const char *name, const short *signature, std::size_t lenght, std::uint16_t offset);

        /**
         * Find all the signatures
         * @return  Vector with all the signatures
         */
        static std::vector<Signature> find_signatures();
    };
}

#endif