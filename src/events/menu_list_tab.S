;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _menu_list_tab
_menu_list_tab:
    pushad
    pushfd

    ;# Get pressed key
    mov ecx, [esp + 0x2C]
    mov eax, 0
    mov al, byte ptr [ecx + 4]

    ;# Get menu list ID
    mov ecx, [ebx]

    ;# Get pressed button index
    mov edx, [ebx + 0x38]
    mov edx, [edx]

    ;# Run events
    push edx
    push ecx
    push eax
    call _on_menu_list_tab
    add esp, 12

    popfd
    popad
    ret
