#include "core/cpu/setup.h"
#include "drivers/screen.h"
#include "core/cpu/isr.h"

void perform_setup();
static void keypress(registers_t*);