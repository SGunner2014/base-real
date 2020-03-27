ENTRY(loader) /* Name of the entry label */

SECTIONS {
    . = 0xC0100000; /* Code should be loaded at 3GB + 1MB */

    /* Align at 4kb and load to 1mb */
    .text ALIGN (0x1000) : AT(ADDR(.text)-0xC0000000)
    {
        *(.text)
    }

    .rodata ALIGN (0x1000) : AT(ADDR(.rodata)-0xC0000000)
    {
        *(.rodata*)
    }

    .data ALIGN (0x1000) : AT(ADDR(.data)-0xC0000000)
    {
        *(.data)
    }

    .bss ALIGN (0x1000) : AT(ADDR(.bss)-0xC0000000)
    {
        *(COMMON)
        *(.bss)
    }
}