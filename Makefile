override MAKEFLAGS += -rR

KERNEL_DIR := ./kernel
ISOROOT_DIR := ./iso_root

KERNEL_ELF := kernel.elf

override ISO := asbestos.iso

override QEMU := qemu-system-x86_64
override QEMUFLAGS := -m 2G -serial stdio -display sdl

override GDB := gdb
override GDBFLAGS := \
	-ex "target remote localhost:1234" \
	-ex "symbol-file $(KERNEL_DIR)/kernel.sym"

.PHONY:
all: $(ISO)

.PHONY:
run: $(ISO)
	$(QEMU) $(QEMUFLAGS) -cdrom $< -boot order=d 

.PHONY:
run-kvm: $(ISO)
	$(QEMU) $(QEMUFLAGS) -cdrom $< -boot order=d -enable-kvm

.PHONY:
run_kernel: $(KERNEL_DIR)/$(KERNEL_ELF)
	$(QEMU) $(QEMUFLAGS) -kernel $<

.PHONY:
debug: $(ISO)
	$(QEMU) $(QEMUFLAGS) -cdrom $< -boot order=d -s -S &
	sudo $(GDB) $(GDBFLAGS)

$(ISO): $(ISOROOT_DIR)/boot/$(KERNEL_ELF)
	cp -v grub/grub.cfg $(ISOROOT_DIR)/boot/grub
	grub-mkrescue -o $@ $(ISOROOT_DIR)/

$(ISOROOT_DIR)/boot/$(KERNEL_ELF): $(KERNEL_DIR)/$(KERNEL_ELF) | $(ISOROOT_DIR)
	cp -v $< $@

$(KERNEL_DIR)/$(KERNEL_ELF): $(KERNEL_DIR)/$(LIBK)
	$(MAKE) -C $(KERNEL_DIR) $(KERNEL_ELF)

$(ISOROOT_DIR):
	mkdir -v -p $@/boot/grub

.PHONY:
clean:
	$(MAKE) -C $(KERNEL_DIR) $(MAKECMDGOALS)
ifneq ("$(wildcard $(BOOT)/$(KERNEL_ELF))", "")
	rm $(BOOT)/$(KERNEL_ELF)
endif
ifneq ("$(wildcard $(ISO))", "")
	rm $(ISO)
endif
	rm -rf $(ISOROOT_DIR)
