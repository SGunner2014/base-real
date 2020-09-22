#include "../../libc/stdint.h"

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

void init_keyboard();

void process_keypress(uint8_t scancode);

struct
{
  uint8_t caps;
  uint8_t lshift;
  uint8_t rshift;
  uint8_t lctrl;
  uint8_t rctrl;
} kflags;

#endif