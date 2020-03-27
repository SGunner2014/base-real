/*
* Sets up the interrupt handlers and contains functions for registering new handlers - utilised by drivers
*
* Author: Sam J Gunnervoid add_idt_handler(int n, uint32_t handler);

*/
#include "isr.h"
#include "setup.h"
#include "ports.h"
#include "../../drivers/screen/screen_buffer.h"

isr_t interrupt_handlers[256];

void install_isrs()
{
    add_idt_handler(0, (uint32_t)isr0);
    add_idt_handler(1, (uint32_t)isr1);
    add_idt_handler(2, (uint32_t)isr2);
    add_idt_handler(3, (uint32_t)isr3);
    add_idt_handler(4, (uint32_t)isr4);
    add_idt_handler(5, (uint32_t)isr5);
    add_idt_handler(6, (uint32_t)isr6);
    add_idt_handler(7, (uint32_t)isr7);
    add_idt_handler(8, (uint32_t)isr8);
    add_idt_handler(9, (uint32_t)isr9);
    add_idt_handler(10, (uint32_t)isr10);
    add_idt_handler(11, (uint32_t)isr11);
    add_idt_handler(12, (uint32_t)isr12);
    add_idt_handler(13, (uint32_t)isr13);
    add_idt_handler(14, (uint32_t)isr14);
    add_idt_handler(15, (uint32_t)isr15);
    add_idt_handler(16, (uint32_t)isr16);
    add_idt_handler(17, (uint32_t)isr17);
    add_idt_handler(18, (uint32_t)isr18);
    add_idt_handler(19, (uint32_t)isr19);
    add_idt_handler(20, (uint32_t)isr20);
    add_idt_handler(21, (uint32_t)isr21);
    add_idt_handler(22, (uint32_t)isr22);
    add_idt_handler(23, (uint32_t)isr23);
    add_idt_handler(24, (uint32_t)isr24);
    add_idt_handler(25, (uint32_t)isr25);
    add_idt_handler(26, (uint32_t)isr26);
    add_idt_handler(27, (uint32_t)isr27);
    add_idt_handler(28, (uint32_t)isr28);
    add_idt_handler(29, (uint32_t)isr29);
    add_idt_handler(30, (uint32_t)isr30);
    add_idt_handler(31, (uint32_t)isr31);

    // Remap PIC
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);

    add_idt_handler(32, (uint32_t)irq0);
    add_idt_handler(33, (uint32_t)irq1);
    add_idt_handler(34, (uint32_t)irq2);
    add_idt_handler(35, (uint32_t)irq3);
    add_idt_handler(36, (uint32_t)irq4);
    add_idt_handler(37, (uint32_t)irq5);
    add_idt_handler(38, (uint32_t)irq6);
    add_idt_handler(39, (uint32_t)irq7);
    add_idt_handler(40, (uint32_t)irq8);
    add_idt_handler(41, (uint32_t)irq9);
    add_idt_handler(42, (uint32_t)irq10);
    add_idt_handler(43, (uint32_t)irq11);
    add_idt_handler(44, (uint32_t)irq12);
    add_idt_handler(45, (uint32_t)irq13);
    add_idt_handler(46, (uint32_t)irq14);
    add_idt_handler(47, (uint32_t)irq15);
}

void handle_isr(registers_t* reg)
{
    if (reg) {
        switch(reg->int_no) {
            case 14:
                fb_write("page fault\n", 0xF0);
        }
    }
}

void handle_irq(registers_t* reg)
{
    // send eoi to pic
    if (reg->int_no >= 40)
        port_byte_out(0xA0, 0x20); /* slave */
    port_byte_out(0x20, 0x20); /* master */

    if (interrupt_handlers[reg->int_no] != 0) {
        isr_t handler = interrupt_handlers[reg->int_no];
        handler(reg);
    }
}

// Registers a new interrupt handler
void register_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}