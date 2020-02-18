run: base.img
	sudo losetup /dev/loop50 base.img
	-sudo qemu-system-i386 -fda /dev/loop50 -d guest_errors
	sudo losetup -d /dev/loop50

bochs: base.img
	bochs

# Compiles all relevant assembly files below
%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

base.img: bootsector.bin secondstage.bin mbr.bin
	dd if=/dev/zero of=base.img bs=516096c count=1000
	sudo sfdisk base.img < sda.sfdisk
	sudo losetup /dev/loop50 base.img
	sudo mkdosfs -F16 /dev/loop50
	sudo mount -t msdos /dev/loop50 /mnt/myfloppy
	sudo cp secondstage.bin /mnt/myfloppy/BASELOAD.SYS
	sudo umount /mnt/myfloppy
	sudo losetup -d /dev/loop50
	dd if=mbr.bin of=base.img bs=512 count=1 seek=0 conv=notrunc
	dd if=bootsector.bin of=base.img bs=512 count=1 seek=64 conv=notrunc

secondstage.bin: src/boot/secondstage.bin
	cat $< > $@

bootsector.bin: src/boot/bootmain.bin
	cat $< > $@

mbr.bin: src/boot/mbr.bin
	cat $< > $@

clean:
	rm -rf *.o *.bin *.img src/boot/*.img src/boot/*.bin /src/boot/*.o