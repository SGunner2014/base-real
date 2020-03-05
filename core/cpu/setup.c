/*
* General setup procedures for the operating system included here.
* This file also contains some functions that are utilised by the interrupt system - these are used by drivers to register interrupt handlers
*
* Author: Sam J. Gunner
*/

#include "setup.h"
#include "../../libc/mem.h"

// Tables needed for setup.
struct gdt_entry gdts[3];
struct gdt gdtbl;

struct idt_entry idt[256];
struct idt_ptr idtbl;

// Loads the GDT using gdt.s
void switch_gdt()
{
    set_gdt_entry(0, 0, 0, 0, 0); // null desc
    set_gdt_entry(1, 0, 0xffffffff, 0x9a, 0xcf); // code segment
    set_gdt_entry(2, 0, 0xffffffff, 0x92, 0xcf); // data segment

    gdtbl.address = (int) &gdts;
    gdtbl.size = sizeof(struct gdt_entry) * 3;
    load_gdt();
}

// Sets a new entry in the gdt
void set_gdt_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    gdts[num].base_low = base & 0xffff;
    gdts[num].base_middle = (base >> 16) & 0xff;
    gdts[num].base_high = (base >> 24) & 0xff;

    gdts[num].limit_low = limit & 0xffff;
    gdts[num].granularity = ((limit >> 16) & 0x0f);

    gdts[num].granularity |= (gran & 0xf0);
    gdts[num].access = access;
}

// Loads the idt using idt.s
void switch_idt()
{
    idtbl.base = (uint32_t) &idt;
    idtbl.limit = (sizeof(struct idt_entry) * 256) - 1;

    load_idt();
}

// Sets an entry in the IDT.
void set_idt_entry(int num, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[num].base_low = (base & 0xffff);
    idt[num].base_high = (base >> 16) & 0xffff;

    idt[num].segment_sel = sel;
    idt[num].always_null = 0;
    idt[num].flags = flags;
}

// Adds a new entry to the idt
void add_idt_handler(int n, uint32_t handler)
{
    set_idt_entry(n, handler, KERNEL_CS, 0x8e);
}