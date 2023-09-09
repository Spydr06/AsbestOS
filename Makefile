KERNEL_DIR := ./kernel
LIMINE_DIR := ./limine
ISOROOT_DIR := ./iso_root

KERNEL_ELF := kernel.elf

override ISO := asbestos.iso

override XORRISO := xorriso
override XORRISOFLAGS += \
	-as mkisofs -b limine-bios-cd.bin \
	-no-emul-boot \
	-boot-load-size 4 \
	-boot-info-table \
	--efi-boot limine-uefi-cd.bin \
	-efi-boot-part \
	--efi-boot-image \
	--protective-msdos-label

override QEMU := qemu-system-x86_64
override QEMUFLAGS := -m 2G -serial stdio -display sdl -cpu qemu64

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
run_kernel: $(KERNEL_DIR)/$(KERNEL_ELF)
	$(QEMU) $(QEMUFLAGS) -kernel $<

.PHONY:
debug: $(ISO)
	$(QEMU) $(QEMUFLAGS) -cdrom $< -boot order=d -s -S &
	sudo $(GDB) $(GDBFLAGS)

$(ISO): $(ISOROOT_DIR)/$(KERNEL_ELF) | $(LIMINE_DIR)
	cp -v limine.cfg 					 \
		$(LIMINE_DIR)/limine-bios.sys 	 \
      	$(LIMINE_DIR)/limine-bios-cd.bin \
		$(LIMINE_DIR)/limine-uefi-cd.bin \
		$(ISOROOT_DIR)
	cp -v \
		$(LIMINE_DIR)/BOOTX64.EFI \
		$(LIMINE_DIR)/BOOTIA32.EFI \
		$(ISOROOT_DIR)/EFI/BOOT
	$(XORRISO) $(XORRISOFLAGS) $(ISOROOT_DIR) -o $@

$(LIMINE_DIR):
	git submodule init $(LIMINE_DIR)

$(ISOROOT_DIR)/$(KERNEL_ELF): $(KERNEL_DIR)/$(KERNEL_ELF) | $(ISOROOT_DIR)
	cp -v $< $@

$(KERNEL_DIR)/$(KERNEL_ELF): $(KERNEL_DIR)/$(LIBK)
	$(MAKE) -C $(KERNEL_DIR) $(KERNEL_ELF)

$(ISOROOT_DIR):
	mkdir -v $@
	mkdir -v -p $@/EFI/BOOT

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
