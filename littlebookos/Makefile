OBJECTS = loader.o framebuffer.o serialwriter.o io.o minilib.o interrupt.o descriptor_tables.o isr.o gdt.o kmain.o 
CC = i686-elf-gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -felf32

all: kernel.elf

kernel.elf: $(OBJECTS)
	i686-elf-ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os: kernel.elf
	cp kernel.elf iso/boot/
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	-@rm *.o *.elf *.iso iso/boot/kernel.elf ../SerialPort*.txt 2>/dev/null || true