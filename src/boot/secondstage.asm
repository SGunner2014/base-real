[org 0x7c00]

entry:
    mov al, 'x'
    mov ah, 0x0e
    int 0x10

    xchg bx, bx
    xchg bx, bx
    xchg bx, bx
    xchg bx, bx
    xchg bx, bx
    xchg bx, bx

    jmp $

times 510 - ($-$$) db 0
dw 0xaa55