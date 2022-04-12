;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.data

mouse_button: .long 0
menu_button_event: .long 0

.text

.globl _handle_widget_mouse_button_press_asm
_handle_widget_mouse_button_press_asm:
    ;# Save stuff
    pushad
    pushfd

    ;# Get pressed widget
    mov ebx, dword ptr [esp + 0x48]

    ;# Get button event
    mov ecx, eax
    mov menu_button_event, ecx

    ;# Get mouse pressed button
    mov edx, 0
    mov dl, byte ptr [edi + 4]
    mov mouse_button, edx
    
    ;# Run events
    push edx
    push ebx
    call _call_widget_mouse_button_press_events
    add esp, 8

    ;# Check if the mouse button matches the menu button event
    mov ebx, [mouse_button]
    mov ecx, [menu_button_event]
    cmp bl, cl
    jne block_event

    ;# Set event allow flag
    popfd
    cmp al, 1 
    popad
    jmp return

    ;# Mouse pressed button doesn't equal to menu button event. Block event.
    block_event:
    popfd
    cmp bl, -1
    popad

    return:
    ret
