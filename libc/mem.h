#ifndef MEM_H
#define MEM_H

#include "stdint.h"

void memcpy(uint8_t *source, uint8_t *dest, int n);
void memset(uint8_t *dest, uint8_t val, uint32_t len);

#endif