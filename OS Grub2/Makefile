OBJECTS = boot.o kernel.o 
CC = i686-elf-gcc
CFLAGS = -m32 -nostdlib -nostdinc -I./ -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Werror -Wextra -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -felf32

all: kernel.elf

kernel.elf: $(OBJECTS)
	i686-elf-ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os: kernel.elf
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/
	cp grub.cfg iso/boot/grub/
	grub-mkrescue -o grub.iso iso
	#-@rm -rf iso 2>/dev/null || true

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	-@rm *.o *.elf *.iso iso/boot/kernel.elf ../SerialPort*.txt 2>/dev/null || true
	-@rm -rf iso 2>/dev/null || true