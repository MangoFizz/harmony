;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

block_original_function: .byte 0

.globl _multiplayer_sound_override
_multiplayer_sound_override:
    pushfd
    pushad
    push esi
    call _do_on_multiplayer_sound
    add esp, 4
    mov block_original_function, al
    popad
    cmp byte ptr block_original_function, 0
    je block
    
    popfd
    jmp dword ptr _multiplayer_sound_fn_return

    block:
    popfd
    ret
