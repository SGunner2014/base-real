global load_idt
extern idtbl
load_idt:
    lidt [idtbl]
    ret