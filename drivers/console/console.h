/*
* An API for interacting with the screen in a console-like
* manner.
*
* Author: Sam J Gunner
*/

#ifndef _CONSOLE_H
#define _CONSOLE_H

#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GRAY 0x7
#define DARK_GRAY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xa
#define LIGHT_CYAN 0xb
#define LIGHT_RED 0xc
#define LIGHT_MAGENTA 0xd
#define YELLOW 0xe
#define WHITE 0xf

void clear_screen();
void write(const char *content);
void print(const char *content);
void print_backspace();
void set_cursor_pos(const int x, const int y);
struct pos_info get_cursor_pos();
void set_background_colour(const char colour);
void set_foreground_color(const char colour);

#endif