// SPDX-License-Identifier: GPL-3.0-only

#include <memory>
#include <windows.h>
#include "../messaging/message_box.hpp"
#include "memory.hpp"
#include "codecave.hpp"

namespace Harmony {
    using namespace Memory;

    void Codecave::set_access_protection(bool setting) noexcept {
        if(setting) {
            // enable code execution
            VirtualProtect(this->cave, this->size, PAGE_EXECUTE_READWRITE, &this->original_page_protection);
        }
        else {
            VirtualProtect(this->cave, this->size, this->original_page_protection, NULL);
        }
    }

    std::uint32_t Codecave::calculate_jmp_offset(const void *jmp, const void *destination) noexcept {
        auto offset = reinterpret_cast<std::uint32_t>(destination) - (reinterpret_cast<std::uint32_t>(jmp) + 5);
        return offset;
    }
    
    std::byte *Codecave::follow_jump(std::byte *jmp) noexcept {
        if(jmp[0] != static_cast<std::byte>(0xE8) && jmp[0] != static_cast<std::byte>(0xE9)) {
            message_box("Unable to follow jump. WHAT THE H*CK IS THIS!");
        }
        auto jmp_offset = *reinterpret_cast<std::uint32_t *>(jmp + 1);
        auto jmp_end = reinterpret_cast<std::uint32_t>(jmp + 5);
        auto *destination = reinterpret_cast<std::byte *>(jmp_offset + jmp_end);
        return destination;
    }

    void Codecave::write_function_call(const void *function, bool pushad) noexcept {
        if(pushad) {
            this->insert(0x9C); // pushfd
            this->insert(0x60); // pushad
        }

        this->insert(0xE8); // call
        auto fn_offset = this->calculate_jmp_offset(reinterpret_cast<void *>(&this->cave[this->size - 1]), function);
        this->insert_address(fn_offset);

        if(pushad) {
            this->insert(0x61); // popad
            this->insert(0x9D); // popfd
        }
    }

    void Codecave::copy_instruction(const void *address, std::uint8_t &copied_bytes) noexcept {
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
                    this->insert(instruction[0]); // call or jmp

                    // offset
                    auto original_offset = *reinterpret_cast<const std::uint32_t *>(&instruction[1]);
                    auto offset = original_offset + this->calculate_jmp_offset(&this->cave[this->size - 1], &instruction[5]);
                    this->insert_address(offset);
                    
                    instruction_size = 5;
                    break;
                }

                // mov r/m8, imm8
                case 0xC6: {
                    this->insert(0xC6);

                    // mov [esp + disp8], imm8
                    if(instruction[1] == 0x44 && instruction[2] == 0x24) {
                        this->insert(&instruction[1], 4);
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
                            this->insert(&instruction[0], 3);
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
                    this->insert(&instruction[0], 2);
                    instruction_size = 2;
                    break;
                }

                // far call / jump
                case 0xFF: {
                    this->insert(0xFF);

                    // call dword ptr [edx + disp32]
                    if(instruction[1] == 0x92) {
                        this->insert(0x92);
                        this->insert(&instruction[2], 4);

                        instruction_size = 6;
                        break;
                    }
                    // call dword ptr [edx + disp8]
                    else if(instruction[1] == 0x52) {
                        this->insert(0x52);
                        this->insert(instruction[2]);

                        instruction_size = 3;
                        break;
                    }
                    // jmp dword ptr [eax ^ 4 + m32]
                    else if(instruction[1] == 0x24 && instruction[2] == 0x85) {
                        this->insert(0x24);
                        this->insert(0x85);
                        this->insert(&instruction[3], 4);

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
                        this->insert(0xC0);
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
                        this->insert(&instruction[0], 4);
                        instruction_size = 4;
                    }
                    else if(instruction[1] == 0xBF && instruction[2] == 0xC0) { // eax, ax
                        this->insert(&instruction[0], 3);
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
                        this->insert(&instruction[0], 4);
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
                    this->insert(&instruction[0], 2);
                    instruction_size = 2;
                    break;
                }

                // dec eax
                case 0x48: {
                    this->insert(&instruction[0], 1);
                    instruction_size = 1;
                    break;
                }

                // cmp
                case 0x83: {
                    if(instruction[1] == 0xF8) { // eax, imm8
                        this->insert(&instruction[0], 3);
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
                    this->insert(0x90);
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
            this->original_instruction.insert(this->original_instruction.end(), instruction_bytes, instruction_bytes + instruction_size);

            copied_bytes += instruction_size;
        }
    }

    void Codecave::write_cave_return() noexcept {
        // jmp
        this->insert(0xE9);

        // offset
        auto offset = this->calculate_jmp_offset(&this->cave[this->size - 1], this->instruction + this->original_instruction.size());
        this->insert_address(offset);
    }

    void Codecave::execute_original_code(bool setting) noexcept {
        this->execute_original_code_flag = setting;
    }

    void Codecave::write_basic_cave(void *address, const void *function, bool pushad) noexcept {
        if(this->hooked) {
            return;
        }

        this->instruction = reinterpret_cast<std::byte *>(address);

        this->write_function_call(function, pushad);

        // cmp byte ptr [flag], 0
        this->insert(0x80);
        this->insert(0x3D);
        auto flag_address = reinterpret_cast<std::uint32_t>(&this->execute_original_code_flag);
        this->insert_address(flag_address);
        this->insert(0); // false

        // je instruction_size
        this->insert(0x74);
        this->insert(0x0);

        // Copy instruction code into cave
        std::uint8_t &instruction_size = *reinterpret_cast<std::uint8_t *>(&this->cave[this->size - 1]);
        this->copy_instruction(address, instruction_size);

        // Write codecave return
        this->write_cave_return();
    }

    void Codecave::write_function_call(void *address, const void *function_before, const void *function_after, bool pushad) {
        if(this->hooked) {
            return;
        }

        this->instruction = reinterpret_cast<std::byte *>(address);

        // Write function call 1
        if(function_before) {
            this->write_function_call(function_before, pushad);
        }

        // Copy instruction code into cave
        std::uint8_t instruction_size = 0;
        this->copy_instruction(address, instruction_size);

        // Write function call 2
        if(function_after) {   
            this->write_function_call(function_after, pushad);
        }

        // Write codecave return
        this->write_cave_return();
    }

    void Codecave::write_function_override(void *address, const void *function, bool pushad) {
        if(this->hooked) {
            return;
        }

        this->instruction = reinterpret_cast<std::byte *>(address);

        this->write_function_call(function, pushad);

        // cmp byte ptr [flag], 0
        this->insert(0x80);
        this->insert(0x3D);
        auto flag_address = reinterpret_cast<std::uint32_t>(&this->execute_original_code_flag);
        this->insert_address(flag_address);
        this->insert(0); // false

        // je instruction_size
        this->insert(0x74);
        this->insert(0x0);

        std::uint8_t &instruction_size = *reinterpret_cast<std::uint8_t *>(&this->cave[this->size - 1]);
        this->copy_instruction(address, instruction_size);

        // Write codecave return
        this->write_cave_return();
        instruction_size += 5;

        // Function return
        this->insert(0xC3);
    }

    void Codecave::hack_chimera_function_override(void *address, const void *function, const void **cave_return) noexcept {
        if(this->hooked) {
            return;
        }

        this->instruction = reinterpret_cast<std::byte *>(address);

        // Backup original jmp instruction
        std::vector<std::byte> original_override_jmp;
        for(std::size_t i = 0; i < 5; i++) {
            original_override_jmp.push_back(this->instruction[i]);
        }
    
        this->insert(0xE9);
        this->insert_address(this->calculate_jmp_offset(&this->cave[this->size - 1], function));

        // Set override return
        *cave_return = &this->cave[this->size];

        // Get original code from Chimera cave
        auto *chimera_cave = reinterpret_cast<std::byte *>(this->follow_jump(address));
        std::uint8_t intruction_size = 0;
        this->copy_instruction(reinterpret_cast<void *>(chimera_cave), intruction_size);
        this->copy_instruction(reinterpret_cast<void *>(chimera_cave + 5), intruction_size);

        // Save Chimera override jump
        this->original_instruction = original_override_jmp;
        
        // Return
        this->write_cave_return();
    }

    void Codecave::hack_chimera_function_call(void *address, const void *function_before, const void *function_after, bool pushad) noexcept {
        if(this->hooked) {
            return;
        }

        // Build function call cave
        this->write_function_call(address, function_before, function_after, pushad);

        // If there is no second function, we don't need to do anything
        if(!function_before) {
            return;
        }

        // Get Chimera's cave exit jmp
        auto *chimera_cave_jmp = follow_jump(this->instruction);
        for(auto &i = chimera_cave_jmp; *i != static_cast<std::byte>(ASM_JMP_IMM32_OPCODE); i++);
        auto *exit_jmp_offset = reinterpret_cast<std::uint32_t *>(chimera_cave_jmp + 1);

        // Calculate where is the second call in our cave
        std::size_t second_call_offset = 0;
        if(function_before) {
            second_call_offset += (pushad ? 9 : 5);
        }
        second_call_offset += this->original_instruction.size();

        // Redirect exit jump in Chimera's cave to our second function call
        *exit_jmp_offset = calculate_jmp_offset(chimera_cave_jmp, this->cave + second_call_offset);
    }

    void Codecave::hook() noexcept {
        if(this->hooked && this->size > 0) {
            return;
        }
        this->hooked = true;
        set_access_protection();

        // Kill original code
        for(std::size_t i = 0; i < this->original_instruction.size(); i++) {
            overwrite(this->instruction + i, static_cast<std::byte>(0x90));
        }

        overwrite(this->instruction, static_cast<std::byte>(0xE9));
        overwrite(this->instruction + 1, this->calculate_jmp_offset(this->instruction, this->cave));
    }

    void Codecave::release() noexcept {
        if(!this->hooked) {
            return;
        }
        overwrite(this->instruction, this->original_instruction.data(), this->original_instruction.size());
        set_access_protection(false);
        this->hooked = false;
    }

    Codecave::Codecave() noexcept {
        this->cave = reinterpret_cast<std::byte *>(malloc(32));
    }

    Codecave::~Codecave() noexcept {
        this->release();
        free(this->cave);
    }
}