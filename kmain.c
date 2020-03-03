#include "drivers/screen.h"
#include "libc/mem.h"

extern void load_gdt();
extern void load_idt();

// Contains the information needed to load the GDT
struct gdt {
    unsigned short size;
    unsigned int address;
} __attribute__((packed));

// Contains an entry in the GDT table
struct gdt_entry {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

// Contains an entry in the IDT table
struct idt_entry {
    unsigned short base_low;
    unsigned short segment_sel;
    unsigned char always_null;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed));


struct gdt_entry gdts[3];
struct gdt gdtbl;

struct idt_entry idt[256];
struct idt_ptr idtbl;

void _load_gdt();
void _set_gdt_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
void _load_idt();
void _set_idt_entry(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

// Main kernel entry point
void kmain()
{
    // We should load the gdt before doing anything else
    _load_gdt();
    _load_idt();

    fb_clear();
    fb_write("Hello, world!", 0x28);

    for (;;) {
        ;
    }
}

// Loads the GDT using gdt.s
void _load_gdt()
{
    _set_gdt_entry(0, 0, 0, 0, 0); // null desc
    _set_gdt_entry(1, 0, 0xffffffff, 0x9a, 0xcf); // code segment
    _set_gdt_entry(2, 0, 0xffffffff, 0x92, 0xcf); // data segment

    gdtbl.address = (int) &gdts;
    gdtbl.size = sizeof(struct gdt_entry) * 3;
    load_gdt();
}

// Sets a new entry in the gdt
void _set_gdt_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
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
void _load_idt()
{
    idtbl.base = (int) &idt;
    idtbl.limit = (sizeof(struct idt_entry) * 256) - 1;

    // clear out the entier idt
    memset((void*) &idt, 0, sizeof(struct idt_entry) * 256);

    load_idt();
}

// Sets an entry in the IDT.
void _set_idt_entry(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[num].base_low = (base & 0xffff);
    idt[num].base_high = (base >> 16) & 0xffff;

    idt[num].segment_sel = sel;
    idt[num].always_null = 0;
    idt[num].flags = flags;
}