#include "../libc/stdint.h"
#include "paging.h"

extern void load_page_directory(void*);
extern void enable_paging();

page_directory_t *page_directory __attribute((aligned(4096))); // cheeky, we should adopt a better practice

// uint32_t page_directory[1024] __attribute((aligned(4096)));
// uint32_t first_page_table[1024] __attribute((aligned(4096)));

void setup_paging()
{
    // identity map the 4gib
    unsigned int i, j;
    for (i = 0; i < 1024; i++) {
        for (j = 0; j < 1024; j++) {
            page_directory->tables[i].entries[j] = (i * 0x10000000 + j * 0x1000) | 3;
        }
    }

    load_page_directory(page_directory);
    enable_paging();
}

// // Initialises paging
// void setup_paging()
// {
//     // Loop through each entry and set the following proeprties:
//     // superverisor - only kernel mode can access
//     // write enabled
//     // not present

//     int i;
//     for (i = 0; i < 1024; i++) {
//         page_directory[i] = 0x00000002;
//     }

//     // create first page table, map to beginning of memory
//     // we're mapping 4 megs
//     unsigned int j;
//     for (j = 0; j < 1024; j++) {
//         first_page_table[j] = (j * 0x1000) | 3; // attributes same as last time, but present
//     }

//     // now we can put this new page table into the page directory
//     page_directory[0] = ((unsigned int)first_page_table) | 3;

//     // now we revert to assembly and enable there
//     load_page_directory(page_directory);
//     enable_paging();
// }
