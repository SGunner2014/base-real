#ifndef _SCREEN_H
#define _SCREEN_H 1

void fb_write(const char *content, const char format);
void fb_clear();
void fb_set_pos(const int pos_x, const int pos_y);
int fb_get_pos();

#endif