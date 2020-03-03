global load_gdt
extern gdtbl
load_gdt:
    lgdt [gdtbl]

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax

    jmp 0x08:test_mark ; Far jump to flush gdt

test_mark:
    ret