// SPDX-License-Identifier: GPL-3.0-only

#ifndef CHIMERA_HOOK_HPP
#define CHIMERA_HOOK_HPP

#include <vector>
#include <cstdint>

#define CALL_INSTRUCTION_SIZE 0x5

namespace Harmony {
    class Codecave {
    public:
        /**
         * Set whether or not to execute original code
        */
        void execute_original_code(bool setting) noexcept;

        /**
         * Write a basic cave. This cave can skip the original function.
         * @param address   Pointer to instruction
         * @param function  Function to be called in the cave
         * @param pushad    Insert pushad and pushfd instructions
         */
        void write_basic_cave(void *address, const void *function, bool pushad = true) noexcept;

        /**
         * Write a double-call cave
         * @param address           Pointer to instruction
         * @param function_before   Function to be called BEFORE original code
         * @param function_after    Function to be called AFTER original code
         * @param pushad            Insert pushad and pushfd instructions
         */
        void write_function_call(void *address, const void *function_before, const void *function_after, bool pushad = true);

        /**
         * Write an override for a Chimera's override cave
         * @param address   Pointer to instruction
         */
        void hack_chimera_function_override(void *address, const void *function, const void **cave_return) noexcept;

        /**
         * Write a cave over a Chimera cave
         * @param address   Pointer to Chimera cave jump
         * @param function_before   Function to be called BEFORE original code
         * @param function_after    Function to be called AFTER original code
         * @param pushad            Insert pushad and pushfd instructions
         */
        void hack_chimera_function_call(void *address, const void *function_before, const void *function_after, bool pushad = true) noexcept;

        /**
         * Hook it!
         */
        void hook() noexcept;

        /**
         * Release hook, restore original code
         */
        void release() noexcept;

        /**
         * Allocate memory for our cave
         */
        Codecave() noexcept;

        /**
         * Free cave memory
         */
        ~Codecave() noexcept;

        /**
         * Calculate offset
         * @param instruction       Instruction address
         * @param address           Address where jump
         */
        static std::uint32_t calculate_jmp_offset(const void *jmp, const void *destination) noexcept;

        /**
         * Follow a call/jmp instruction
         * @param jmp   Pointer to instruction
         */
        static std::byte *follow_jump(std::byte *jmp) noexcept;

        /**
         * Follow a call/jmp instruction
         * @param jmp   Pointer to instruction
         */
        static inline std::byte *follow_jump(void *jmp) noexcept {
            return follow_jump(reinterpret_cast<std::byte *>(jmp));
        }

    private: 
        /** Instruction to hook */
        std::byte *instruction;

        /** Cave itself */
        std::byte *cave;

        /** Cave size */
        std::size_t size = 0;

        /** Skip the original instruction */
        bool execute_original_code_flag = true;

        /** State */
        bool hooked = false;

        /** Original instruction */
        std::vector<std::byte> original_instruction;

        /** Cave original protection */
        unsigned long original_page_protection;

        /**
         * Set cave as executable
         */
        void set_access_protection(bool setting = true) noexcept;

        /**
         * Write a function call instruction
         * @param function  Function to be called
         * @param pushad    Insert pushad and pushfd instructions
         */
        void write_function_call(const void *function, bool pushad = true) noexcept;

        /**
         * Copy a code instruction from a given address
         * @param address   Instruction address
         */
        void copy_instruction(const void *address, std::uint8_t &instruction_size) noexcept;

        /**
         * Write cave return
         * @param bytes     The amount of bytes to jump
         */
        void write_cave_return() noexcept;

        /**
         * Insert a byte into the cave
         * @param byte  Byte to insert
         */
        template<typename T> inline void insert(T byte) noexcept {
            cave[size] = static_cast<std::byte>(byte);
            size++;
        }

        /**
         * Insert byte array into cave
         * @param bytes     Pointer to byte array
         * @param lenght    Size of array
         */
        template<typename T> inline void insert(T *bytes, std::size_t lenght) noexcept {
            for(std::size_t i = 0; i < lenght; i++, size++) {
                cave[size] = reinterpret_cast<const std::byte *>(bytes)[i];
            }
        }

        /**
         * Insert an address into cave
         * @param address   Address to insert
         */
        inline void insert_address(std::uint32_t address) noexcept {
            *reinterpret_cast<std::uint32_t *>(&cave[size]) = address;
            size += 4;
        }
    };

}

#endif