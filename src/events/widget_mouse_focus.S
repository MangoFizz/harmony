;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _handle_widget_mouse_focus_asm
_handle_widget_mouse_focus_asm:
    pushad
    pushfd

    push esi ;# focused widget
    call _call_widget_mouse_focus_events
    add esp, 4
    
    popfd
    popad
    ret
