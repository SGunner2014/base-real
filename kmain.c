#include "kmain.h"
#include "drivers/console/console.h"

// Main kernel entry point
void kmain()
{
    // Perform initial setup actions, like gdt, idt.
    perform_setup();

    asm("int $2");
    asm("int $3");

    clear_screen();
    print("Hello, world!");

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