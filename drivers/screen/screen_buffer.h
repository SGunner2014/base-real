#ifndef _SCREEN_BUFFER_H
#define _SCREEN_BUFFER_H 1

struct pos_info
{
    int pos_x;
    int pos_y;
};

void fb_write(const char *content, const char format);
void fb_clear(const char format);
void fb_set_pos(const int pos_x, const int pos_y);
struct pos_info fb_get_pos();
void set_blink(int blink);
int get_blink();

#endif