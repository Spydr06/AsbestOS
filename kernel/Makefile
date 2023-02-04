# files
LINK_SCRIPT := link.ld
KERNEL_ELF := kernel.elf
LIBK := libk.a

SOURCES := $(wildcard *.[cs])
OBJECTS := $(patsubst %, %.o, $(SOURCES))

LIBK_INCLUDE := ../libc/include

# assembler, compiler flags
CC = gcc
AS = nasm
CFLAGS  = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		  -nostartfiles -nodefaultlibs -Wall -Wextra -c -I$(LIBK_INCLUDE)
LDFLAGS = -T $(LINK_SCRIPT) -melf_i386
ASFLAGS = -f elf

.PHONY:
all: $(KERNEL_ELF)

$(KERNEL_ELF): $(OBJECTS) $(LIBK)
	ld $(LDFLAGS) $^ -o $(KERNEL_ELF)

%.c.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.s.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

.PHONY:
clean:
ifneq ("$(wildcard $(KERNEL_ELF))", "")
	rm $(KERNEL_ELF)
endif
ifneq ("$(shell find . -name "*.o" -or -name "*.a")", "")
	rm $(shell find . -name "*.o" -or -name "*.a")
endif
