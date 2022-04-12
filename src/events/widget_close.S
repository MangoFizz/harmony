;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _close_widget_override
_close_widget_override:
    pushad
    pushfd
    
    push eax ;# widget
    call _call_widget_close_events
    add esp, 4

    test eax, eax
    jnz do_close_widget

    popfd
    popad
    ret

    do_close_widget:
    popfd
    popad

    ;# Jump back to original function
    jmp dword ptr _close_widget_fn_return
