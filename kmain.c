#include "drivers/screen.h"
// #include "drivers/mem/gdt.h"

extern void load_gdt();

struct gdt {
    unsigned short size;
    unsigned int address;
} __attribute((packed));

struct gdt_entry {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute((packed));

struct gdt_entry gdts[3];
struct gdt gdtbl;

void _load_gdt();
void _set_gdt_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

void kmain()
{
    // We should load the gdt before doing anything else
    _load_gdt();

    fb_clear();
    fb_write("Hello, world!", 0x28);

    for (;;) {
        ;
    }
}

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
void _set_gdt_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
    gdts[num].base_low = base & 0xffff;
    gdts[num].base_middle = (base >> 16) & 0xff;
    gdts[num].base_high = (base >> 24) & 0xff;

    gdts[num].limit_low = limit & 0xffff;
    gdts[num].granularity = ((limit >> 16) & 0x0f);

    gdts[num].granularity |= (gran & 0xf0);
    gdts[num].access = access;
}