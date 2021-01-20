;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _on_multiplayer_sound_asm
_on_multiplayer_sound_asm:
    pushfd
    pushad

    push esi
	call _do_on_multiplayer_sound
	pop esi

    popad
    popfd
    ret
