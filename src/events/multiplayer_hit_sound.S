;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _multiplayer_hit_sound_event_asm
_multiplayer_hit_sound_event_asm:
    pushad
    pushfd

    ;# Get and save x87 status word (from sound volume FPU)
    fnstsw ax
    push ax

    ;# Call our events
    call _do_multiplayer_hit_sound_events

    ;# If the sound volume FPU is zero, the C3 flag from the status word should be 1
    pop ax
    test ah, 0x44
    jp do_not_block_sound

    ;# Block sound function
    mov byte ptr _allow_multiplayer_hit_sound, 0

    do_not_block_sound:
    popfd
    popad
    ret
