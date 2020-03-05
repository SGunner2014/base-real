#include "../../libc/stdint.h"

#ifndef _SETUP_H
#define _SETUP_H 1
#define KERNEL_CS 0x08

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

void switch_gdt();
void set_gdt_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
void switch_idt();
void set_idt_entry(int num, unsigned long base, unsigned short sel, unsigned char flags);
void add_idt_handler(int n, uint32_t handler);

#endif