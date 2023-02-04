KERNEL := ./kernel
BOOT := ./iso/boot
KERNEL_ELF := kernel.elf
ISO := os.iso
QEMU := qemu-system-x86_64

LIBC := libc
LIBK := libk.a

QEMUFLAGS := -boot order=d -m 32M -serial stdio -display sdl
ISOFLAGS := -R -b boot/grub/stage2_eltorito -no-emul-boot \
			-boot-load-size 4 -A os -input-charset utf8   \
			-boot-info-table

.PHONY:
all: $(ISO)

.PHONY:
run: $(ISO)
	$(QEMU) $(QEMUFLAGS) -cdrom $<

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
