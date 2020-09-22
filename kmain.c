#include "kmain.h"
#include "core/cpu/setup.h"
#include "core/cpu/isr.h"
#include "core/cpu/ports.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/console/console.h"
#include "core/cpu/timer.h"
#include "libc/function.h"
#include "libc/string.h"
#include "libc/mem.h"

// Main kernel entry point
void kmain()
{
    // Perform initial setup actions, like gdt, idt.
    perform_setup();

    asm("int $2");
    asm("int $3");

    clear_screen();
    print("Hello, world!");
    write("> ");
}

// Performs initial setup actions required for the os to boot.
void perform_setup()
{
    switch_gdt();
    install_isrs();
    switch_idt();

    init_keyboard(); // Initialise keyboard driver
    init_timer(50);
}

// Invoked when the user has entered a line of input
void on_user_input(char *input)
{
    if (strcmp(input, "END") == 0)
    {
        print("Stopping the CPU. Bye!");
        asm volatile("hlt");
    }
    else if (strcmp(input, "PAGE") == 0)
    {
        uint32_t phys_addr;
        uint32_t page = kmalloc(1000, 1, &phys_addr);

        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        write("Page: ");
        write(page_str);
        write(", physical address: ");
        print(phys_str);
    }

    write("You said: ");
    print(input);
    write("> ");
}