OBJECTS = boot/loader.o kernel/kmain.o drivers/screen/screen_buffer.o core/cpu/ports.o libc/mem.o core/mem/gdt.o core/cpu/idt.o core/cpu/isr.o \
	core/cpu/setup.o core/cpu/interrupt.o drivers/keyboard/keyboard.o drivers/console/console.o \
	boot/paging.o boot/paging_asm.o libc/string.o core/cpu/timer.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot \
		-boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o os.iso \
		iso

run: os.iso
	bochs

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso $(OBJECTS)