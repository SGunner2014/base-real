#include "mem.h"

void memcpy(uint8_t *source, uint8_t *dest, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        *(dest + i) = *(source + i);
    }
}

void memset(uint8_t *dest, uint8_t val, uint32_t length)
{
    uint8_t *temp = (uint8_t*) dest;
    for (; length != 0; length--) {
        *temp++ = val;
    }
}