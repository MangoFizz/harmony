;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.data

play_sound_address: .long 0

.text

play_sound_function_sig: .string "play_sound"

.globl _play_sound_asm
_play_sound_asm:
    pushad
    pushfd

    cmp dword ptr play_sound_address, 0
    jnz found
    lea eax, play_sound_function_sig
    push eax
    call _get_address_for_signature
    mov play_sound_address, eax
    add esp, 4
    found:

    ;# Get sound tag ID
    mov eax, [esp + 0x28]

    ;# Look for a valid tag id
    cmp eax, -1
    je return

    ;# Play it
    sub esp, 0xC
    push 0
    push 0
    push 0
    push 0
    push -1
    lea ecx, dword ptr [esp + 0x14]
    push ecx
    push eax
    mov word ptr [esp + 0x1C], 0
    mov dword ptr [esp + 0x20], 0x3F800000
    mov dword ptr [esp + 0x24], 0x3F800000
    call dword ptr play_sound_address
    add esp, 0x28

    return:
    popfd
    popad
    ret
