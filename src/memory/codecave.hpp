// SPDX-License-Identifier: GPL-3.0-only

#ifndef CHIMERA_HOOK_HPP
#define CHIMERA_HOOK_HPP

#include <cstdint>

namespace Harmony {
    class Codecave {
    public:
        /** Hook data */
        unsigned char data[64];

        /** Data size */
        std::size_t data_size;

        /** Skip the original instruction */
        bool skip_og_code;

        /**
         * Write a call instruction
         * @param offset    Reference to data offset where the instruction will be written
         * @param function  Function that will be called
         * @param pushad    Insert pushad and pushfd instructions
         */
        void write_function_call(std::size_t &offset, void *function, bool pushad = true) noexcept;

        /**
         * Copy a given instruction to out codecave
         * @param offset        Reference to data offset where the instruction will be written
         * @param instruction   Pointer to the instruction
         * @param length        Length of the instruction
         */
        void copy_intruction(std::size_t &offset, void *instruction, std::size_t length) noexcept;

        /**
         * Write a cmp instruction that checks if the skip og code flag is set
         * @param offset    Reference to data offset where the instruction will be written
         * @param bytes     The amount of bytes to jump
         */
        void write_skip_code_check(std::size_t &offset, std::uint8_t bytes) noexcept;

        /**
         * Write a jump intruction to exit codecave
         * @param offset    Reference to data offset where the instruction will be written
         * @param address   Address to jump
         */
        void write_exit(std::size_t &offset, void *address) noexcept;
    
        /**
         * Write a hook jmp instruction
         * @param address   Pointer where the jump will be written
         * @param offset    Data offset to jump, 0 by default
         */
        void hook(void *address, std::size_t offset = 0) noexcept;

        /**
         * Write a basic hook over a call / jmp instruction
         * @param function  Function to be called in the hook
         * @param address   Pointer to the call/jmp instruction, nullptr by default
         * @param pushad    Insert pushad and pushfd instructions
         */
        void write_basic_hook(void *function, void *address, bool pushad = true) noexcept;

        /** 
         * Constructor for Hook
         * Enables code execution on the hook data memory
         */
        Codecave() noexcept;
    };

}

#endif