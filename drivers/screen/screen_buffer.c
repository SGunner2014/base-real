/*
 * This is a really basic API for the frame buffer.
 *
 * We shouldn't use this directly - use console instead.
 *
 * Author: Sam J Gunner
 */

#include "screen_buffer.h"
#include "../../core/cpu/ports.h"
#include "../../libc/mem.h"

const int VID_MEM_ADDR = 0x000B8000;
const int REG_SCREEN_CTRL = 0x3d4;
const int REG_SCREEN_DATA = 0x3d5;
const int SCREEN_HEIGHT = 25;
const int SCREEN_WIDTH = 80;

int _getpos();
void _setpos(int pos);
void _printc(const char c, int format);

// Writes a string to the framebuffer at the current position
void fb_write(const char *content, const char format)
{
    int i = 0;

    while (content[i])
        _printc(content[i++], format);
}

// Clears the screen
void fb_clear(const char format)
{
    char *vid_mem = (char *)VID_MEM_ADDR;
    int i;
    for (i = 0; i < (SCREEN_HEIGHT * SCREEN_WIDTH * 2); i += 2)
    {
        vid_mem[i] = 0;
        vid_mem[i + 1] = format;
    }
    _setpos(0);
}

// Sets the current cursor position
void fb_set_pos(const int pos_x, const int pos_y)
{
    int offset;
    offset = (pos_y * SCREEN_WIDTH * 2) + (pos_x * 2);
    _setpos(offset);
}

// Returns the current cursor positions
struct pos_info fb_get_pos()
{
    int offset = _getpos() / 2;
    int pos_y = offset / SCREEN_WIDTH;
    int pos_x = offset % SCREEN_WIDTH;
    struct pos_info posinf;
    posinf.pos_x = pos_x;
    posinf.pos_y = pos_y;
    return posinf;
}

// void set_blink(int blink)
// {
// }

// int get_blink()
// {
// }

// Returns the current cursor position, accounting for 2-byte cells
int _getpos()
{
    int offset = 0;
    port_byte_out(REG_SCREEN_CTRL, 14);
    offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);

    // finally, account for 2-byte cells
    return offset * 2;
}

// Sets the current cursor position, accounting for 2-byte cells
void _setpos(int pos)
{
    pos = pos / 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(pos >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(pos & 0xff));
}

// Prints a single character to the screen
void _printc(const char c, int format)
{
    char *vid_mem = (char *)VID_MEM_ADDR;
    int offset = _getpos();
    int maxOffset = SCREEN_HEIGHT * SCREEN_WIDTH * 2;
    int newOffset;
    int lineLength = SCREEN_WIDTH * 2;

    // 1) work out new offset
    // 2) work out if we need to scroll a new line

    if (c == '\n')
    {
        int multiples = offset / lineLength + 1;
        newOffset = multiples * lineLength;
    }
    else
    {
        newOffset = offset + 2;
    }

    // we need to scroll the screen if this is true
    if (newOffset > maxOffset)
    {
        int i;
        uint32_t currOffset, prevOffset;

        // copy over the bytes from each row to the one above
        for (i = 1; i < SCREEN_HEIGHT; i++)
        {
            currOffset = (uint32_t)vid_mem + i * SCREEN_WIDTH * 2;
            prevOffset = (uint32_t)vid_mem + (i - 1) * SCREEN_WIDTH * 2;
            memcpy((unsigned char *)currOffset, (unsigned char *)prevOffset, SCREEN_WIDTH * 2);
        }

        // erase the last row
        currOffset = (SCREEN_HEIGHT - 1) * SCREEN_WIDTH * 2;
        memset((unsigned char *)currOffset, 0, SCREEN_WIDTH * 2);

        _setpos(currOffset);
        offset = currOffset;
    }
    else if (c == '\n')
    {
        _setpos(newOffset);
    }

    // finally, put the character into place
    if (c != '\n')
    {
        vid_mem[offset] = c;
        vid_mem[offset + 1] = format;
        _setpos(offset + 2);
    }
}