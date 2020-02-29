#include "drivers/screen.h"

void kmain()
{
    fb_set_pos(0, 0);
    fb_write("Hello, world!", 0x28);

    for (;;) {
        ;
    }
}