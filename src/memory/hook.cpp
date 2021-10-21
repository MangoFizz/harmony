// SPDX-License-Identifier: GPL-3.0-only

#include <memory>
#include <windows.h>
#include "../messaging/message_box.hpp"
#include "memory.hpp"
#include "hook.hpp"

namespace Harmony::Memory {
    
    void Hook::hook() noexcept {
        if(!this->cave.empty() && this->hooked) {
            return;
        }
        this->hooked = true;

        // Change access protection in cave
        this->cave.set_access_protection();

        // Kill original code
        for(std::size_t i = 0; i < this->original_code.size(); i++) {
            overwrite(this->instruction + i, static_cast<std::byte>(0x90));
        }

        // Write hook
        overwrite(this->instruction, static_cast<std::byte>(0xE9));
        overwrite(this->instruction + 1, this->calculate_32bit_offset(this->instruction, &this->cave.data[0]));
    }

    void Hook::release() noexcept {
        if(!this->hooked) {
            return;
        }

        // Restore original instruction
        overwrite(this->instruction, this->original_code.data(), this->original_code.size());

        // Restore state
        this->cave.set_access_protection(false);
        this->hooked = false;
    }

    void Hook::initialize(void *instruction, const void *function_before, const void *function_after, bool pushad) noexcept {
        if(this->hooked) {
            return;
        }

        // Set instruction
        this->instruction = reinterpret_cast<std::byte *>(instruction);

        // Write function before
        if(function_before) {
            this->write_function_call(function_before, pushad);
        }

        // Copy instructions
        this->copy_instructions(instruction);

        // Write function after
        if(function_after) {
            this->write_function_call(function_after, pushad);
        }

        // write return jump
        this->write_cave_return_jmp();
    }

    Hook::~Hook() noexcept {
        this->release();
    }

    std::uint32_t Hook::calculate_32bit_offset(const void *jmp, const void *destination) noexcept {
        auto offset = reinterpret_cast<std::uint32_t>(destination) - (reinterpret_cast<std::uint32_t>(jmp) + 5);
        return offset;
    }

    std::byte *Hook::follow_jump(std::byte *jmp) noexcept {
        auto jmp_offset = *reinterpret_cast<std::uint32_t *>(jmp + 1);
        auto jmp_end = reinterpret_cast<std::uint32_t>(jmp + 5);
        auto *destination = reinterpret_cast<std::byte *>(jmp_offset + jmp_end);
        return destination;
    }

    void Hook::write_function_call(const void *function, bool pushad) noexcept {
        if(pushad) {
            this->cave.insert(0x9C); // pushfd
            this->cave.insert(0x60); // pushad
        }

        this->cave.insert(0xE8); // call
        auto fn_offset = this->calculate_32bit_offset(reinterpret_cast<const void *>(&this->cave.get_top()), function);
        this->cave.insert_address(fn_offset);

        if(pushad) {
            this->cave.insert(0x61); // popad
            this->cave.insert(0x9D); // popfd
        }
    }

    void Hook::copy_instructions(const void *address, std::uint8_t &copied_bytes) noexcept {
        auto *instruction = reinterpret_cast<const std::uint8_t *>(address);
        std::size_t instruction_size = 0;

        copied_bytes = 0;

        while(copied_bytes < 5) {
            instruction += instruction_size;

            switch(instruction[0]) {
                // call rel32
                case 0xE8: 
                // jmp rel32
                case 0xE9: {
                    this->cave.insert(instruction[0]); // call or jmp

                    // offset
                    auto original_offset = *reinterpret_cast<const std::uint32_t *>(&instruction[1]);
                    auto offset = original_offset + this->calculate_32bit_offset(&this->cave.get_top(), &instruction[5]);
                    this->cave.insert_address(offset);
                    
                    instruction_size = 5;
                    break;
                }

                // mov r/m8, imm8
                case 0xC6: {
                    this->cave.insert(0xC6);

                    // mov [esp + disp8], imm8
                    if(instruction[1] == 0x44 && instruction[2] == 0x24) {
                        this->cave.insert(&instruction[1], 4);
                        instruction_size = 5;
                    }
                    else {
                        message_box("Unsupported mov instruction.");
                        std::terminate();
                    }
                    break;
                }

                // mov r8, byte ptr [r32 + disp8]
                case 0x8A: {
                    switch(instruction[1]) {
                        case 0x47: { // al, edi
                            this->cave.insert(&instruction[0], 3);
                            instruction_size = 3;
                            break;
                        }

                        default: {
                            message_box("Unsupported mov instruction.");
                            std::terminate();
                        }
                    }
                    break;
                }

                // test r/m8,r8
                case 0x84: {
                    this->cave.insert(&instruction[0], 2);
                    instruction_size = 2;
                    break;
                }

                // far call / jump
                case 0xFF: {
                    this->cave.insert(0xFF);

                    // call dword ptr [edx + disp32]
                    if(instruction[1] == 0x92) {
                        this->cave.insert(0x92);
                        this->cave.insert(&instruction[2], 4);

                        instruction_size = 6;
                        break;
                    }
                    // call dword ptr [edx + disp8]
                    else if(instruction[1] == 0x52) {
                        this->cave.insert(0x52);
                        this->cave.insert(instruction[2]);

                        instruction_size = 3;
                        break;
                    }
                    // jmp dword ptr [eax ^ 4 + m32]
                    else if(instruction[1] == 0x24 && instruction[2] == 0x85) {
                        this->cave.insert(0x24);
                        this->cave.insert(0x85);
                        this->cave.insert(&instruction[3], 4);

                        instruction_size = 7;
                        break;
                    }
                    else {
                        message_box("Unsupported call instruction.");
                        std::terminate();
                    }
                }

                // test
                case 0x85: {
                    // test eax, eax (?)
                    if(instruction[1] == 0xC0) {
                        this->cave.insert(0xC0);
                        instruction_size = 2;
                    }
                    else {
                        message_box("Unsupported test instruction.");
                        std::terminate();
                    }
                    break;
                }

                // movzx
                case 0x0F: {
                    if(instruction[1] == 0xB6 && instruction[2] == 0x47) { // eax, byte ptr [edi + disp8]
                        this->cave.insert(&instruction[0], 4);
                        instruction_size = 4;
                    }
                    else if(instruction[1] == 0xBF && instruction[2] == 0xC0) { // eax, ax
                        this->cave.insert(&instruction[0], 3);
                        instruction_size = 3;
                    }
                    else {
                        message_box("Unsupported movzx instruction.");
                        std::terminate();
                    }
                    break;
                }

                // cmp
                case 0x66: {
                    if(instruction[1] == 0x39 && instruction[2] == 0x46) { // word ptr [esi + disp8], ax
                        this->cave.insert(&instruction[0], 4);
                        instruction_size = 4;
                    }
                    else {
                        message_box("Unsupported cmp instruction.");
                        std::terminate();
                    }
                    break;
                }

                // cmp al, imm8
                case 0x3C: {
                    this->cave.insert(&instruction[0], 2);
                    instruction_size = 2;
                    break;
                }

                // dec eax
                case 0x48: {
                    this->cave.insert(&instruction[0], 1);
                    instruction_size = 1;
                    break;
                }

                // cmp
                case 0x83: {
                    if(instruction[1] == 0xF8) { // eax, imm8
                        this->cave.insert(&instruction[0], 3);
                        instruction_size = 3;
                    }
                    else {
                        message_box("Unsupported cmp instruction.");
                        std::terminate();
                    }
                    break;
                }

                // nop
                case 0x90: {
                    this->cave.insert(0x90);
                    instruction_size = 1;
                    break;
                }

                default: {
                    message_box("Unable to build cave: unsupported instruction. \nOpcode: 0x%.2X at 0x%.8X", instruction[0], instruction);
                    std::terminate();
                }
            }

            // Backup original instruction
            auto *instruction_bytes = reinterpret_cast<const std::byte *>(instruction);
            this->original_code.insert(this->original_code.end(), instruction_bytes, instruction_bytes + instruction_size);

            copied_bytes += instruction_size;
        }
    }

    void Hook::copy_instructions(const void *address) noexcept {
        std::uint8_t no = 0;
        this->copy_instructions(address, no);
    }

    void Hook::write_cave_return_jmp() noexcept {
        // jmp
        this->cave.insert(0xE9);

        // offset
        auto offset = this->calculate_32bit_offset(&this->cave.get_top(), this->instruction + this->original_code.size());
        this->cave.insert_address(offset);
    }

    void SwitchHook::execute_original_code(bool setting) noexcept {
        *this->execute_original_code_flag = setting;
    }

    void SwitchHook::initialize(void *instruction, const void *function, bool pushad) noexcept {
        if(this->hooked) {
            return;
        }

        // Set instruction
        this->instruction = reinterpret_cast<std::byte *>(instruction);

        // Initialize execute original code flag
        this->execute_original_code_flag = std::make_unique<bool>(true);

        // write function call
        this->write_function_call(function, pushad);

        // cmp byte ptr [flag], 0
        this->cave.insert(0x80);
        this->cave.insert(0x3D);
        auto flag_address = reinterpret_cast<std::uint32_t>(this->execute_original_code_flag.get());
        this->cave.insert_address(flag_address);
        this->cave.insert(0); // false

        // je instruction_size
        this->cave.insert(0x74);
        this->cave.insert(0x0);
        std::uint8_t &jmp_offset = *reinterpret_cast<std::uint8_t *>(&this->cave.get_top());

        // Copy instruction code into cave
        std::uint8_t instruction_size;
        this->copy_instructions(instruction, instruction_size);

        // Update jump offset
        jmp_offset += instruction_size;

        // Write codecave return
        this->write_cave_return_jmp();
    }

    SwitchHook::~SwitchHook() noexcept {
        this->release();
    }

    void FunctionOverride::initialize(void *instruction, const void *function, bool pushad) noexcept {
        if(this->hooked) {
            return;
        }

        // Set instruction
        this->instruction = reinterpret_cast<std::byte *>(instruction);

        // Initialize execute original code flag
        this->execute_original_code_flag = std::make_unique<bool>(true);

        // write function call
        this->write_function_call(function, pushad);

        // cmp byte ptr [flag], 0
        this->cave.insert(0x80);
        this->cave.insert(0x3D);
        auto flag_address = reinterpret_cast<std::uint32_t>(this->execute_original_code_flag.get());
        this->cave.insert_address(flag_address);
        this->cave.insert(0); // false

        // je return
        this->cave.insert(0x74);
        this->cave.insert(0x0);
        std::uint8_t &jmp_offset = *reinterpret_cast<std::uint8_t *>(&this->cave.get_top());

        // Copy instruction code into cave
        std::uint8_t instruction_size;
        this->copy_instructions(instruction, instruction_size);
        jmp_offset += instruction_size;

        // Write return to original code
        this->write_cave_return_jmp();
        jmp_offset += 5;

        // Write function return
        this->cave.insert(0xC3);
    }

    FunctionOverride::~FunctionOverride() noexcept {
        this->release();
    }

    void ChimeraFunctionOverride::initialize(void *cave, const void *function, const void **cave_return) noexcept {
        if(this->hooked) {
            return;
        }
        
        // Set instruction
        this->instruction = reinterpret_cast<std::byte *>(cave);

        // Backup original jmp instruction
        std::vector<std::byte> original_override_jmp;
        for(std::size_t i = 0; i < 5; i++) {
            original_override_jmp.push_back(this->instruction[i]);
        }
    
        this->cave.insert(0xE9);
        this->cave.insert_address(this->calculate_32bit_offset(&this->cave.get_top(), function));

        // Set override return
        *cave_return = &this->cave.get_top() + 1;

        // Get original code from Chimera cave
        auto *chimera_cave = reinterpret_cast<std::byte *>(this->follow_jump(cave));
        std::uint8_t intruction_size = 0;
        this->copy_instructions(reinterpret_cast<void *>(chimera_cave), intruction_size);
        this->copy_instructions(reinterpret_cast<void *>(chimera_cave + 5), intruction_size);

        // Save Chimera override jump
        this->original_code = original_override_jmp;
        
        // Return
        this->write_cave_return_jmp();
    }

    ChimeraFunctionOverride::~ChimeraFunctionOverride() noexcept {
        this->release();
    }
    
}
