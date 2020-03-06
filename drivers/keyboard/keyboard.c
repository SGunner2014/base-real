#include "keyboard.h"
#include "../../core/cpu/isr.h"
#include "../../core/cpu/ports.h"
#include "../screen/screen_buffer.h"

static void handle_keyboard_interrupt(registers_t *register_state)
{
    int scancode = port_byte_in(0x60);
    fb_write("key", 0x28);
    scancode++;
    if (register_state)
        return;
}

// Initialises the keyboard
void init_keyboard()
{
    register_handler(IRQ_1, handle_keyboard_interrupt);
}