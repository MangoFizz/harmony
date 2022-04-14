;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _call_console_unknown_command_events_asm
_call_console_unknown_command_events_asm:
    pushad
    pushfd
    mov edx, [esp + 0x30]
    push edx ;# command
    call _call_console_unknown_command_events
    add esp, 4
    popfd
    popad
    ret
