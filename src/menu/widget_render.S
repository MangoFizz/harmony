;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _menu_render_background_bitmap_asm
_menu_render_background_bitmap_asm:
    pushad
    pushfd
    mov eax, [esp + 0x28]
    mov ecx, [esp + 0x30]

    push ecx
    push eax
    call _menu_rescale_widget_render_area
    call _widescreen_displace_menu_elements
    add esp, 8

    popfd
    popad
    ret

.globl _menu_render_text_asm
_menu_render_text_asm:
    pushfd
    pushad

    push ecx
    call _widescreen_displace_menu_text
    add esp, 4

    popad
    popfd
    ret
