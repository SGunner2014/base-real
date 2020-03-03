extern isr_handler
extern irq_handler

; handles all isr routines and then passes onto c code
common_isr_handler:
    pusha ; save register state
    mov ax, fds
    push eax ; save data seg desc
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    push esp
    cld
    call isr_handler

    pop eax
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    iret

; handles all irq routines and then passes onto c code
common_irq_handler:
    pusha ; save register state
    mov ax, fds
    push eax ; save data seg desc
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    push esp
    cld
    call irq_handler

    pop ebx
    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa
    add esp, 8
    iret