;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _play_widget_sound_override
_play_widget_sound_override:
    pushad
    pushfd

    ;# Decrement the meme
    dec eax

    ;# Catch weird calls
    cmp eax, 3
    ja do_play_widget_sound
    cmp eax, 0
    jl do_play_widget_sound

    push eax ;# sound index
    call _call_widget_sound_events
    add esp, 4

    ;# Check allow flag
    test eax, eax
    jnz do_play_widget_sound

    popfd
    popad
    ret

    do_play_widget_sound:
    popfd
    popad
    jmp dword ptr _play_widget_sound_fn_return
