[extern handle_isr]
[extern handle_irq]

; handles all isr routines and then passes onto c code
common_isr_handler:
    pusha ; save register state
    mov ax, ds
    push eax ; save data seg desc
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    cld
    call handle_isr

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
    mov ax, ds
    push eax ; save data seg desc
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    cld
    call handle_irq

    pop ebx
    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa
    add esp, 8
    iret

; First make the ISRs global
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
; IRQs
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; 0: Divide By Zero Exception
isr0:
    push byte 0
    push byte 0
    jmp common_isr_handler

; 1: Debug Exception
isr1:
    push byte 0
    push byte 1
    jmp common_isr_handler

; 2: Non Maskable Interrupt Exception
isr2:
    push byte 0
    push byte 2
    jmp common_isr_handler

; 3: Int 3 Exception
isr3:
    push byte 0
    push byte 3
    jmp common_isr_handler

; 4: INTO Exception
isr4:
    push byte 0
    push byte 4
    jmp common_isr_handler

; 5: Out of Bounds Exception
isr5:
    push byte 0
    push byte 5
    jmp common_isr_handler

; 6: Invalid Opcode Exception
isr6:
    push byte 0
    push byte 6
    jmp common_isr_handler

; 7: Coprocessor Not Available Exception
isr7:
    push byte 0
    push byte 7
    jmp common_isr_handler

; 8: Double Fault Exception (With Error Code!)
isr8:
    push byte 8
    jmp common_isr_handler

; 9: Coprocessor Segment Overrun Exception
isr9:
    push byte 0
    push byte 9
    jmp common_isr_handler

; 10: Bad TSS Exception (With Error Code!)
isr10:
    push byte 10
    jmp common_isr_handler

; 11: Segment Not Present Exception (With Error Code!)
isr11:
    push byte 11
    jmp common_isr_handler

; 12: Stack Fault Exception (With Error Code!)
isr12:
    push byte 12
    jmp common_isr_handler

; 13: General Protection Fault Exception (With Error Code!)
isr13:
    push byte 13
    jmp common_isr_handler

; 14: Page Fault Exception (With Error Code!)
isr14:
    push byte 14
    jmp common_isr_handler

; 15: Reserved Exception
isr15:
    push byte 0
    push byte 15
    jmp common_isr_handler

; 16: Floating Point Exception
isr16:
    push byte 0
    push byte 16
    jmp common_isr_handler

; 17: Alignment Check Exception
isr17:
    push byte 0
    push byte 17
    jmp common_isr_handler

; 18: Machine Check Exception
isr18:
    push byte 0
    push byte 18
    jmp common_isr_handler

; 19: Reserved
isr19:
    push byte 0
    push byte 19
    jmp common_isr_handler

; 20: Reserved
isr20:
    push byte 0
    push byte 20
    jmp common_isr_handler

; 21: Reserved
isr21:
    push byte 0
    push byte 21
    jmp common_isr_handler

; 22: Reserved
isr22:
    push byte 0
    push byte 22
    jmp common_isr_handler

; 23: Reserved
isr23:
    push byte 0
    push byte 23
    jmp common_isr_handler

; 24: Reserved
isr24:
    push byte 0
    push byte 24
    jmp common_isr_handler

; 25: Reserved
isr25:
    push byte 0
    push byte 25
    jmp common_isr_handler

; 26: Reserved
isr26:
    push byte 0
    push byte 26
    jmp common_isr_handler

; 27: Reserved
isr27:
    push byte 0
    push byte 27
    jmp common_isr_handler

; 28: Reserved
isr28:
    push byte 0
    push byte 28
    jmp common_isr_handler

; 29: Reserved
isr29:
    push byte 0
    push byte 29
    jmp common_isr_handler

; 30: Reserved
isr30:
    push byte 0
    push byte 30
    jmp common_isr_handler

; 31: Reserved
isr31:
    push byte 0
    push byte 31
    jmp common_isr_handler

; IRQ handlers
irq0:
	push byte 0
	push byte 32
	jmp common_irq_handler

irq1:
	push byte 1
	push byte 33
	jmp common_irq_handler

irq2:
	push byte 2
	push byte 34
	jmp common_irq_handler

irq3:
	push byte 3
	push byte 35
	jmp common_irq_handler

irq4:
	push byte 4
	push byte 36
	jmp common_irq_handler

irq5:
	push byte 5
	push byte 37
	jmp common_irq_handler

irq6:
	push byte 6
	push byte 38
	jmp common_irq_handler

irq7:
	push byte 7
	push byte 39
	jmp common_irq_handler

irq8:
	push byte 8
	push byte 40
	jmp common_irq_handler

irq9:
	push byte 9
	push byte 41
	jmp common_irq_handler

irq10:
	push byte 10
	push byte 42
	jmp common_irq_handler

irq11:
	push byte 11
	push byte 43
	jmp common_irq_handler

irq12:
	push byte 12
	push byte 44
	jmp common_irq_handler

irq13:
	push byte 13
	push byte 45
	jmp common_irq_handler

irq14:
	push byte 14
	push byte 46
	jmp common_irq_handler

irq15:
	push byte 15
	push byte 47
	jmp common_irq_handler