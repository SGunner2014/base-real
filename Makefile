run: base.img
	qemu-system-i386 -fda base.img -d guest_errors

# Compiles all relevant assembly files below
%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

base.img: bootsector.bin secondstage.bin
	dd if=/dev/zero of=base.img bs=512 count=2880
	sudo losetup /dev/loop50 base.img
	sudo mkdosfs /dev/loop50
	sudo mkdir -p /mnt/myfloppy
	sudo mount -t msdos /dev/loop50 /mnt/myfloppy

	sudo cp secondstage.bin /mnt/myfloppy/BOOT.SYS

	sudo umount /mnt/myfloppy
	sudo losetup -d /dev/loop50

	dd if=bootsector.bin of=base.img bs=512 count=1 seek=0 conv=notrunc

secondstage.bin: src/boot/secondstage.bin
	cat $< > $@

bootsector.bin: src/boot/bootmain.bin
	cat $< > $@

clean:
	rm -rf *.o *.bin *.img src/boot/*.img src/boot/*.bin /src/boot/*.o