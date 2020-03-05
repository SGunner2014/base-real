#include "kmain.h"

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

// Performs initial setup actions required for the os to boot.
void perform_setup()
{
    switch_gdt();
    install_isrs();
    switch_idt();

    init_keyboard(); // Initialise keyboard driver
}