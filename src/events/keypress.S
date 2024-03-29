;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _call_keypress_events_asm
_call_keypress_events_asm:
    pushad
    pushfd
    push ecx ;# pressed key data
    call _call_keypress_events
    add esp, 4
    popfd
    popad
    ret
