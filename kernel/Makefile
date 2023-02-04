# files
LINK_SCRIPT := link.ld
KERNEL_ELF := kernel.elf
LIBK := libk.a

BUILDDIR := .build

SOURCES := $(wildcard *.[cs])
OBJECTS := $(patsubst %, $(BUILDDIR)/%.o, $(SOURCES))

LIBK_INCLUDE := ../libc/include

# assembler, compiler flags
CC = gcc
AS = nasm
CFLAGS  = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		  -O2 -nostartfiles -nodefaultlibs -Wall -Wextra -c -I$(LIBK_INCLUDE)
LDFLAGS = -T $(LINK_SCRIPT) -melf_i386
ASFLAGS = -f elf

.PHONY:
all: $(KERNEL_ELF)

$(KERNEL_ELF): $(OBJECTS) $(LIBK)
	ld $(LDFLAGS) $^ -o $(KERNEL_ELF)

$(BUILDDIR)/%.c.o: %.c | $(BUILDDIR)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.s.o: %.s | $(BUILDDIR)
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDDIR):
	mkdir $@

.PHONY:
clean:
ifneq ("$(wildcard $(KERNEL_ELF))", "")
	rm $(KERNEL_ELF)
endif
ifneq ("$(wildcard $(BUILDDIR))", "")
	rm -r $(BUILDDIR)
endif
ifneq ("$(wildcard $(LIBK))", "")
	rm $(LIBK)
endif
