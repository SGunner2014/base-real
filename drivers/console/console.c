/*
* An API for interacting with the screen in a console-like
* manner.
*
* Author: Sam J Gunner
*/

#include "../screen/screen_buffer.h"

// Clears the screen with the current background colour.
void clear_screen()
{
    fb_clear();
}