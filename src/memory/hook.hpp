// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_MEMORY_HOOK_HPP
#define HARMONY_MEMORY_HOOK_HPP

#include <vector>
#include <memory>
#include <cstdint>
#include "codecave.hpp"

namespace Harmony::Memory {
    class Hook {
    public:
        /**
         * Hook it!
         */
        void hook() noexcept;

        /**
         * Release hook, restore original code
         */
        void release() noexcept;

        /**
         * Initialize basic hook.
         * @param instruction           Pointer to instruction to hook.
         * @param function_before       Function to be called before original code.
         * @param function_after        Function to be called after original code.
         * @param pushad                Insert pushad and pushfd instructions.
         */
        void initialize(void *instruction, const void *function_before, const void *function_after = nullptr, bool pushad = true) noexcept;

        /**
         * Basic hook constructor.
         * @param instruction           Pointer to instruction to hook.
         * @param function_before       Function to be called before original code.
         * @param function_after        Function to be called after original code.
         * @param pushad                Insert pushad and pushfd instructions.
         */
        Hook(void *instruction, const void *function_before, const void *function_after = nullptr, bool pushad = true) noexcept {
            initialize(instruction, function_before, function_after, pushad);
        }

        /**
         * Empty constructor.
         */
        Hook() {}

        /**
         * Destroy hook.
         */
        ~Hook() noexcept;

        /**
         * Calculate a 32-bit offset.
         * @param jmp           Address of the jmp instruction.
         * @param destination   Jump destination.
         */
        static std::uint32_t calculate_32bit_offset(const void *jmp, const void *destination) noexcept;

        /**
         * Follow a call/jmp instruction.
         * @param jmp   Pointer to the instruction.
         */
        static std::byte *follow_jump(std::byte *jmp) noexcept;

        /**
         * Follow a call/jmp instruction.
         * @param jmp   Pointer to the instruction.
         */
        static inline std::byte *follow_jump(void *jmp) noexcept {
            return follow_jump(reinterpret_cast<std::byte *>(jmp));
        }

        /** Hooked instruction */
        std::byte *instruction;
    protected: 
        /** Hook code */
        Codecave cave;

        /** Original code */
        std::vector<std::byte> original_code;

        /** Is this hooked? */
        bool hooked = false;

        /**
         * Write a function call instruction into cave.
         * @param function  Function to be called.
         * @param pushad    Insert pushad and pushfd instructions.
         */
        void write_function_call(const void *function, bool pushad = true) noexcept;

        /**
         * Copy assembly instructions into cave.
         * @param address           Address where the code to copy is.
         * @param instruction_size  Size of the copied instruction(s) in cave.
         */
        void copy_instructions(const void *address, std::uint8_t &instructions_size) noexcept;

        /**
         * Copy assembly instructions into cave.
         * @param address           Address where the code to copy is.
         */
        void copy_instructions(const void *address) noexcept;

        /**
         * Write cave return.
         * @param bytes     The amount of bytes to jump
         */
        void write_cave_return_jmp() noexcept;
    };

    class SwitchHook : public Hook {
    public:
        /**
         * Set whether or not to execute original code
        */
        void execute_original_code(bool setting) noexcept;

        /**
         * Initialize switch hook.
         * @param instruction   Pointer to instruction to hook.
         * @param function      Function to be called in the hook.
         * @param pushad        Insert pushad and pushfd instructions.
         */
        void initialize(void *instruction, const void *function, bool pushad = true) noexcept;

        /**
         * Switch hook constructor.
         * @param instruction   Pointer to instruction to hook.
         * @param function      Function to be called in the hook.
         * @param pushad        Insert pushad and pushfd instructions.
         */
        SwitchHook(void *instruction, const void *function, bool pushad = true) noexcept {
            initialize(instruction, function, pushad);
        }

        /**
         * Empty constructor.
         */
        SwitchHook() {}

        /**
         * Destroy hook.
         */
        ~SwitchHook() noexcept;

        protected:
        /** Skip the original instruction */
        std::unique_ptr<bool> execute_original_code_flag;
    };

    class FunctionOverride : public SwitchHook {
    public:
        /**
         * Initialize function override hook.
         * @param instruction   Pointer to instruction to hook.
         * @param function      Function to be called in the hook.
         * @param pushad        Insert pushad and pushfd instructions.
         */
        void initialize(void *instruction, const void *function, bool pushad = true) noexcept;

        /**
         * Function override hook constructor.
         * @param instruction   Pointer to instruction to hook.
         * @param function      Function to be called in the hook.
         * @param pushad        Insert pushad and pushfd instructions.
         */
        FunctionOverride(void *instruction, const void *function, bool pushad = true) noexcept {
            initialize(instruction, function, pushad);
        }

        /**
         * Empty constructor.
         */
        FunctionOverride() {}

        /**
         * Destroy hook.
         */
        ~FunctionOverride() noexcept;
    };

    class ChimeraFunctionOverride : public Hook {
    public:
        /**
         * Initialize Chimera's function-override override
         * @param cave          Pointer to Chimera's cave.
         * @param function      Function to be called in the hook.
         * @param cave_return   Return address for function.
         */
        void initialize(void *cave, const void *function, const void **cave_return) noexcept;

        /**
         * Constructor for Chimera's function-override override
         * @param cave          Pointer to Chimera's cave.
         * @param function      Function to be called in the hook.
         * @param cave_return   Return address for function.
         */
        ChimeraFunctionOverride(void *cave, const void *function, const void **cave_return) noexcept {
            initialize(cave, function, cave_return);
        }

        /**
         * Empty constructor.
         */
        ChimeraFunctionOverride() {}

        /**
         * Destroy hook.
         */
        ~ChimeraFunctionOverride() noexcept;
    };
}

#endif
