[org 0x700]
bits 16

; %include "src/boot/real_print.asm"

; This is the second-stage bootloader
; no longer confined to 512 bytes, we can easily enter protected mode and do anything else that we need to do
entry:
    mov ah, 0x0e
    mov al, 'x'
    int 0x10
    mov ah, 0x0e
    mov al, 'x'
    int 0x10
    mov ah, 0x0e
    mov al, 'x'
    int 0x10
    mov ah, 0x0e
    mov al, 'x'
    int 0x10
    mov ah, 0x0e
    mov al, 'x'
    int 0x10
    ; mov bx, welcome_msg
    ; call real_print
    ; call real_print_nl
    jmp $

welcome_msg db "Hello, world", 0