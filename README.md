# base-real
My attempt at something resembling an operating system.

## Here's the plan so far:

- Create a bootloader which shows a message on the screen
- Boot to a secondary bootloader with FAT16 filesystem, located at /BOOT.SYS
- Load the rest of the operating system into memory and start the kernel.
- Set up interrupts and interrupt handlers
- Create driver for keyboard and accept user input