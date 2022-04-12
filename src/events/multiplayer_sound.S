;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _multiplayer_sound_override
_multiplayer_sound_override:
    pushad
    pushfd

    push esi
    call _do_on_multiplayer_sound
    add esp, 4

    test eax, eax
    jnz do_multiplayer_sound

    popfd
    popad
    ret

    do_multiplayer_sound:
    popfd
    popad
    jmp dword ptr _multiplayer_sound_fn_return
