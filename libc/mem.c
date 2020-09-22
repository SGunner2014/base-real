#include "mem.h"

void memcpy(uint8_t *source, uint8_t *dest, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        *(dest + i) = *(source + i);
    }
}

void memset(uint8_t *dest, uint8_t val, uint32_t length)
{
    uint8_t *temp = (uint8_t *)dest;
    for (; length != 0; length--)
    {
        *temp++ = val;
    }
}

uint32_t free_mem_addr = 0x10000;

uint32_t kmalloc(uint32_t size, int align, uint32_t *phys_addr)
{
    // Pages are aligned to 4k (0x1000)
    if (align == 1 && (free_mem_addr & 0xfffff000))
    {
        free_mem_addr &= 0xfffff000;
        free_mem_addr += 0x1000;
    }

    if (phys_addr)
        *phys_addr = free_mem_addr;

    uint32_t ret = free_mem_addr;
    free_mem_addr += size; // increment pointer
    return ret;
}