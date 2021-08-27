;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _on_multiplayer_event_asm
_on_multiplayer_event_asm:
    pushfd
    pushad
    push edi ;# local player
    push ecx ;# victim
    push eax ;# killer
    push edx ;# event type
    call _do_on_multiplayer_event
    add esp, 16
    popad
    popfd
    ret
