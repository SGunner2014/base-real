#include "../libc/stdint.h"
#include "paging.h"

extern void load_page_directory(void *);
extern void enable_paging();

page_directory_t *page_directory __attribute__((aligned(4096)));

void setup_paging()
{
    // Set up some very basic identity paging for the first 1mb.
    unsigned int i;
    for (i = 0; i < 1024; i++)
    {
        page_directory->tables[0].entries[i] = 0x1000 * i | 3;
        page_directory->tables[768].entries[i] = 0x1000 * i | 3;
    }
    load_page_directory(page_directory);
    enable_paging();
}