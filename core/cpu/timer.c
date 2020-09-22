#include "timer.h"
#include "../../drivers/console/console.h"
#include "../../libc/stdint.h"
#include "../../libc/string.h"
#include "ports.h"
#include "isr.h"
#include "../../libc/function.h"

uint32_t tick = 0;

static void timer_callback(registers_t *regs)
{
  tick++;
  UNUSED(regs);
}

void init_timer(uint32_t freq)
{
  /* Register as handler */
  register_handler(IRQ_0, timer_callback);

  /* Get PIT value, hardware clock at 1193180 Hz */
  uint32_t divisor = 1193180 / freq;
  uint8_t low = (uint8_t)(divisor & 0xff);
  uint8_t high = (uint8_t)((divisor >> 8) & 0xff);

  port_byte_out(0x43, 0x36); // command port
  port_byte_out(0x40, low);
  port_byte_out(0x40, high);
}