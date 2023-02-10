KERNEL := ./kernel
BOOT := ./iso/boot
KERNEL_ELF := kernel.elf
ISO := os.iso
QEMU := qemu-system-i386

# GDB := gdb # <- use this for the default gdb executable
# GDB := gdb-gef
GDB := i686-elf-gdb

LIBC := libc
LIBK := libk.a

GDBFLAGS := -ex "target remote localhost:1234" \
			-ex "symbol-file kernel/kernel.sym"

QEMUFLAGS := -m 128M -serial stdio -display sdl -cpu qemu32
ISOFLAGS := -R -b boot/grub/stage2_eltorito -no-emul-boot \
			-boot-load-size 4 -A os -input-charset utf8   \
			-boot-info-table

.PHONY:
all: $(ISO)

.PHONY:
run: $(ISO)
	$(QEMU) $(QEMUFLAGS) -cdrom $< -boot order=d 

.PHONY:
run_kernel: $(KERNEL)/$(KERNEL_ELF)
	$(QEMU) $(QEMUFLAGS) -kernel $<

.PHONY:
debug: $(ISO)
	$(QEMU) $(QEMUFLAGS) -cdrom $< -boot order=d -s -S &
	sudo $(GDB) $(GDBFLAGS)

$(ISO): $(BOOT)/$(KERNEL_ELF)	
	mkisofs $(ISOFLAGS) -o $@ iso

$(BOOT)/$(KERNEL_ELF): $(KERNEL)/$(KERNEL_ELF)
	cp $< $@

$(KERNEL)/$(KERNEL_ELF): $(KERNEL)/$(LIBK)
	$(MAKE) -C $(KERNEL) $(KERNEL_ELF)

$(KERNEL)/$(LIBK): $(LIBC)/$(LIBK)
	cp $< $@

$(LIBC)/$(LIBK):
	$(MAKE) -C $(LIBC) $(LIBK)

.PHONY:
clean:
	$(MAKE) -C $(KERNEL) $(MAKECMDGOALS)
	$(MAKE) -C $(LIBC) $(MAKECMDGOALS)
ifneq ("$(wildcard $(BOOT)/$(KERNEL_ELF))", "")
	rm $(BOOT)/$(KERNEL_ELF)
endif
ifneq ("$(wildcard $(ISO))", "")
	rm $(ISO)
endif
