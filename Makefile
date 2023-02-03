KERNEL := ./kernel
BOOT := ./iso/boot
KERNEL_ELF := kernel.elf
ISO := os.iso
QEMU := qemu-system-x86_64

.PHONY:
all: $(ISO)

.PHONY:
run: $(ISO)
	$(QEMU) -cdrom $< -boot order=d -m 32M

$(ISO): $(BOOT)/$(KERNEL_ELF)	
	mkisofs -R \
            -b boot/grub/stage2_eltorito    \
            -no-emul-boot                   \
            -boot-load-size 4               \
            -A os                           \
            -input-charset utf8             \
            -boot-info-table                \
            -o os.iso                       \
            iso

$(BOOT)/$(KERNEL_ELF): $(KERNEL)/$(KERNEL_ELF)
	cp $< $@

$(KERNEL)/$(KERNEL_ELF):
	$(MAKE) -C $(KERNEL) $(KERNEL_ELF)

.PHONY:
clean:
	$(MAKE) -C $(KERNEL) $(MAKECMDGOALS) 
ifneq ("$(wildcard $(BOOT)/$(KERNEL_ELF))", "")
	rm $(BOOT)/$(KERNEL_ELF)
endif
ifneq ("$(wildcard $(ISO))", "")
	rm $(ISO)
endif
