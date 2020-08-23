/*
* An API for interacting with the screen in a console-like
* manner.
*
* Author: Sam J Gunner
*/
#include "console.h"
#include "../screen/screen_buffer.h"

// Clears the screen with the current background colour.
void clear_screen()
{
    fb_clear(current_colours);
}

// Writes some content to the screen at the current position
void write(const char *content)
{
    fb_write(content, current_colours);
}

// Prints some content to the screen (followed by a newline char)
void print(const char *content)
{
    fb_write(content, current_colours);
    fb_write("\n", current_colours);
}

// Sets the current cursor position
void set_cursor_pos(const int x, const int y)
{
    fb_set_pos(x, y);
}

// Returns the current cursor position
struct pos_info get_cursor_pos()
{
    return fb_get_pos();
}

// Sets the current console background colour
void set_background_colour(const char colour)
{
    colour << 16;
    current_colours = current_colours & 0x0f;
    current_colours = current_colours | colour;
}

// Sets the current console foreground colour
void set_foreground_color(const char colour)
{
    current_colours = current_colours & 0xf0;
    current_colours = current_colours | colour;
}

void print_backspace()
{
    struct pos_info pos = fb_get_pos();
    if (pos.pos_x < 1)
    {
        if (pos.pos_y > 0)
        {
            pos.pos_y--;
        }
    }
    else
    {
        pos.pos_x--;
    }

    fb_set_pos(pos.pos_x, pos.pos_y);
    fb_write(' ', 0x00);
    fb_set_pos(pos.pos_x, pos.pos_y);
}