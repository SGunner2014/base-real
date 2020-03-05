#include "kmain.h"
#include "core/cpu/ports.h"

// Main kernel entry point
void kmain()
{
    // Perform initial setup actions, like gdt, idt.
    perform_setup();

    asm("int $2");
    asm("int $3");

    fb_write("Hello, world!\n", 0x28);

    for (;;) {
        asm("hlt");
    }
}

// Called when a key is pressed
static void keypress(registers_t* reg)
{
    unsigned char scan_code = port_byte_in(0x60);
    scan_code++;
    fb_write("key was pressed\n", 0x28);

    if (reg)
        return;
}

// Performs initial setup actions required for the os to boot.
void perform_setup()
{
    switch_gdt();
    install_isrs();
    switch_idt();

    register_handler(IRQ_1, keypress);
    register_handler(IRQ_2, keypress);
}