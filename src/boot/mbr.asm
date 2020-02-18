[org 0x7c00]

entry:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    mov ah, 42h
    mov si, dap
    int 0x13

    jmp 0x1000:0x0

dap:
    db 0x10   ; required
    db 0x0
    dw 0x1    ; sectors to read
    dw 0x0    ; offset
    dw 0x1000 ; segment
    dq 0x40   ; start from sector 64