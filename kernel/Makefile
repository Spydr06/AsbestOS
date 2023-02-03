LINK_SCRIPT := link.ld
KERNEL_ELF := kernel.elf
ASM_FILES := loader.s
OBJ_FILES := loader.o

.PHONY:
all: $(KERNEL_ELF)

$(KERNEL_ELF): $(OBJ_FILES)
	ld -T $(LINK_SCRIPT) -melf_i386 loader.o -o $(KERNEL_ELF)

$(OBJ_FILES):
	nasm -f elf32 $(ASM_FILES)

.PHONY:
clean:
ifneq ("$(wildcard $(KERNEL_ELF))", "")
	rm $(KERNEL_ELF)
endif
ifneq ("$(wildcard $(OBJ_FILES))", "")
	rm $(OBJ_FILES)
endif
